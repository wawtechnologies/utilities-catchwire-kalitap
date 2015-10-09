
/*
 * cpswcptsget.c - CPSW CPTS Registers Get Utility
 *
 * Usage : cpswcptsget <register>
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
    {"idver"         , no_argument, 0, CPTS_IDVER         },
    {"control"       , no_argument, 0, CPTS_CONTROL       },
    {"ts_push"       , no_argument, 0,  CPTS_TS_PUSH      },
    {"ts_load_val"   , no_argument, 0, CPTS_TS_LOAD_VAL   },
    {"ts_load_en"    , no_argument, 0, CPTS_TS_LOAD_EN    },
    {"intstat_raw"   , no_argument, 0, CPTS_INTSTAT_RAW   },
    {"intstat_masked", no_argument, 0, CPTS_INTSTAT_MASKED},
    {"int_enable"    , no_argument, 0, CPTS_INT_ENABLE    },
    {"event_pop"     , no_argument, 0, CPTS_EVENT_POP     },
    {"event_low"     , no_argument, 0, CPTS_EVENT_LOW     },
    {"event_high"    , no_argument, 0, CPTS_EVENT_HIGH    },
    {"all"           , no_argument, 0, CPSW_BASE_SIZE     },
    {0               , 0          , 0, 0                  }
  };

  opt = getopt_long(argc, argv, "", long_options, &long_index);

  if ((opt == -1) || (opt == '?'))
  {
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage: %s <register>\n", argv[0]);
    fprintf(stderr, "\n");
    fprintf(stderr, "--idver\n");
    fprintf(stderr, "--control\n");
    fprintf(stderr, "--ts_push\n");
    fprintf(stderr, "--ts_load_val\n");
    fprintf(stderr, "--ts_load_en\n");
    fprintf(stderr, "--intstat_raw\n");
    fprintf(stderr, "--intstat_masked\n");
    fprintf(stderr, "--int_enable\n");
    fprintf(stderr, "--event_pop\n");
    fprintf(stderr, "--event_low\n");
    fprintf(stderr, "--event_high\n");
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
    fprintf(stdout, "IDVER          : 0x%08X\n", ptr[CPTS_IDVER         /4]);
    fprintf(stdout, "CONTROL        : 0x%08X\n", ptr[CPTS_CONTROL       /4]);
    fprintf(stdout, "TS_PUSH        : 0x%08X\n", ptr[CPTS_TS_PUSH       /4]);
    fprintf(stdout, "TS_LOAD_VAL    : 0x%08X\n", ptr[CPTS_TS_LOAD_VAL   /4]);
    fprintf(stdout, "TS_LOAD_EN     : 0x%08X\n", ptr[CPTS_TS_LOAD_EN    /4]);
    fprintf(stdout, "INTSTAT_RAW    : 0x%08X\n", ptr[CPTS_INTSTAT_RAW   /4]);
    fprintf(stdout, "INTSTAT_MASKED : 0x%08X\n", ptr[CPTS_INTSTAT_MASKED/4]);
    fprintf(stdout, "INT_ENABLE     : 0x%08X\n", ptr[CPTS_INT_ENABLE    /4]);
    fprintf(stdout, "EVENT_POP      : 0x%08X\n", ptr[CPTS_EVENT_POP     /4]);
    fprintf(stdout, "EVENT_LOW      : 0x%08X\n", ptr[CPTS_EVENT_LOW     /4]);
    fprintf(stdout, "EVENT_HIGH     : 0x%08X\n", ptr[CPTS_EVENT_HIGH    /4]);
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

