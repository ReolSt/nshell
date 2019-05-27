#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "String.h"

typedef struct sockaddr SocketAddress;
typedef struct sockaddr_in SocketAddressIPv4;
typedef struct sockaddr_in6 SocketAddressIPv6;
typedef struct sockaddr_un SocketAddressUnix;

typedef enum _protocol_family
{
  ProtocolFamily_IPv4 = PF_INET,
  ProtocolFamily_IPv6 = PF_INET6,
#ifdef PF_LOCAL
  ProtocolFamily_Local = PF_LOCAL,
#endif
#ifdef PF_PACKET
  ProtocolFamily_Packet = PF_PACKET,
#endif
#ifdef PF_IPX
  ProtocolFamily_IPX = PF_IPX
#endif
} ProtocolFamily;

typedef enum _address_family
{
  AddressFamily_IPv4 = AF_INET,
  AddressFamily_IPv6 = AF_INET6,
#ifdef AF_LOCAL
  AddressFamily_Local = AF_LOCAL,
#endif
#ifdef AF_UNIX
  AddressFamily_Unix = AF_UNIX,
#endif
#ifdef AF_UNIX_CCSID
  AddressFamily_Unix_CCSID = AF_UNIX_CCSID,
#endif
#ifdef AF_IPX
  AddressFamily_IPX = AF_IPX
#endif
} AddressFamily;

typedef struct _socket_tcp
{
  int socket_descriptor;
  int port_host;
  String address_string;
  ProtocolFamily protocol_family;
  AddressFamily address_family;
  SocketAddress server_address;
} SocketTCP;

int socket_tcp_create
(
  SocketTCP *socket_tcp,
  ProtocolFamily protocol_family,
  AddressFamily address_family
);
int socket_tcp_get_descriptor(SocketTCP *socket_tcp);
void socket_tcp_set_port(SocketTCP *socket_tcp, short port);
int socket_tcp_get_port(SocketTCP *socket_tcp);
void socket_tcp_set_protocol_family
(
  SocketTCP *socket_tcp,
  ProtocolFamily protocol_family
);
ProtocolFamily socket_tcp_get_protocol_family(SocketTCP *socket_tcp);
void socket_tcp_set_address_family
(
  SocketTCP *socket_tcp,
  AddressFamily address_family
);
AddressFamily socket_tcp_get_address_family(SocketTCP *socket_tcp);
int socket_tcp_connect(SocketTCP *socket_tcp, char *address, size_t len);
const char *socket_tcp_get_address(SocketTCP *socket_tcp);
void socket_tcp_close(SocketTCP *socket_tcp);

#endif
