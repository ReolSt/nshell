#include "Network.h"
#include "String.h"
int socket_tcp_create
(
  SocketTCP *socket_tcp,
  ProtocolFamily protocol_family,
  AddressFamily address_family
)
{
  socket_tcp_set_protocol_family(socket_tcp, protocol_family);
  socket_tcp_set_address_family(socket_tcp, address_family);
  int socket_descriptor = socket(protocol_family, SOCK_STREAM, 0);
  if(socket_descriptor < 0)
  {
    return socket_descriptor;
  }
  socket_tcp->socket_descriptor = socket_descriptor;
  socket_tcp->socket_file = fdopen(socket_descriptor, "r+");
  return socket_descriptor;
}

void socket_tcp_set_port(SocketTCP *socket_tcp, short port)
{
  switch(socket_tcp->address_family)
  {
    case AddressFamily_IPv4:
    {
      SocketAddressIPv4 *server_address = (SocketAddressIPv4*)&(socket_tcp->server_address);
      server_address->sin_port = htons(port);
      break;
    }
  }
}

int socket_tcp_get_descriptor(SocketTCP *socket_tcp)
{
  return socket_tcp->socket_descriptor;
}

FILE* socket_tcp_get_file(SocketTCP *socket_tcp)
{
  return socket_tcp->socket_file;
}

short socket_tcp_get_port(SocketTCP *socket_tcp)
{
  return socket_tcp->port_host;
}

void socket_tcp_set_protocol_family
(
  SocketTCP *socket_tcp,
  ProtocolFamily protocol_family
)
{
  socket_tcp->protocol_family = protocol_family;
}

ProtocolFamily socket_tcp_get_protocol_family(SocketTCP *socket_tcp)
{
  return socket_tcp->protocol_family;
}

void socket_tcp_set_address_family
(
  SocketTCP *socket_tcp,
  AddressFamily address_family
)
{
  socket_tcp->address_family = address_family;
  socket_tcp->server_address.sa_family = address_family;
}

AddressFamily socket_tcp_get_address_family(SocketTCP *socket_tcp)
{
  return socket_tcp->address_family;
}


int socket_tcp_connect(SocketTCP *socket_tcp, char *address, size_t len)
{
  size_t size = 0;
  switch(socket_tcp->address_family)
  {
    case AddressFamily_IPv4:
    {
      SocketAddressIPv4 *server_address = (SocketAddressIPv4*)&(socket_tcp->server_address);
      server_address->sin_addr.s_addr = inet_addr(address);
      size = sizeof(SocketAddressIPv4);
      break;
    }
  }
  int result =
    connect(
      socket_tcp->socket_descriptor,
      (struct sockaddr*)&(socket_tcp->server_address),
      sizeof(socket_tcp->server_address)
    );
  if(result < 0)
  {
    return result;
  }
  string_init(&(socket_tcp->address_string), address, len);
  return result;
}

const char *socket_tcp_get_address(SocketTCP *socket_tcp)
{
  return string_c_str(&(socket_tcp->address_string));
}

void socket_tcp_close(SocketTCP *socket_tcp)
{
  string_destroy(&(socket_tcp->address_string));
  close(socket_tcp->socket_descriptor);
}
