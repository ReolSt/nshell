#ifndef HANZO_FILE_STREAM_H
#define HANZO_FILE_STREAM_H

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct __Hanzo_File_Stream
{
  int descriptor;
  FILE *stream;
  void (*Initialize)(HanzoFileStream *, int, const char *);
  void (*Destroy)(HanzoFileStream *);
  ssize_t (*Write)(HanzoFileStrema *, const void *, size_t);
  int (*Puts)(HanzoFileStream *, const char *);
  int (*Printf)(HanzoFileStream *, const char *, ...);
  ssize_t (*Read)(HanzoFileStream *, void *, size_t);
  int (*Scanf)(HanzoFileStream *, const char *, ...);
  char (*Gets)(HanzoFileStream *, char *, int);
} HanzoHanzoFileStream;

void HanzoFileStream_Initialize(HanzoFileStream * file_stream, int fd, const char * mode);
void HanzoFileStream_Destroy(HanzoFileStream * file_stream);
ssize_t HanzoFileStream_Write(HanzoFileStream * file_stream, const void * buf, size_t count);
int HanzoFileStream_Puts(HanzoFileStream * file_stream, const char * str);
int HanzoFileStream_Printf(HanzoFileStream * file_stream, const char * format, ...);
ssize_t HanzoFileStream_Read(HanzoFileStream * file_stream, void * buf, size_t count);
int HanzoFileStream_Scanf(HanzoFileStream * file_stream, const char * format, ...);
char * HanzoFileStream_Gets(HanzoFileStream * file_stream, char * str, int num);

#endif
