
/*
 * cpswaleset.c - CPSW ALE Register Set Utility
 *
 * Usage : cpswaleset <register> <value>
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
    {"control"     , required_argument, 0, ALE_CONTROL     },
    {"prescale"    , required_argument, 0, ALE_PRESCALE    },
    {"unknown_vlan", required_argument, 0, ALE_UNKNOWN_VLAN},
    {"tblctl"      , required_argument, 0, ALE_TBLCTL      },
    {"tblw2"       , required_argument, 0, ALE_TBLW2       },
    {"tblw1"       , required_argument, 0, ALE_TBLW1       },
    {"tblw0"       , required_argument, 0, ALE_TBLW0       },
    {"portctl0"    , required_argument, 0, ALE_PORTCTL0    },
    {"portctl1"    , required_argument, 0, ALE_PORTCTL1    },
    {"portctl2"    , required_argument, 0, ALE_PORTCTL2    },
    {"portctl3"    , required_argument, 0, ALE_PORTCTL3    },
    {"portctl4"    , required_argument, 0, ALE_PORTCTL4    },
    {"portctl5"    , required_argument, 0, ALE_PORTCTL5    },
    {0             , 0                , 0, 0               }
  };

  opt = getopt_long(argc, argv, "", long_options, &long_index);

  if ((opt == -1) || (opt == '?'))
  {
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage: %s <register> <value>\n", argv[0]);
    fprintf(stderr, "\n");
    fprintf(stderr, "--control\n");
    fprintf(stderr, "--prescale\n");
    fprintf(stderr, "--unknown_vlan\n");
    fprintf(stderr, "--tblctl\n");
    fprintf(stderr, "--tblw2\n");
    fprintf(stderr, "--tblw1\n");
    fprintf(stderr, "--tblw0\n");
    fprintf(stderr, "--portctl0\n");
    fprintf(stderr, "--portctl1\n");
    fprintf(stderr, "--portctl2\n");
    fprintf(stderr, "--portctl3\n");
    fprintf(stderr, "--portctl4\n");
    fprintf(stderr, "--portctl5\n");
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
