#ifndef RAINBOW_SOCKET_H
#define RAINBOW_SOCKET_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "RainbowCall.h"
#include "RainbowString.h"
#include "RainbowFileStream.h"

typedef struct sockaddr RainbowSocketAddress;
typedef struct sockaddr_in RainbowSocketAddressIPv4;
typedef struct sockaddr_in6 RainbowSocketAddressIPv6;
typedef struct sockaddr_un RainbowSocketAddressUnix;

typedef enum __Rainbow_Socket_Type
{
  RainbowSocketType_Stream = SOCK_STREAM,
  RainbowSocketType_Dgram = SOCK_DGRAM,
  RainbowSocketType_Raw = SOCK_RAW,
#ifdef SOCK_RDM
  RainbowSocketType_RDM = SOCK_RDM,
#endif
#ifdef SOCK_SEQPACKET
  RainbowSocketType_SeqPacket = SOCK_SEQPACKET,
#endif
#ifdef SOCK_PACKET
  RainbowSocketType_Packet = SOCK_PACKET
#endif
} RainbowSocketType;

typedef enum __Rainbow_Address_Family
{
  RainbowAddressFamily_UnSpec = PF_UNSPEC,
#ifdef AF_UNIX
  RainbowAddressFamily_Unix = AF_UNIX,
#endif
  RainbowAddressFamily_IPv4 = AF_INET,
#ifdef AF_AX25
  RainbowAddressFamily_AX25 = AF_AX25,
#endif
#ifdef AF_IPX
  RainbowAddressFamily_IPX = AF_IPX,
#endif
#ifdef AF_APPLETALK
  RainbowAddressFamily_AppleTalk = AF_APPLETALK,
#endif
#ifdef AF_NETROM
  RainbowAddressFamily_NetRom = AF_NETROM,
#endif
#ifdef AF_BRIDGE
  RainbowAddressFamily_Bridge = AF_BRIDGE,
#endif
#ifdef AF_AAL5
  RainbowAddressFamily_AAL5 = AF_AAL5,
#endif
#ifdef AF_X25
  RainbowAddressFamily_X25 = AF_X25,
#endif
  RainbowAddressFamily_IPv6 = AF_INET6,
#ifdef AF_MAX
  RainbowAddressFamily_Max = AF_MAX
#endif
} RainbowAddressFamily;

typedef enum __Protocol_Family
{
  RainbowProtocolFamily_UnSpec = PF_UNSPEC,
#ifdef PF_UNIX
  RainbowProtocolFamily_Unix = PF_UNIX,
#endif
  RainbowProtocolFamily_IPv4 = PF_INET,
#ifdef PF_AX25
  RainbowProtocolFamily_AX25 = PF_AX25,
#endif
#ifdef PF_IPX
  RainbowProtocolFamily_IPX = PF_IPX,
#endif
#ifdef PF_APPLETALK
  RainbowProtocolFamily_AppleTalk = PF_APPLETALK,
#endif
#ifdef PF_NETROM
  RainbowProtocolFamily_NetRom = PF_NETROM,
#endif
#ifdef PF_BRIDGE
  RainbowProtocolFamily_Bridge = PF_BRIDGE,
#endif
#ifdef PF_AAL5
  RainbowProtocolFamily_AAL5 = PF_AAL5,
#endif
#ifdef PF_X25
  RainbowProtocolFamily_X25 = PF_X25,
#endif
  RainbowProtocolFamily_IPv6 = PF_INET6,
#ifdef PF_MAX
  RainbowProtocolFamily_Max = PF_MAX
#endif
} RainbowProtocolFamily;

typedef struct __Rainbow_Socket_TCP
{
  int initialized;
  unsigned int port_host;
  RainbowFileStream file_stream;
  RainbowString address_RainbowString;
  RainbowProtocolFamily protocol_family;
  RainbowAddressFamily address_family;
  RainbowSocketAddress server_address;

  int (*Initialize)(struct __Rainbow_Socket_TCP *, RainbowProtocolFamily, RainbowAddressFamily);
  int (*IsInitialized)(struct __Rainbow_Socket_TCP *);
  RainbowFileStream * (*GetFileStream)(struct __Rainbow_Socket_TCP *);
  unsigned int (*GetPort)(struct __Rainbow_Socket_TCP *);
  void (*SetPort)(struct __Rainbow_Socket_TCP *, unsigned int port);
  RainbowProtocolFamily (*GetProtocolFamily)(struct __Rainbow_Socket_TCP *);
  void (*SetProtocolFamily)(struct __Rainbow_Socket_TCP *, RainbowProtocolFamily);
  RainbowAddressFamily (*GetAddressFamily)(struct __Rainbow_Socket_TCP *);
  void (*SeAddressFamily)(struct __Rainbow_Socket_TCP *, RainbowAddressFamily);
  int (*Connect)(struct __Rainbow_Socket_TCP *, const char *, size_t);
  const char * (*GetAddress)(struct __Rainbow_Socket_TCP *);
  void (*Destroy)(struct __Rainbow_Socket_TCP *);
} RainbowSocketTCP;

int RainbowSocketTCP_Initialize
(
  RainbowSocketTCP * socket_tcp,
  RainbowProtocolFamily protocol_family,
  RainbowAddressFamily address_family
);
int RainbowSocketTCP_IsInitialized
(
  RainbowSocketTCP * socket_tcp
);
RainbowFileStream * RainbowSocketTCP_GetFileStream(RainbowSocketTCP * socket_tcp);
unsigned int RainbowSocketTCP_GetPort(RainbowSocketTCP * socket_tcp);
void RainbowSocketTCP_SetPort(RainbowSocketTCP * socket_tcp, unsigned int port);
RainbowProtocolFamily RainbowSocketTCP_GetProtocolFamily(RainbowSocketTCP * socket_tcp);

void RainbowSocketTCP_SetProtocolFamily
(
  RainbowSocketTCP * socket_tcp,
  RainbowProtocolFamily protocol_family
);
RainbowAddressFamily RainbowSocketTCP_GetAddressFamily(RainbowSocketTCP * socket_tcp);
void RainbowSocketTCP_SetAddressFamily
(
  RainbowSocketTCP * socket_tcp,
  RainbowAddressFamily address_family
);
int RainbowSocketTCP_Connect(RainbowSocketTCP * socket_tcp, const char *address, size_t len);
const char *RainbowSocketTCP_GetAddress(RainbowSocketTCP * socket_tcp);
void RainbowSocketTCP_Destroy(RainbowSocketTCP * socket_tcp);

#endif
