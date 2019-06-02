#ifndef RAINBOW_FILE_STREAM_H
#define RAINBOW_FILE_STREAM_H

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

#include "RainbowCall.h"

typedef struct __Rainbow_File_Stream
{
  int initialized;
  int descriptor;
  FILE *stream;

  void (*Initialize)(struct __Rainbow_File_Stream *, int, const char *);
  int (*IsInitialized)(struct __Rainbow_File_Stream *);
  void (*Destroy)(struct __Rainbow_File_Stream *);
  int (*GetDescriptor)(struct __Rainbow_File_Stream *);
  FILE * (*GetStream)(struct __Rainbow_File_Stream *);
  ssize_t (*Write)(struct __Rainbow_File_Stream *, const void *, size_t);
  int (*Puts)(struct __Rainbow_File_Stream *, const char *);
  int (*Printf)(struct __Rainbow_File_Stream *, const char *, ...);
  ssize_t (*Read)(struct __Rainbow_File_Stream *, void *, size_t);
  int (*Scanf)(struct __Rainbow_File_Stream *, const char *, ...);
  char * (*Gets)(struct __Rainbow_File_Stream *, char *, int);
} RainbowFileStream;

void RainbowFileStream_Initialize(RainbowFileStream * file_stream, int fd, const char * mode);
int RainbowFileStream_IsInitialized(RainbowFileStream * file_stream);
void RainbowFileStream_Destroy(RainbowFileStream * file_stream);
int RainbowFileStream_GetDescriptor(RainbowFileStream * file_stream);
FILE * RainbowFileStream_GetStream(RainbowFileStream * file_stream);
ssize_t RainbowFileStream_Write(RainbowFileStream * file_stream, const void * buf, size_t count);
int RainbowFileStream_Puts(RainbowFileStream * file_stream, const char * str);
int RainbowFileStream_Printf(RainbowFileStream * file_stream, const char * format, ...);
ssize_t RainbowFileStream_Read(RainbowFileStream * file_stream, void * buf, size_t count);
int RainbowFileStream_Scanf(RainbowFileStream * file_stream, const char * format, ...);
char * RainbowFileStream_Gets(RainbowFileStream * file_stream, char * str, int num);

#endif