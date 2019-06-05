#include "AirForceFileStream.h"

void AirForceFileStream_Initialize(AirForceFileStream * file_stream)
{
  file_stream->descriptor = -1;
  file_stream->stream = NULL;
//function pointers
  file_stream->Initialize = AirForceFileStream_Initialize;
  file_stream->IsInitialized = AirForceFileStream_IsInitialized;
  file_stream->Open = AirForceFileStream_Open;
  file_stream->Close = AirForceFileStream_Close;
  file_stream->FOpen = AirForceFileStream_FOpen;
  file_stream->FDOpen = AirForceFileStream_FDOpen;
  file_stream->FReOpen = AirForceFileStream_FReOpen;
  file_stream->FClose = AirForceFileStream_FClose;
  file_stream->SetVBuf = AirForceFileStream_SetVBuf;
  file_stream->Destroy = AirForceFileStream_Destroy;
  file_stream->GetDescriptor = AirForceFileStream_GetDescriptor;
  file_stream->GetStream = AirForceFileStream_GetStream;
  file_stream->Write = AirForceFileStream_Write;
  file_stream->Puts = AirForceFileStream_Puts;
  file_stream->Printf = AirForceFileStream_Printf;
  file_stream->Read = AirForceFileStream_Read;
  file_stream->Gets = AirForceFileStream_Gets;
  file_stream->Scanf = AirForceFileStream_Scanf;
//
  file_stream->initialized = 1;
}

int AirForceFileStream_Open(AirForceFileStream * file_stream, const char * pathname, int flags)
{
  file_stream->descriptor = open(pathname, flags);
  file_stream->stream = fdopen(file_stream->descriptor, "r+");
  return file_stream->descriptor;
}

int AirForceFileStream_Close(AirForceFileStream * file_stream)
{
  return close(file_stream->descriptor);
}

FILE * AirForceFileStream_FOpen(AirForceFileStream * file_stream, const char * filename, const char * mode)
{
  file_stream->stream = fopen(filename, mode);
  return file_stream->stream;
}

FILE * AirForceFileStream_FDOpen(AirForceFileStream * file_stream, int fd, const char * mode)
{
  file_stream->descriptor = fd;
  file_stream->stream = fdopen(fd, mode);
  return file_stream->stream;
}

FILE * AirForceFileStream_FReOpen(AirForceFileStream * file_stream, const char * path, const char *mode)
{
  return freopen(path, mode, file_stream->stream);
}

int AirForceFileStream_FClose(AirForceFileStream * file_stream)
{
  return fclose(file_stream->stream);
}

int AirForceFileStream_SetVBuf(AirForceFileStream * file_stream, char * buffer, int mode, size_t size)
{
  return setvbuf(file_stream->stream, buffer, mode, size);
}

int AirForceFileStream_IsInitialized(AirForceFileStream * file_stream)
{
  return file_stream->initialized;
}

void AirForceFileStream_Destroy(AirForceFileStream * file_stream)
{
  close(file_stream->descriptor);
  fclose(file_stream->stream);
  file_stream->descriptor = -1;
  file_stream->stream = NULL;
}

int AirForceFileStream_GetDescriptor(AirForceFileStream * file_stream)
{
  return file_stream->descriptor;
}

FILE * AirForceFileStream_GetStream(AirForceFileStream * file_stream)
{
  return file_stream->stream;
}

ssize_t AirForceFileStream_Write(AirForceFileStream * file_stream, const void *buf, size_t count)
{
  return write(file_stream->descriptor, buf, count);
}

int AirForceFileStream_Puts(AirForceFileStream * file_stream, const char * str)
{
  return fputs(str, file_stream->stream);
}

int AirForceFileStream_Printf(AirForceFileStream * file_stream, const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf(file_stream->stream, format, args);
  va_end(args);
}

ssize_t AirForceFileStream_Read(AirForceFileStream * file_stream, void *buf, size_t count)
{
  return read(file_stream->descriptor, buf, count);
}

int AirForceFileStream_Scanf(AirForceFileStream * file_stream, const char * format, ...)
{
  va_list args;
  va_start(args, format);
  vfscanf(file_stream->stream, format, args);
  va_end(args);
}

char * AirForceFileStream_Gets(AirForceFileStream * file_stream, char * str, int num)
{
  return fgets(str, num, file_stream->stream);
}
