#include "HanzoString.h"

void __HanzoString_ExtendForNullTerminating(HanzoString *hanzo_string)
{
  if(hanzo_string->string_vector.size + 2 >= hanzo_string->string_vector.capacity)
  {
    __HanzoVector_Extend(&(hanzo_string->string_vector));
  }
}

void HanzoString_Initialize(HanzoString *hanzo_string, const char *s, size_t length)
{
  HanzoVector_Initialize(&(hanzo_string->string_vector), sizeof(char));
  for(int i=0;i<length;++i)
  {
  HanzoVector_PushBack(&(hanzo_string->string_vector), s + i);
  }
  hanzo_string->size = length;
  hanzo_string->initialized = 1;
//function pointers
  hanzo_string->Initialize = HanzoString_Initialize;
  hanzo_string->IsInitialized = HanzoString_IsInitialized;
  hanzo_string->Append = HanzoString_Append;
  hanzo_string->Pop = HanzoString_Pop;
  hanzo_string->Insert = HanzoString_Insert;
  hanzo_string->Remove = HanzoString_Remove;
  hanzo_string->Clear = HanzoString_Clear;
  hanzo_string->Destroy = HanzoString_Destroy;
  hanzo_string->CStr = HanzoString_CStr;
  hanzo_string->At = HanzoString_At;
  hanzo_string->AtPtr = HanzoString_AtPtr;
  hanzo_string->Front = HanzoString_Front;
  hanzo_string->Back = HanzoString_Back;
  hanzo_string->Length =HanzoString_Length;
}

int HanzoString_IsInitialized(HanzoString *hanzo_string)
{
  return hanzo_string->initialized;
}

void HanzoString_Clear(HanzoString *hanzo_string)
{
  HanzoVector_Clear(&(hanzo_string->string_vector));
  hanzo_string->size = 0;
}

void HanzoString_Destroy(HanzoString *hanzo_string)
{
  hanzo_string->initialized = 0;
  HanzoVector_Destroy(&(hanzo_string->string_vector));
  hanzo_string->size = 0;
}

void HanzoString_Append(HanzoString *hanzo_string, char ch)
{
  HanzoVector_PushBack(&(hanzo_string->string_vector), &ch);
  hanzo_string->size += 1;
  __HanzoString_ExtendForNullTerminating(hanzo_string);
}

void HanzoString_Pop(HanzoString *hanzo_string)
{
  if(hanzo_string->size > 0)
  {
    HanzoVector_PopBack(&(hanzo_string->string_vector));
    hanzo_string->size -= 1;
  }
}

void HanzoString_Insert(HanzoString *hanzo_string, int index, char ch)
{
  HanzoVector_Insert(&(hanzo_string->string_vector), index, &ch);
  hanzo_string->size += 1;
  __HanzoString_ExtendForNullTerminating(hanzo_string);
}

void HanzoString_Remove(HanzoString *hanzo_string, int index)
{
  HanzoVector_Remove(&(hanzo_string->string_vector), index);
  hanzo_string->size -= 1;
}

const char *HanzoString_CStr(HanzoString *hanzo_string)
{
  return (const char*)HanzoVector_At(&(hanzo_string->string_vector), 0);
}

char HanzoString_At(HanzoString *hanzo_string, int index)
{
  return *(char*)HanzoVector_At(&(hanzo_string->string_vector), index);
}

char *HanzoString_AtPtr(HanzoString *hanzo_string, int index)
{
  return (char*)HanzoVector_At(&(hanzo_string->string_vector), index);
}

char HanzoString_Front(HanzoString *hanzo_string)
{
  return *(char*)HanzoVector_Front(&(hanzo_string->string_vector));
}

char HanzoString_Back(HanzoString *hanzo_string)
{
  return *(char*)HanzoVector_Back(&(hanzo_string->string_vector));
}

int HanzoString_Length(HanzoString *hanzo_string)
{
  return hanzo_string->size;
}

//for test
#include <stdio.h>
#include "HanzoCall.h"
int main()
{
  HanzoString string;
  HanzoString_Initialize(&string, "Testasdf", 8);
  string.Remove(&string, 4);
  printf("%s\n",string.CStr(&string));
  printf("%c\n",string.At(&string, 1));
  string.Append(&string, 'a');
  string.Append(&string, 'b');
  HanzoCall(string, Insert, 2, 'd');
  // string.Insert(&string, 2, 'd');
  printf("%s\n",string.CStr(&string));
}
