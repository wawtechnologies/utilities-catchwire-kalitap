
/*
 * cpswaleset.c - CPSW ALE Register Get Utility
 *
 * Usage : cpswaleget <register>
 * Author: Alexander Zakharov, WAW Technologies Inc.
 * Date  : September, 2015
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
    {"idver"       , no_argument, 0, ALE_IDVER       },
    {"control"     , no_argument, 0, ALE_CONTROL     },
    {"prescale"    , no_argument, 0, ALE_PRESCALE    },
    {"unknown_vlan", no_argument, 0, ALE_UNKNOWN_VLAN},
    {"tblctl"      , no_argument, 0, ALE_TBLCTL      },
    {"tblw2"       , no_argument, 0, ALE_TBLW2       },
    {"tblw1"       , no_argument, 0, ALE_TBLW1       },
    {"tblw0"       , no_argument, 0, ALE_TBLW0       },
    {"portctl0"    , no_argument, 0, ALE_PORTCTL0    },
    {"portctl1"    , no_argument, 0, ALE_PORTCTL1    },
    {"portctl2"    , no_argument, 0, ALE_PORTCTL2    },
    {"portctl3"    , no_argument, 0, ALE_PORTCTL3    },
    {"portctl4"    , no_argument, 0, ALE_PORTCTL4    },
    {"portctl5"    , no_argument, 0, ALE_PORTCTL5    },
    {"all"         , no_argument, 0, CPSW_BASE_SIZE  },
    {0             , 0          , 0, 0               }
  };

  opt = getopt_long(argc, argv, "", long_options, &long_index);

  if ((opt == -1) || (opt == '?'))
  {
    fprintf(stderr, "Usage: %s <register>\n", argv[0]);
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
    fprintf(stdout, "IDVER        : 0x%08X\n", ptr[ALE_IDVER       /4]);
    fprintf(stdout, "CONTROL      : 0x%08X\n", ptr[ALE_CONTROL     /4]);
    fprintf(stdout, "PRESCALE     : 0x%08X\n", ptr[ALE_PRESCALE    /4]);
    fprintf(stdout, "UNKNOWN_VLAN : 0x%08X\n", ptr[ALE_UNKNOWN_VLAN/4]);
    fprintf(stdout, "TBLCTL       : 0x%08X\n", ptr[ALE_TBLCTL      /4]);
    fprintf(stdout, "TBLW2        : 0x%08X\n", ptr[ALE_TBLW2       /4]);
    fprintf(stdout, "TBLW1        : 0x%08X\n", ptr[ALE_TBLW1       /4]);
    fprintf(stdout, "TBLW0        : 0x%08X\n", ptr[ALE_TBLW0       /4]);
    fprintf(stdout, "PORTCTL0     : 0x%08X\n", ptr[ALE_PORTCTL0    /4]);
    fprintf(stdout, "PORTCTL1     : 0x%08X\n", ptr[ALE_PORTCTL1    /4]);
    fprintf(stdout, "PORTCTL2     : 0x%08X\n", ptr[ALE_PORTCTL2    /4]);
    fprintf(stdout, "PORTCTL3     : 0x%08X\n", ptr[ALE_PORTCTL3    /4]);
    fprintf(stdout, "PORTCTL4     : 0x%08X\n", ptr[ALE_PORTCTL4    /4]);
    fprintf(stdout, "PORTCTL5     : 0x%08X\n", ptr[ALE_PORTCTL5    /4]);
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

