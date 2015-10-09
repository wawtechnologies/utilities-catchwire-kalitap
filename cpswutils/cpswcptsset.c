
/*
 * cpswcptsset.c - CPSW CPTS Registers Set Utility
 *
 * Usage : cpswcptsset <register> <value>
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
    {"control"    , required_argument, 0, CPTS_CONTROL    },
    {"ts_push"    , required_argument, 0, CPTS_TS_PUSH    },
    {"ts_load_val", required_argument, 0, CPTS_TS_LOAD_VAL},
    {"ts_load_en" , required_argument, 0, CPTS_TS_LOAD_EN },
    {"intstat_raw", required_argument, 0, CPTS_INTSTAT_RAW},
    {"int_enable" , required_argument, 0, CPTS_INT_ENABLE },
    {"event_pop"  , required_argument, 0, CPTS_EVENT_POP  },
    {0            , 0                , 0, 0               }
  };

  opt = getopt_long(argc, argv, "", long_options, &long_index);

  if ((opt == -1) || (opt == '?'))
  {
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage: %s <register> <hex value>\n", argv[0]);
    fprintf(stderr, "\n");
    fprintf(stderr, "--control\n");
    fprintf(stderr, "--ts_push\n");
    fprintf(stderr, "--ts_load_val\n");
    fprintf(stderr, "--ts_load_en\n");
    fprintf(stderr, "--intstat_raw\n");
    fprintf(stderr, "--int_enable\n");
    fprintf(stderr, "--event_pop\n");
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

