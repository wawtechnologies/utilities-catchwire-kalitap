
/* 
 * udp0srv.c - A simple UDP zero server 
 *
 * Usage : udp0srv <port>
 * Author: Alexander Zakharov, WAW Technologies Inc.
 * Date  : September, 2015
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define BUFSIZE 65536


int
main(int argc, char **argv)
{
  int sockfd;                    /* socket                        */
  int portno;                    /* port to listen on             */
  int clientlen;                 /* byte size of client's address */
  struct sockaddr_in serveraddr; /* server's addr                 */
  struct sockaddr_in clientaddr; /* client addr                   */
  char buf[BUFSIZE];             /* message buf                   */
  int optval;                    /* flag value for setsockopt     */
  int n;                         /* message byte size             */

  /* 
   * Check command line arguments 
   */
  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit   (EXIT_FAILURE);
  }

  portno = atoi(argv[1]);

  /* 
   * Socket: create parent socket 
   */
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  if (sockfd < 0) 
  {
    perror("ERROR opening socket");
    exit  (EXIT_FAILURE);
  }

  /* Setsockopt: Handy debugging trick that lets 
   * us rerun the server immediately after we kill it; 
   * otherwise we have to wait about 20 secs. 
   * Eliminates "ERROR on binding: Address already in use" error. 
   */
  optval = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 
	     (const void *)&optval , sizeof(int));

  /*
   * Build server's Internet address
   */
  bzero((char *) &serveraddr, sizeof(serveraddr));
  serveraddr.sin_family      = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port        = htons((unsigned short)portno);

  /* 
   * Bind: associate the parent socket with a port 
   */
  if (bind(sockfd, (struct sockaddr *) &serveraddr, 
	            sizeof(serveraddr)) < 0) 
  {
    perror("ERROR on socket bind");
    exit  (EXIT_FAILURE);
  }

  /* 
   * Main loop: wait for a datagram, then do nothing
   */
  while (1)
  {
    bzero(buf, BUFSIZE);
    n = recvfrom(sockfd, buf, BUFSIZE, 0,
		 (struct sockaddr *) &clientaddr, &clientlen);
    if (n < 0)
    {
      perror("ERROR in recvfrom");
      exit  (EXIT_FAILURE);
    }

    /* Do nothing */
    /* printf("Server received %d bytes\n", n); */
  }
}

