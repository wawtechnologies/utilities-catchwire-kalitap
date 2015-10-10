
/*
 * cpswsl2set.c - CPSW SL2 Registers Set Utility
 *
 * Usage : cpswsl2`set <register> <value>
 * Author: Alexander Zakharov, WAW Technologies Inc.
 * Date  : October, 2015
 */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include "cpswregs.h"


int
main(int argc, char *argv[])
{
  int                    opt        = 0;
  int                    long_index = 0;
  int                    fd         = 0;
  unsigned int           val        = 0;
  volatile unsigned int *ptr        = NULL;

  static struct option long_options[] =
  {
    {"maccontrol", required_argument, 0, SL2_MACCONTROL},
    {"soft_reset", required_argument, 0, SL2_SOFT_RESET},
    {"rx_maxlen" , required_argument, 0, SL2_RX_MAXLEN },
    {"bofftest"  , required_argument, 0, SL2_BOFFTEST  },
    {"emcontrol" , required_argument, 0, SL2_EMCONTROL },
    {"rx_pri_map", required_argument, 0, SL2_RX_PRI_MAP},
    {"tx_gap"    , required_argument, 0, SL2_TX_GAP    },
    {0           , 0                , 0, 0             }
  };

  opt = getopt_long(argc, argv, "", long_options, &long_index);

  if ((opt == -1) || (opt == '?'))
  {
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage: %s <register> <hex value>\n", argv[0]);
    fprintf(stderr, "\n");
    fprintf(stderr, "--maccontrol\n");
    fprintf(stderr, "--soft_reset\n");
    fprintf(stderr, "--rx_maxlen\n");
    fprintf(stderr, "--bofftest\n");
    fprintf(stderr, "--emcontrol\n");
    fprintf(stderr, "--rx_pri_map\n");
    fprintf(stderr, "--tx_gap\n");
    fprintf(stderr, "\n");
    exit   (EXIT_FAILURE);
  }

  /* Open /dev/mem */

  fd = open("/dev/mem", O_RDWR | O_SYNC);

  if (fd == -1)
  {
    fprintf(stderr, "Cannot open /dev/mem\n");
    perror ("open");
    exit   (EXIT_FAILURE);
  }

  /* Map target memory */

  ptr = (volatile unsigned int *)mmap(NULL,
                                      CPSW_BASE_SIZE,
                                      PROT_READ | PROT_WRITE,
                                      MAP_SHARED,
                                      fd,
                                      CPSW_BASE_ADDR);


  if (ptr == MAP_FAILED)
  {
    close  (fd);
    fprintf(stderr, "Memory mapping failed\n");
    perror ("mmap");
    exit   (EXIT_FAILURE);
  }

  /* Get the value from optarg */

  val = strtoul(optarg, NULL, 16);

  /* Set the value */

  ptr[((unsigned int)(opt))/4] = val;

  /* Unmap target memory */

  if (munmap((void *)ptr, CPSW_BASE_SIZE) == -1)
  {
    close  (fd);
    fprintf(stderr, "Cannot unmap target memory\n");
    perror ("munmap");
    exit   (EXIT_FAILURE);
  }

  /* Close /dev/mem */

  if (close(fd) == -1)
  {
    fprintf(stderr, "Cannot close /dev/mem\n");
    perror ("close");
    exit   (EXIT_FAILURE);
  }

  exit (EXIT_SUCCESS);
}

