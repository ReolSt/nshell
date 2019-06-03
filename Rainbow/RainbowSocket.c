#include "RainbowSocket.h"

int RainbowSocketTCP_Initialize
(
  RainbowSocketTCP * socket_tcp,
  RainbowProtocolFamily protocol_family,
  RainbowAddressFamily address_family
)
{
  memset(&(socket_tcp->server_address), 0, sizeof(socket_tcp->server_address));
  int socket_descriptor = socket(protocol_family, RainbowSocketType_Stream, 0);
  if(socket_descriptor < 0)
  {
    return socket_descriptor;
  }
  RainbowSocketTCP_SetProtocolFamily(socket_tcp, protocol_family);
  RainbowSocketTCP_SetAddressFamily(socket_tcp, address_family);
  RainbowFileStream_Initialize(&(socket_tcp->file_stream), socket_descriptor, "r+");
//function pointers
  socket_tcp->Initialize = RainbowSocketTCP_Initialize;
  socket_tcp->IsInitialized = RainbowSocketTCP_IsInitialized;
  socket_tcp->GetFileStream = RainbowSocketTCP_GetFileStream;
  socket_tcp->GetPort = RainbowSocketTCP_GetPort;
  socket_tcp->SetPort = RainbowSocketTCP_SetPort;
  socket_tcp->GetProtocolFamily= RainbowSocketTCP_GetProtocolFamily;
  socket_tcp->SetProtocolFamily= RainbowSocketTCP_SetProtocolFamily;
  socket_tcp->Connect = RainbowSocketTCP_Connect;
  socket_tcp->GetAddress = RainbowSocketTCP_GetAddress;
  socket_tcp->Destroy = RainbowSocketTCP_Destroy;
//
  socket_tcp->initialized = 1;
  return socket_descriptor;
}

int RainbowSocketTCP_IsInitialized(RainbowSocketTCP * socket_tcp)
{
  return socket_tcp->initialized;
}
RainbowFileStream * RainbowSocketTCP_GetFileStream(RainbowSocketTCP * socket_tcp)
{
  return &(socket_tcp->file_stream);
}

unsigned int RainbowSocketTCP_GetPort(RainbowSocketTCP * socket_tcp)
{
  return socket_tcp->port_host;
}

void RainbowSocketTCP_SetPort(RainbowSocketTCP * socket_tcp, unsigned int port)
{
  switch(socket_tcp->address_family)
  {
    case RainbowAddressFamily_IPv4:
    {
      RainbowSocketAddressIPv4 *server_address = (RainbowSocketAddressIPv4 *)&(socket_tcp->server_address);
      server_address->sin_port = htons(port);
      break;
    }
  }
}

RainbowProtocolFamily RainbowSocketTCP_GetProtocolFamily(RainbowSocketTCP * socket_tcp)
{
  return socket_tcp->protocol_family;
}

void RainbowSocketTCP_SetProtocolFamily
(
  RainbowSocketTCP * socket_tcp,
  RainbowProtocolFamily protocol_family
)
{
  socket_tcp->protocol_family = protocol_family;
}

RainbowAddressFamily RainbowSocketTCP_GetAddressFamily(RainbowSocketTCP * socket_tcp)
{
  return socket_tcp->address_family;
}

void RainbowSocketTCP_SetAddressFamily
(
  RainbowSocketTCP * socket_tcp,
  RainbowAddressFamily address_family
)
{
  socket_tcp->address_family = address_family;
  socket_tcp->server_address.sa_family = address_family;
}

int RainbowSocketTCP_Connect(RainbowSocketTCP * socket_tcp, const char *address, size_t len)
{
  size_t size = 0;
  switch(socket_tcp->address_family)
  {
    case RainbowAddressFamily_IPv4:
    {
      RainbowSocketAddressIPv4 *server_address = (RainbowSocketAddressIPv4 *)&(socket_tcp->server_address);
      server_address->sin_addr.s_addr = inet_addr(address);
      size = sizeof(RainbowSocketAddressIPv4);
      break;
    }
  }
  int result =
    connect(
      RainbowCall(socket_tcp->file_stream, GetDescriptor),
      (struct sockaddr*)&(socket_tcp->server_address),
      sizeof(socket_tcp->server_address)
    );
  if(result < 0)
  {
    return result;
  }
  RainbowString_Initialize(&(socket_tcp->address_RainbowString), address, len);
  return result;
}

const char *RainbowSocketTCP_GetAddress(RainbowSocketTCP * socket_tcp)
{
  return RainbowString_CStr(&(socket_tcp->address_RainbowString));
}

void RainbowSocketTCP_Destroy(RainbowSocketTCP * socket_tcp)
{
  RainbowString_Destroy(&(socket_tcp->address_RainbowString));
  int descriptor = RainbowCall(socket_tcp->file_stream, GetDescriptor);
  shutdown(descriptor, SHUT_RDWR);
  close(descriptor);
}
