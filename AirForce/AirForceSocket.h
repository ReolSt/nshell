#ifndef AIRFORCE_SOCKET_H
#define AIRFORCE_SOCKET_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "AirForceCall.h"
#include "AirForceString.h"
#include "AirForceFileStream.h"

typedef struct sockaddr AirForceSocketAddress;
typedef struct sockaddr_in AirForceSocketAddressIPv4;
typedef struct sockaddr_in6 AirForceSocketAddressIPv6;
typedef struct sockaddr_un AirForceSocketAddressUnix;

typedef enum __AirForce_Socket_Type
{
  AirForceSocketType_Stream = SOCK_STREAM,
  AirForceSocketType_Dgram = SOCK_DGRAM,
  AirForceSocketType_Raw = SOCK_RAW,
#ifdef SOCK_RDM
  AirForceSocketType_RDM = SOCK_RDM,
#endif
#ifdef SOCK_SEQPACKET
  AirForceSocketType_SeqPacket = SOCK_SEQPACKET,
#endif
#ifdef SOCK_PACKET
  AirForceSocketType_Packet = SOCK_PACKET
#endif
} AirForceSocketType;

typedef enum __AirForce_Address_Family
{
  AirForceAddressFamily_UnSpec = PF_UNSPEC,
#ifdef AF_UNIX
  AirForceAddressFamily_Unix = AF_UNIX,
#endif
  AirForceAddressFamily_IPv4 = AF_INET,
#ifdef AF_AX25
  AirForceAddressFamily_AX25 = AF_AX25,
#endif
#ifdef AF_IPX
  AirForceAddressFamily_IPX = AF_IPX,
#endif
#ifdef AF_APPLETALK
  AirForceAddressFamily_AppleTalk = AF_APPLETALK,
#endif
#ifdef AF_NETROM
  AirForceAddressFamily_NetRom = AF_NETROM,
#endif
#ifdef AF_BRIDGE
  AirForceAddressFamily_Bridge = AF_BRIDGE,
#endif
#ifdef AF_AAL5
  AirForceAddressFamily_AAL5 = AF_AAL5,
#endif
#ifdef AF_X25
  AirForceAddressFamily_X25 = AF_X25,
#endif
  AirForceAddressFamily_IPv6 = AF_INET6,
#ifdef AF_MAX
  AirForceAddressFamily_Max = AF_MAX
#endif
} AirForceAddressFamily;

typedef enum __Protocol_Family
{
  AirForceProtocolFamily_UnSpec = PF_UNSPEC,
#ifdef PF_UNIX
  AirForceProtocolFamily_Unix = PF_UNIX,
#endif
  AirForceProtocolFamily_IPv4 = PF_INET,
#ifdef PF_AX25
  AirForceProtocolFamily_AX25 = PF_AX25,
#endif
#ifdef PF_IPX
  AirForceProtocolFamily_IPX = PF_IPX,
#endif
#ifdef PF_APPLETALK
  AirForceProtocolFamily_AppleTalk = PF_APPLETALK,
#endif
#ifdef PF_NETROM
  AirForceProtocolFamily_NetRom = PF_NETROM,
#endif
#ifdef PF_BRIDGE
  AirForceProtocolFamily_Bridge = PF_BRIDGE,
#endif
#ifdef PF_AAL5
  AirForceProtocolFamily_AAL5 = PF_AAL5,
#endif
#ifdef PF_X25
  AirForceProtocolFamily_X25 = PF_X25,
#endif
  AirForceProtocolFamily_IPv6 = PF_INET6,
#ifdef PF_MAX
  AirForceProtocolFamily_Max = PF_MAX
#endif
} AirForceProtocolFamily;

typedef struct __AirForce_Socket_TCP
{
  int initialized;
  unsigned int port_host;
  AirForceFileStream file_stream;
  AirForceString address_AirForceString;
  AirForceProtocolFamily protocol_family;
  AirForceAddressFamily address_family;
  AirForceSocketAddress server_address;

  int (*Initialize)(struct __AirForce_Socket_TCP *, AirForceProtocolFamily, AirForceAddressFamily);
  int (*IsInitialized)(struct __AirForce_Socket_TCP *);
  AirForceFileStream * (*GetFileStream)(struct __AirForce_Socket_TCP *);
  unsigned int (*GetPort)(struct __AirForce_Socket_TCP *);
  void (*SetPort)(struct __AirForce_Socket_TCP *, unsigned int port);
  AirForceProtocolFamily (*GetProtocolFamily)(struct __AirForce_Socket_TCP *);
  void (*SetProtocolFamily)(struct __AirForce_Socket_TCP *, AirForceProtocolFamily);
  AirForceAddressFamily (*GetAddressFamily)(struct __AirForce_Socket_TCP *);
  void (*SeAddressFamily)(struct __AirForce_Socket_TCP *, AirForceAddressFamily);
  int (*Connect)(struct __AirForce_Socket_TCP *, const char *, size_t);
  const char * (*GetAddress)(struct __AirForce_Socket_TCP *);
  void (*Destroy)(struct __AirForce_Socket_TCP *);
} AirForceSocketTCP;

int AirForceSocketTCP_Initialize
(
  AirForceSocketTCP * socket_tcp,
  AirForceProtocolFamily protocol_family,
  AirForceAddressFamily address_family
);
int AirForceSocketTCP_IsInitialized
(
  AirForceSocketTCP * socket_tcp
);
AirForceFileStream * AirForceSocketTCP_GetFileStream(AirForceSocketTCP * socket_tcp);
unsigned int AirForceSocketTCP_GetPort(AirForceSocketTCP * socket_tcp);
void AirForceSocketTCP_SetPort(AirForceSocketTCP * socket_tcp, unsigned int port);
AirForceProtocolFamily AirForceSocketTCP_GetProtocolFamily(AirForceSocketTCP * socket_tcp);

void AirForceSocketTCP_SetProtocolFamily
(
  AirForceSocketTCP * socket_tcp,
  AirForceProtocolFamily protocol_family
);
AirForceAddressFamily AirForceSocketTCP_GetAddressFamily(AirForceSocketTCP * socket_tcp);
void AirForceSocketTCP_SetAddressFamily
(
  AirForceSocketTCP * socket_tcp,
  AirForceAddressFamily address_family
);
int AirForceSocketTCP_Connect(AirForceSocketTCP * socket_tcp, const char *address, size_t len);
const char *AirForceSocketTCP_GetAddress(AirForceSocketTCP * socket_tcp);
void AirForceSocketTCP_Destroy(AirForceSocketTCP * socket_tcp);

#endif
