#include "AirForceString.h"

void __AirForceString_ExtendForNullTerminating(AirForceString *string)
{
  if(string->string_vector.size + 2 >= string->string_vector.capacity)
  {
    __AirForceVector_Extend(&(string->string_vector));
  }
}

void AirForceString_Initialize(AirForceString *string, const char *s, size_t length)
{
  AirForceVector_Initialize(&(string->string_vector), sizeof(char));
  for(int i=0;i<length;++i)
  {
  AirForceVector_PushBack(&(string->string_vector), s + i);
  }
  string->size = length;
//function pointers
  string->Initialize = AirForceString_Initialize;
  string->IsInitialized = AirForceString_IsInitialized;
  string->Append = AirForceString_Append;
  string->PushBack = AirForceString_PushBack;
  string->PopBack = AirForceString_PopBack;
  string->Insert = AirForceString_Insert;
  string->Remove = AirForceString_Remove;
  string->Clear = AirForceString_Clear;
  string->Destroy = AirForceString_Destroy;
  string->CStr = AirForceString_CStr;
  string->At = AirForceString_At;
  string->AtPtr = AirForceString_AtPtr;
  string->Front = AirForceString_Front;
  string->Back = AirForceString_Back;
  string->Length =AirForceString_Length;
//
  string->initialized = 1;
}

int AirForceString_IsInitialized(AirForceString *string)
{
  return string->initialized;
}

void AirForceString_Clear(AirForceString *string)
{
  AirForceVector_Clear(&(string->string_vector));
  string->size = 0;
}

void AirForceString_Destroy(AirForceString *string)
{
  string->initialized = 0;
  AirForceVector_Destroy(&(string->string_vector));
  string->size = 0;
}

void AirForceString_PushBack(AirForceString *string, char ch)
{
  AirForceVector_PushBack(&(string->string_vector), &ch);
  string->size += 1;
  __AirForceString_ExtendForNullTerminating(string);
}


void AirForceString_PopBack(AirForceString *string)
{
  if(string->size > 0)
  {
    AirForceVector_PopBack(&(string->string_vector));
    string->size -= 1;
  }
}

void AirForceString_Append(AirForceString *string, const char * s, size_t length)
{
  for(int i = 0; i < length; ++i)
  {
    AirForceString_PushBack(string, s[i]);
  }
}

void AirForceString_Insert(AirForceString *string, int index, char ch)
{
  AirForceVector_Insert(&(string->string_vector), index, &ch);
  string->size += 1;
  __AirForceString_ExtendForNullTerminating(string);
}

void AirForceString_Remove(AirForceString *string, int index)
{
  AirForceVector_Remove(&(string->string_vector), index);
  string->size -= 1;
}

const char *AirForceString_CStr(AirForceString *string)
{
  return (const char*)AirForceVector_At(&(string->string_vector), 0);
}

char AirForceString_At(AirForceString *string, int index)
{
  return *(char*)AirForceVector_At(&(string->string_vector), index);
}

char *AirForceString_AtPtr(AirForceString *string, int index)
{
  return (char*)AirForceVector_At(&(string->string_vector), index);
}

char AirForceString_Front(AirForceString *string)
{
  return *(char*)AirForceVector_Front(&(string->string_vector));
}

char AirForceString_Back(AirForceString *string)
{
  return *(char*)AirForceVector_Back(&(string->string_vector));
}

int AirForceString_Length(AirForceString *string)
{
  return string->size;
}

//for test
// #include <stdio.h>
// #include "AirForceCall.h"
// int main()
// {
//   AirForceString string;
//   AirForceString_Initialize(&string, "Testasdf", 8);
//   string.Remove(&string, 4);
//   printf("%s\n",string.CStr(&string));
//   printf("%c\n",string.At(&string, 1));
//   string.Append(&string, 'a');
//   string.Append(&string, 'b');
//   AirForceCall(string, Insert, 2, 'd');
//   // string.Insert(&string, 2, 'd');
//   printf("%s\n",string.CStr(&string));
// }
