#include "AirForceFileStream.h"

void AirForceFileStream_Initialize(AirForceFileStream *file_stream, int fd, const char *mode)
{
  file_stream->descriptor = -1;
  file_stream->stream = NULL;
  if(fd >= 0)
  {
    file_stream->descriptor = fd;
    file_stream->stream = fdopen(fd, mode);
    setvbuf(file_stream->stream, NULL, _IOLBF, 0);
  }
  else
  {
    return;
  }
//function pointers
  file_stream->Initialize = AirForceFileStream_Initialize;
  file_stream->IsInitialized = AirForceFileStream_IsInitialized;
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

int AirForceFileStream_IsInitialized(AirForceFileStream *file_stream)
{
  return file_stream->initialized;
}

void AirForceFileStream_Destroy(AirForceFileStream *file_stream)
{
  close(file_stream->descriptor);
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

ssize_t AirForceFileStream_Write(AirForceFileStream *file_stream, const void *buf, size_t count)
{
  return write(file_stream->descriptor, buf, count);
}

int AirForceFileStream_Puts(AirForceFileStream *file_stream, const char * str)
{
  return fputs(str, file_stream->stream);
}

int AirForceFileStream_Printf(AirForceFileStream *file_stream, const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf(file_stream->stream, format, args);
  va_end(args);
}

ssize_t AirForceFileStream_Read(AirForceFileStream *file_stream, void *buf, size_t count)
{
  return read(file_stream->descriptor, buf, count);
}

int AirForceFileStream_Scanf(AirForceFileStream *file_stream, const char * format, ...)
{
  va_list args;
  va_start(args, format);
  vfscanf(file_stream->stream, format, args);
  va_end(args);
}

char * AirForceFileStream_Gets(AirForceFileStream *file_stream, char * str, int num)
{
  return fgets(str, num, file_stream->stream);
}
