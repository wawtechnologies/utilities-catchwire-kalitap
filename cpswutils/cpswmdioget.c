
/*
 * cpswmdioget.c - CPSW MDIO Registers Get Utility
 *
 * Usage : cpswmdioget <register>
 * Author: Alexander Zakharov, WAW Technologies Inc.
 * Date  : November, 2015
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
    {"ver"           , no_argument, 0, MDIO_VER           },
    {"control"       , no_argument, 0, MDIO_CONTROL       },
    {"alive"         , no_argument, 0, MDIO_ALIVE         },
    {"link"          , no_argument, 0, MDIO_LINK          },
    {"linkintraw"    , no_argument, 0, MDIO_LINKINTRAW    },
    {"linkintmasked" , no_argument, 0, MDIO_LINKINTMASKED },
    {"userintraw"    , no_argument, 0, MDIO_USERINTRAW    },
    {"userintmasked" , no_argument, 0, MDIO_USERINTMASKED },
    {"userintmaskset", no_argument, 0, MDIO_USERINTMASKSET},
    {"userintmaskclr", no_argument, 0, MDIO_USERINTMASKCLR},
    {"useraccess0"   , no_argument, 0, MDIO_USERACCESS0   },
    {"userphysel0"   , no_argument, 0, MDIO_USERPHYSEL0   },
    {"useraccess1"   , no_argument, 0, MDIO_USERACCESS1   },
    {"userphysel1"   , no_argument, 0, MDIO_USERPHYSEL1   },
    {"all"           , no_argument, 0, CPSW_BASE_SIZE     },
    {0               , 0          , 0, 0                  }
  };

  opt = getopt_long(argc, argv, "", long_options, &long_index);

  if ((opt == -1) || (opt == '?'))
  {
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage: %s <register>\n", argv[0]);
    fprintf(stderr, "\n");
    fprintf(stderr, "--ver\n");
    fprintf(stderr, "--control\n");
    fprintf(stderr, "--alive\n");
    fprintf(stderr, "--link\n");
    fprintf(stderr, "--linkintraw\n");
    fprintf(stderr, "--linkintmasked\n");
    fprintf(stderr, "--userintraw\n");
    fprintf(stderr, "--userintmasked\n");
    fprintf(stderr, "--userintmaskset\n");
    fprintf(stderr, "--userintmaskclr\n");
    fprintf(stderr, "--useraccess0\n");
    fprintf(stderr, "--userphysel0\n");
    fprintf(stderr, "--useraccess1\n");
    fprintf(stderr, "--userphysel1\n");
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
    fprintf(stdout, "VER            : 0x%08X\n", ptr[MDIO_VER           /4]);
    fprintf(stdout, "CONTROL        : 0x%08X\n", ptr[MDIO_CONTROL       /4]);
    fprintf(stdout, "ALIVE          : 0x%08X\n", ptr[MDIO_ALIVE         /4]);
    fprintf(stdout, "LINK           : 0x%08X\n", ptr[MDIO_LINK          /4]);
    fprintf(stdout, "LINKINTRAW     : 0x%08X\n", ptr[MDIO_LINKINTRAW    /4]);
    fprintf(stdout, "LINKINTMASKED  : 0x%08X\n", ptr[MDIO_LINKINTMASKED /4]);
    fprintf(stdout, "USERINTRAW     : 0x%08X\n", ptr[MDIO_USERINTRAW    /4]);
    fprintf(stdout, "USERINTMASKED  : 0x%08X\n", ptr[MDIO_USERINTMASKED /4]);
    fprintf(stdout, "USERINTMASKSET : 0x%08X\n", ptr[MDIO_USERINTMASKSET/4]);
    fprintf(stdout, "USERINTMASKCLR : 0x%08X\n", ptr[MDIO_USERINTMASKCLR/4]);
    fprintf(stdout, "USERACCESS0    : 0x%08X\n", ptr[MDIO_USERACCESS0   /4]);
    fprintf(stdout, "USERPHYSEL0    : 0x%08X\n", ptr[MDIO_USERPHYSEL0   /4]);
    fprintf(stdout, "USERACCESS1    : 0x%08X\n", ptr[MDIO_USERACCESS1   /4]);
    fprintf(stdout, "USERPHYSEL1    : 0x%08X\n", ptr[MDIO_USERPHYSEL1   /4]);
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

