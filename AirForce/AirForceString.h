#ifndef AIRFORCE_STRING_H
#define AIRFORCE_STRING_H

#include "AirForceCall.h"
#include "AirForceVector.h"

typedef struct __AirForce_String
{
  int initialized;
  AirForceVector string_vector;
  size_t size;

  void (*Initialize)(struct __AirForce_String *, const char *s, size_t);
  int (*IsInitialized)(struct __AirForce_String *);
  void (*Clear)(struct __AirForce_String *);
  void (*Destroy)(struct __AirForce_String *);
  void (*Append)(struct __AirForce_String *, const char *, size_t);
  void (*PushBack)(struct __AirForce_String *, char);
  void (*PopBack)(struct __AirForce_String *);
  void (*Insert)(struct __AirForce_String *, int, const char);
  void (*Remove)(struct __AirForce_String *, int);
  const char * (*CStr)(struct __AirForce_String *);
  char (*At)(struct __AirForce_String *, int);
  char * (*AtPtr)(struct __AirForce_String *, int);
  char (*Front)(struct __AirForce_String *);
  char (*Back)(struct __AirForce_String *);
  int (*Length)(struct __AirForce_String *);
} AirForceString;

void __AirForceString_ExtendForNullTerminating(AirForceString * string);
void AirForceString_Initialize(AirForceString * string, const char * s, size_t length);
int AirForceString_IsInitialized(AirForceString * string);
void AirForceString_Clear(AirForceString * string);
void AirForceString_Destroy(AirForceString * string);
void AirForceString_PushBack(AirForceString * string, char ch);
void AirForceString_PopBack(AirForceString * string);
void AirForceString_Append(AirForceString * string, const char * s, size_t length);
void AirForceString_Insert(AirForceString * string, int index,  char ch);
void AirForceString_Remove(AirForceString * string, int index);
const char * AirForceString_CStr(AirForceString * string);
char AirForceString_At(AirForceString * string, int index);
char * AirForceString_AtPtr(AirForceString * string, int index);
char AirForceString_Front(AirForceString * string);
char AirForceString_Back(AirForceString * string);
int AirForceString_Length(AirForceString * string);
#endif
