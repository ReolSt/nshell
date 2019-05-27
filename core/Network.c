#include "nshell.h"
int socket_tcp_create
(
  SocketTCP *socket,
  ProtocolFamily protocol_family,
  AddressFamily address_family,
)
{
  socket_tcp_set_protocol_family(socket, protocol_family);
  socket_tcp_set_address_family(socket, address_family);
  int socket_descriptor = socket(protocol_family, SOCK_STREAM, 0);
  if(socket_descriptor < 0)
  {
    return socket_descriptor;
  }
  socket->socket_descriptor = socket_descriptor;
  return socket_descriptor;
}

void socket_tcp_set_port(SocketTCP *socket, short port)
{
  switch(socket->address_family)
  {
    case AddressFamily_IPv4:
    {
      SocketAddressIPv4 *server_address = (SocketAddressIPv4*)&(socket->server_address);
      server_address->sin_port = htons(port);
      break;
    }
  }
}

int socket_tcp_get_descriptor(SocketTCP *socket)
{
  return socket->socket_descriptor;
}

short socket_tcp_get_port(SocketTCP *socket)
{
  return ntohs(server_address.sin_port);
}

void socket_tcp_set_protocol_family
(
  SocketTCP *socket,
  ProtocolFamily protocol_family
)
{
  socket->protocol_family = protocol_family;
}

ProtocolFamily socket_tcp_get_protocol_family(SocketTCP *socket)
{
  return socket->protocol_family;
}

void socket_tcp_set_address_family
(
  SocketTCP *socket,
  AddressFamily address_family
)
{
  socket->address_family = address_family;
  server_address.sa_family = address_family;
}

AddressFamily socket_tcp_get_address_family(SocketTCP *socket)
{
  return socket->address_family;
}


int socket_tcp_connect(SocketTCP *socket, char *address, size_t len)
{
  size_t size = 0;
  switch(socket->address_family)
  {
    case AddressFamily_IPv4:
    {
      SocketAddressIPv4 *server_address = (SocketAddressIPv4*)&(socket->server_address);
      server_address->sin_addr.s_addr = inet_addr(address);
      size = sizeof(SockAddressIPv4);
      break;
    }
  }
  int result =
    connect(
      socket->socket_descriptor,
      (struct sockaddr*)&(socket->server_address),
      sizeof(socket->server_address)
    );
  if(result < 0)
  {
    return result;
  }
  string_init(&(socket->address_string), address, len);
  return result;
}

const char *socket_tcp_get_address(SocketTCP *socket)
{
  return string_c_str(&(socket->address_string));
}

void socket_tcp_close(SocketTCP *socket)
{
  string_destroy(&(socket->address_string));
  close(socket->socket_fd);
}
