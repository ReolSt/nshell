#include "AirForceSocket.h"

int AirForceSocketTCP_Initialize
(
  AirForceSocketTCP * socket_tcp,
  AirForceProtocolFamily protocol_family,
  AirForceAddressFamily address_family
)
{
  memset(&(socket_tcp->server_address), 0, sizeof(socket_tcp->server_address));
  int socket_descriptor = socket(protocol_family, AirForceSocketType_Stream, 0);
  if(socket_descriptor < 0)
  {
    return socket_descriptor;
  }
  AirForceSocketTCP_SetProtocolFamily(socket_tcp, protocol_family);
  AirForceSocketTCP_SetAddressFamily(socket_tcp, address_family);
  AirForceFileStream_Initialize(&(socket_tcp->file_stream), socket_descriptor, "r+");
//function pointers
  socket_tcp->Initialize = AirForceSocketTCP_Initialize;
  socket_tcp->IsInitialized = AirForceSocketTCP_IsInitialized;
  socket_tcp->GetFileStream = AirForceSocketTCP_GetFileStream;
  socket_tcp->GetPort = AirForceSocketTCP_GetPort;
  socket_tcp->SetPort = AirForceSocketTCP_SetPort;
  socket_tcp->GetProtocolFamily= AirForceSocketTCP_GetProtocolFamily;
  socket_tcp->SetProtocolFamily= AirForceSocketTCP_SetProtocolFamily;
  socket_tcp->Connect = AirForceSocketTCP_Connect;
  socket_tcp->GetAddress = AirForceSocketTCP_GetAddress;
  socket_tcp->Destroy = AirForceSocketTCP_Destroy;
//
  socket_tcp->initialized = 1;
  return socket_descriptor;
}

int AirForceSocketTCP_IsInitialized(AirForceSocketTCP * socket_tcp)
{
  return socket_tcp->initialized;
}
AirForceFileStream * AirForceSocketTCP_GetFileStream(AirForceSocketTCP * socket_tcp)
{
  return &(socket_tcp->file_stream);
}

unsigned int AirForceSocketTCP_GetPort(AirForceSocketTCP * socket_tcp)
{
  return socket_tcp->port_host;
}

void AirForceSocketTCP_SetPort(AirForceSocketTCP * socket_tcp, unsigned int port)
{
  switch(socket_tcp->address_family)
  {
    case AirForceAddressFamily_IPv4:
    {
      AirForceSocketAddressIPv4 *server_address = (AirForceSocketAddressIPv4 *)&(socket_tcp->server_address);
      server_address->sin_port = htons(port);
      break;
    }
  }
}

AirForceProtocolFamily AirForceSocketTCP_GetProtocolFamily(AirForceSocketTCP * socket_tcp)
{
  return socket_tcp->protocol_family;
}

void AirForceSocketTCP_SetProtocolFamily
(
  AirForceSocketTCP * socket_tcp,
  AirForceProtocolFamily protocol_family
)
{
  socket_tcp->protocol_family = protocol_family;
}

AirForceAddressFamily AirForceSocketTCP_GetAddressFamily(AirForceSocketTCP * socket_tcp)
{
  return socket_tcp->address_family;
}

void AirForceSocketTCP_SetAddressFamily
(
  AirForceSocketTCP * socket_tcp,
  AirForceAddressFamily address_family
)
{
  socket_tcp->address_family = address_family;
  socket_tcp->server_address.sa_family = address_family;
}

int AirForceSocketTCP_Connect(AirForceSocketTCP * socket_tcp, const char *address, size_t len)
{
  size_t size = 0;
  switch(socket_tcp->address_family)
  {
    case AirForceAddressFamily_IPv4:
    {
      AirForceSocketAddressIPv4 *server_address = (AirForceSocketAddressIPv4 *)&(socket_tcp->server_address);
      server_address->sin_addr.s_addr = inet_addr(address);
      size = sizeof(AirForceSocketAddressIPv4);
      break;
    }
  }
  int result =
    connect(
      AirForceCall(socket_tcp->file_stream, GetDescriptor),
      (struct sockaddr*)&(socket_tcp->server_address),
      sizeof(socket_tcp->server_address)
    );
  if(result < 0)
  {
    return result;
  }
  AirForceString_Initialize(&(socket_tcp->address_AirForceString), address, len);
  return result;
}

const char *AirForceSocketTCP_GetAddress(AirForceSocketTCP * socket_tcp)
{
  return AirForceString_CStr(&(socket_tcp->address_AirForceString));
}

void AirForceSocketTCP_Destroy(AirForceSocketTCP * socket_tcp)
{
  AirForceString_Destroy(&(socket_tcp->address_AirForceString));
  int descriptor = AirForceCall(socket_tcp->file_stream, GetDescriptor);
  shutdown(descriptor, SHUT_RDWR);
  close(descriptor);
}
