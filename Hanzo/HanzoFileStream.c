#include "HanzoFileStream.h"

void HanzoFileStream_Initialize(HanzoFileStream *file_stream, int fd, const char *mode)
{
  file_stream->desciptor = -1;
  file_stream->stream = NULL;
  if(fd >= 0)
  {
    file_stream->stream = fdopen(fd, mode);
  }
  else
  {
    return;
  }
  file_stream->Initialize = HanzoFileStream_Initialize;
  file_stream->Destroy = HanzoFileStream_Destroy;
  file_stream->Write = HanzoFileStream_Write;
  file_stream->Puts = HanzoFileStream_Puts;
  file_stream->Printf = HanzoFileStream_Printf;
  file_stream->Read = HanzoFileStream_Read;
  file_stream->Gets = HanzoFileStream_Gets;
  file_stream->Scanf = HanzoFileStream_Scanf;
}

void HanzoFileStream_Destroy(HanzoFileStream *file_stream)
{
  close(file_descriptor);
  file_stream->descriptor = -1;
  file_stream->stream = NULL;
}

ssize_t HanzoFileStream_Write(HanzoFileStream *file_stream, const void *buf, size_t count)
{
  return write(file_stream->descriptor, buf, count);
}

int HanzoFileStream_Puts(HanzoFileStream *file_stream, const char * str)
{
  return fputs(str, file_stream->stream);
}

int HanzoFileStream_Printf(HanzoFileStream *file_stream, const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf(file_stream->stream, format, args);
  va_end(args);
}

ssize_t HanzoFileStream_Read(HanzoFileStream *file_stream, void *buf, size_t count)
{
  return read(file_stream->descriptor, buf, count);
}

int HanzoFileStream_Scanf(HanzoFileStream *file_stream, const char * format, ...)
{
  va_list args;
  va_start(args, format);
  vfscanf(file_stream->stream, format, args);
  va_end(args);
}

char * HanzoFileStream_Gets(HanzoFileStream *file_stream, char * str, int num)
{
  return fgets(str, num, file_stream->stream);
}
