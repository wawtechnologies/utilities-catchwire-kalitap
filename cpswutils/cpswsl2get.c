
/*
 * cpsws2get.c - CPSW SL2 Registers Get Utility
 *
 * Usage : cpswsl2get <register>
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
    {"idver"     , no_argument, 0, SL2_IDVER     },
    {"maccontrol", no_argument, 0, SL2_MACCONTROL},
    {"macstatus" , no_argument, 0, SL2_MACSTATUS },
    {"soft_reset", no_argument, 0, SL2_SOFT_RESET},
    {"rx_maxlen" , no_argument, 0, SL2_RX_MAXLEN },
    {"bofftest"  , no_argument, 0, SL2_BOFFTEST  },
    {"rx_pause"  , no_argument, 0, SL2_RX_PAUSE  },
    {"tx_pause"  , no_argument, 0, SL2_TX_PAUSE  },
    {"emcontrol" , no_argument, 0, SL2_EMCONTROL },
    {"rx_pri_map", no_argument, 0, SL2_RX_PRI_MAP},
    {"tx_gap"    , no_argument, 0, SL2_TX_GAP    },
    {"all"       , no_argument, 0, CPSW_BASE_SIZE},
    {0           , 0          , 0, 0             }
  };

  opt = getopt_long(argc, argv, "", long_options, &long_index);

  if ((opt == -1) || (opt == '?'))
  {
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage: %s <register>\n", argv[0]);
    fprintf(stderr, "\n");
    fprintf(stderr, "--idver\n");
    fprintf(stderr, "--maccontrol\n");
    fprintf(stderr, "--macstatus\n");
    fprintf(stderr, "--soft_reset\n");
    fprintf(stderr, "--rx_maxlen\n");
    fprintf(stderr, "--bofftest\n");
    fprintf(stderr, "--rx_pause\n");
    fprintf(stderr, "--tx_pause\n");
    fprintf(stderr, "--emcontrol\n");
    fprintf(stderr, "--rx_pri_map\n");
    fprintf(stderr, "--tx_gap\n");
    fprintf(stderr, "--all\n");
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

  /* Get the value */

  if (opt == CPSW_BASE_SIZE)
  {
    fprintf(stdout, "\n");
    fprintf(stdout, "IDVER      : 0x%08X\n", ptr[SL2_IDVER     /4]);
    fprintf(stdout, "MACCONTROL : 0x%08X\n", ptr[SL2_MACCONTROL/4]);
    fprintf(stdout, "MACSTATUS  : 0x%08X\n", ptr[SL2_MACSTATUS /4]);
    fprintf(stdout, "SOFT_RESET : 0x%08X\n", ptr[SL2_SOFT_RESET/4]);
    fprintf(stdout, "RX_MAXLEN  : 0x%08X\n", ptr[SL2_RX_MAXLEN /4]);
    fprintf(stdout, "BOFFTEST   : 0x%08X\n", ptr[SL2_BOFFTEST  /4]);
    fprintf(stdout, "RX_PAUSE   : 0x%08X\n", ptr[SL2_RX_PAUSE  /4]);
    fprintf(stdout, "TX_PAUSE   : 0x%08X\n", ptr[SL2_TX_PAUSE  /4]);
    fprintf(stdout, "EMCONTROL  : 0x%08X\n", ptr[SL2_EMCONTROL /4]);
    fprintf(stdout, "RX_PRI_MAP : 0x%08X\n", ptr[SL2_RX_PRI_MAP/4]);
    fprintf(stdout, "TX_GAP     : 0x%08X\n", ptr[SL2_TX_GAP    /4]);
    fprintf(stdout, "\n");
  }
  else
  {
    fprintf(stdout, "0x%08X\n", ptr[((unsigned int)(opt))/4]);
  }

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

