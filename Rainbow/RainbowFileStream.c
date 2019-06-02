#include "RainbowFileStream.h"

void RainbowFileStream_Initialize(RainbowFileStream *file_stream, int fd, const char *mode)
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
  file_stream->Initialize = RainbowFileStream_Initialize;
  file_stream->IsInitialized = RainbowFileStream_IsInitialized;
  file_stream->Destroy = RainbowFileStream_Destroy;
  file_stream->GetDescriptor = RainbowFileStream_GetDescriptor;
  file_stream->GetStream = RainbowFileStream_GetStream;
  file_stream->Write = RainbowFileStream_Write;
  file_stream->Puts = RainbowFileStream_Puts;
  file_stream->Printf = RainbowFileStream_Printf;
  file_stream->Read = RainbowFileStream_Read;
  file_stream->Gets = RainbowFileStream_Gets;
  file_stream->Scanf = RainbowFileStream_Scanf;
//
  file_stream->initialized = 1;
}

int RainbowFileStream_IsInitialized(RainbowFileStream *file_stream)
{
  return file_stream->initialized;
}

void RainbowFileStream_Destroy(RainbowFileStream *file_stream)
{
  close(file_stream->descriptor);
  file_stream->descriptor = -1;
  file_stream->stream = NULL;
}

int RainbowFileStream_GetDescriptor(RainbowFileStream * file_stream)
{
  return file_stream->descriptor;
}

FILE * RainbowFileStream_GetStream(RainbowFileStream * file_stream)
{
  return file_stream->stream;
}

ssize_t RainbowFileStream_Write(RainbowFileStream *file_stream, const void *buf, size_t count)
{
  return write(file_stream->descriptor, buf, count);
}

int RainbowFileStream_Puts(RainbowFileStream *file_stream, const char * str)
{
  return fputs(str, file_stream->stream);
}

int RainbowFileStream_Printf(RainbowFileStream *file_stream, const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf(file_stream->stream, format, args);
  va_end(args);
}

ssize_t RainbowFileStream_Read(RainbowFileStream *file_stream, void *buf, size_t count)
{
  return read(file_stream->descriptor, buf, count);
}

int RainbowFileStream_Scanf(RainbowFileStream *file_stream, const char * format, ...)
{
  va_list args;
  va_start(args, format);
  vfscanf(file_stream->stream, format, args);
  va_end(args);
}

char * RainbowFileStream_Gets(RainbowFileStream *file_stream, char * str, int num)
{
  return fgets(str, num, file_stream->stream);
}
