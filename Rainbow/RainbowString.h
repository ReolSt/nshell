#ifndef HANZO_STRING_H
#define HANZO_STRING_H
#include "RainbowVector.h"
typedef struct __Rainbow_String
{
  int initialized;
  RainbowVector string_vector;
  size_t size;
  void (*Initialize)(struct __Rainbow_String *, const char *s, size_t);
  int (*IsInitialized)(struct __Rainbow_String *);
  void (*Clear)(struct __Rainbow_String *);
  void (*Destroy)(struct __Rainbow_String *);
  void (*Append)(struct __Rainbow_String *, const char);
  void (*Pop)(struct __Rainbow_String *);
  void (*Insert)(struct __Rainbow_String *, int, const char);
  void (*Remove)(struct __Rainbow_String *, int);
  const char * (*CStr)(struct __Rainbow_String *);
  char (*At)(struct __Rainbow_String *, int);
  char * (*AtPtr)(struct __Rainbow_String *, int);
  char (*Front)(struct __Rainbow_String *);
  char (*Back)(struct __Rainbow_String *);
  int (*Length)(struct __Rainbow_String *);
} RainbowString;

void __RainbowString_ExtendForNullTerminating(RainbowString *rainbow_string);
void RainbowString_Initialize(RainbowString *rainbow_string, const char *s, size_t length);
int RainbowString_IsInitialized(RainbowString *rainbow_string);
void RainbowString_Clear(RainbowString *rainbow_string);
void RainbowString_Destroy(RainbowString *rainbow_string);
void RainbowString_Append(RainbowString *rainbow_string, char ch);
void RainbowString_Pop(RainbowString *rainbow_string);
void RainbowString_Insert(RainbowString *rainbow_string, int index,  char ch);
void RainbowString_Remove(RainbowString *rainbow_string, int index);
const char *RainbowString_CStr(RainbowString *rainbow_string);
char RainbowString_At(RainbowString *rainbow_string, int index);
char *RainbowString_AtPtr(RainbowString *rainbow_string, int index);
char RainbowString_Front(RainbowString *rainbow_string);
char RainbowString_Back(RainbowString *rainbow_string);
int RainbowString_Length(RainbowString *rainbow_string);
#endif
