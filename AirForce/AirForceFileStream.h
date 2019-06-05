#ifndef AIRFORCE_FILE_STREAM_H
#define AIRFORCE_FILE_STREAM_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>

#include "AirForceCall.h"

typedef struct __AirForce_File_Stream
{
  int initialized;
  int descriptor;
  FILE *stream;

  void (*Initialize)(struct __AirForce_File_Stream *);
  int (*IsInitialized)(struct __AirForce_File_Stream *);
  int (*Open)(struct __AirForce_File_Stream *, const char *, int);
  int (*Close)(struct __AirForce_File_Stream *);
  FILE * (*FOpen)(struct __AirForce_File_Stream *,const char *, const char *);
  FILE * (*FDOpen)(struct __AirForce_File_Stream *, int fd, const char * mode);
  FILE * (*FReOpen)(struct __AirForce_File_Stream *, const char *, const char *);
  int (*FClose)(struct __AirForce_File_Stream *);
  int (*SetVBuf)(struct __AirForce_File_Stream *, char * buffer, int mode, size_t size);
  void (*Destroy)(struct __AirForce_File_Stream *);
  int (*GetDescriptor)(struct __AirForce_File_Stream *);
  FILE * (*GetStream)(struct __AirForce_File_Stream *);
  ssize_t (*Write)(struct __AirForce_File_Stream *, const void *, size_t);
  int (*Puts)(struct __AirForce_File_Stream *, const char *);
  int (*Printf)(struct __AirForce_File_Stream *, const char *, ...);
  ssize_t (*Read)(struct __AirForce_File_Stream *, void *, size_t);
  int (*Scanf)(struct __AirForce_File_Stream *, const char *, ...);
  char * (*Gets)(struct __AirForce_File_Stream *, char *, int);
} AirForceFileStream;

void AirForceFileStream_Initialize(AirForceFileStream * file_stream);
int AirForceFileStream_IsInitialized(AirForceFileStream * file_stream);
int AirForceFileStream_Open(AirForceFileStream * file_stream, const char * pathname, int flags);
int AirForceFileStream_Close(AirForceFileStream * file_stream);
FILE * AirForceFileStream_FOpen(AirForceFileStream * file_stream, const char * filename, const char * mode);
FILE * AirForceFileStream_FDOpen(AirForceFileStream * file_stream, int fd, const char * mode);
FILE * AirForceFileStream_FReOpen(AirForceFileStream * file_stream, const char * path, const char *mode);
int AirForceFileStream_FClose(AirForceFileStream * file_stream);
int AirForceFileStream_SetVBuf(AirForceFileStream * file_stream, char * buffer, int mode, size_t size);
void AirForceFileStream_Destroy(AirForceFileStream * file_stream);
int AirForceFileStream_GetDescriptor(AirForceFileStream * file_stream);
FILE * AirForceFileStream_GetStream(AirForceFileStream * file_stream);
ssize_t AirForceFileStream_Write(AirForceFileStream * file_stream, const void * buf, size_t count);
int AirForceFileStream_Puts(AirForceFileStream * file_stream, const char * str);
int AirForceFileStream_Printf(AirForceFileStream * file_stream, const char * format, ...);
ssize_t AirForceFileStream_Read(AirForceFileStream * file_stream, void * buf, size_t count);
int AirForceFileStream_Scanf(AirForceFileStream * file_stream, const char * format, ...);
char * AirForceFileStream_Gets(AirForceFileStream * file_stream, char * str, int num);

#endif
