/*
 * BibleSync library
 * biblesync.cc
 *
 * Karl Kleinpaste, May 2014
 *
 * All files related to implementation of BibleSync, including program
 * source, READMEs, manual pages, and related similar documents, are in
 * the public domain.  As a matter of simple decency, your social
 * obligations are to credit the source and to coordinate any changes you
 * make back to the origin repository.  These obligations are non-
 * binding for public domain software, but they are to be seriously
 * handled nonetheless.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
 
#define	BSP_MULTICAST	"239.225.27.227"
#define	BSP_PORT	22272
 
struct in_addr        localInterface;
struct sockaddr_in    groupSock;
int                   sd;
int                   datalen;
char                  databuf[1024];
 
unsigned char header[] = {
    0x40, 0x9c, 0xaf, 0x11, 0x02, 0x02, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
};

unsigned char body[] = ""
    "app.name=MUMBLE\n"
    "app.version=4.3.2.1.0\n"
    "app.inst.uuid=00112233-4455-6677-8899-aabbccddeeff\n"
    "app.os=FAKE=OS\n"
    "app.device=6809 running BeOS\n"
    "app.user=BSP Tester (bsp)\n"
    "msg.sync.passPhrase=RandomPhrase\n"
    "msg.sync.domain=BIBLE-VERSE\n"
    "msg.sync.group=1\n"
    "msg.sync.bibleAbbrev=KJV\n"
    "msg.sync.altVerse=\n"
    "msg.sync.verse=Gen.1.1\n"
    "";

unsigned char message[1281],
    *mptr = &message[32];	/* point at message body. */

/*
 * argv[1] == local interface address
 * argv[2] == 1 or 2
 * argv[3] == other args
 * other args must be quoted on the command line w/trailing '\n'.
 * $ ./send-test 192.168.1.27 2 'msg.sync.passPhrase=TestPhrase
 * > '
 * you can add as many other things here as you like,
 * all quoted/newlined as one arg.
 */

int main (int argc, char *argv[])
{
    if ((argc != 3) && (argc != 4))
    {
	perror("arg count");
	exit(1);
    }
 
  /* ------------------------------------------------------------*/
  /*                                                             */
  /* Send Multicast Datagram code example.                       */
  /*                                                             */
  /* ------------------------------------------------------------*/
 
  /*
   * Create a datagram socket on which to send.
   */
  sd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sd < 0) {
    perror("opening datagram socket");
    exit(1);
  }
 
  /*
   * Initialize the group sockaddr structure with a
   * group address of 225.1.1.1 and port 5555.
   */
  memset((char *) &groupSock, 0, sizeof(groupSock));
  groupSock.sin_family = AF_INET;
  groupSock.sin_addr.s_addr = inet_addr(BSP_MULTICAST);
  groupSock.sin_port = htons(BSP_PORT);
 
  /*
   * Disable loopback so you do not receive your own datagrams.
   */
  {
    char loopch=1;
 
    if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP,
                   (char *)&loopch, sizeof(loopch)) < 0) {
      perror("setting IP_MULTICAST_LOOP:");
      close(sd);
      exit(1);
    }
  }
 
  /*
   * Set local interface for outbound multicast datagrams.
   * The IP address specified must be associated with a local,
   * multicast-capable interface.
   */
  localInterface.s_addr = inet_addr(argv[1]);
  if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF,
                 (char *)&localInterface,
                 sizeof(localInterface)) < 0) {
    perror("setting local interface");
    exit(1);
  }
 
 
  /*
   * Send a message to the multicast group specified by the
   * groupSock sockaddr structure.
   */

  memcpy(message, header, 32);
  message[5] = atoi(argv[2]);
  strcpy(mptr, body);
  if (argv[3])
      strcat(mptr, argv[3]);

  if (sendto(sd, message, 32+strlen(mptr), 0,
             (struct sockaddr*)&groupSock,
             sizeof(groupSock)) < 0)
  {
    perror("sending datagram message");
  }
}
