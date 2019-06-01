#ifndef HANZO_STRING_H
#define HANZO_STRING_H
#include "HanzoVector.h"
typedef struct __Hanzo_String
{
  int initialized;
  HanzoVector string_vector;
  size_t size;
  void (*Initialize)(struct __Hanzo_String *, const char *s, size_t);
  int (*IsInitialized)(struct __Hanzo_String *);
  void (*Clear)(struct __Hanzo_String *);
  void (*Destroy)(struct __Hanzo_String *);
  void (*Append)(struct __Hanzo_String *, const char);
  void (*Pop)(struct __Hanzo_String *);
  void (*Insert)(struct __Hanzo_String *, int, const char);
  void (*Remove)(struct __Hanzo_String *, int);
  const char * (*CStr)(struct __Hanzo_String *);
  char (*At)(struct __Hanzo_String *, int);
  char * (*AtPtr)(struct __Hanzo_String *, int);
  char (*Front)(struct __Hanzo_String *);
  char (*Back)(struct __Hanzo_String *);
  int (*Length)(struct __Hanzo_String *);
} HanzoString;

void __HanzoString_ExtendForNullTerminating(HanzoString *hanzo_string);
void HanzoString_Initialize(HanzoString *hanzo_string, const char *s, size_t length);
int HanzoString_IsInitialized(HanzoString *hanzo_string);
void HanzoString_Clear(HanzoString *hanzo_string);
void HanzoString_Destroy(HanzoString *hanzo_string);
void HanzoString_Append(HanzoString *hanzo_string, char ch);
void HanzoString_Pop(HanzoString *hanzo_string);
void HanzoString_Insert(HanzoString *hanzo_string, int index,  char ch);
void HanzoString_Remove(HanzoString *hanzo_string, int index);
const char *HanzoString_CStr(HanzoString *hanzo_string);
char HanzoString_At(HanzoString *hanzo_string, int index);
char *HanzoString_AtPtr(HanzoString *hanzo_string, int index);
char HanzoString_Front(HanzoString *hanzo_string);
char HanzoString_Back(HanzoString *hanzo_string);
int HanzoString_Length(HanzoString *hanzo_string);
#endif
