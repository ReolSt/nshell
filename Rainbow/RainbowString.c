#include "RainbowString.h"

void __RainbowString_ExtendForNullTerminating(RainbowString *rainbow_string)
{
  if(rainbow_string->string_vector.size + 2 >= rainbow_string->string_vector.capacity)
  {
    __RainbowVector_Extend(&(rainbow_string->string_vector));
  }
}

void RainbowString_Initialize(RainbowString *rainbow_string, const char *s, size_t length)
{
  RainbowVector_Initialize(&(rainbow_string->string_vector), sizeof(char));
  for(int i=0;i<length;++i)
  {
  RainbowVector_PushBack(&(rainbow_string->string_vector), s + i);
  }
  rainbow_string->size = length;
  rainbow_string->initialized = 1;
//function pointers
  rainbow_string->Initialize = RainbowString_Initialize;
  rainbow_string->IsInitialized = RainbowString_IsInitialized;
  rainbow_string->Append = RainbowString_Append;
  rainbow_string->Pop = RainbowString_Pop;
  rainbow_string->Insert = RainbowString_Insert;
  rainbow_string->Remove = RainbowString_Remove;
  rainbow_string->Clear = RainbowString_Clear;
  rainbow_string->Destroy = RainbowString_Destroy;
  rainbow_string->CStr = RainbowString_CStr;
  rainbow_string->At = RainbowString_At;
  rainbow_string->AtPtr = RainbowString_AtPtr;
  rainbow_string->Front = RainbowString_Front;
  rainbow_string->Back = RainbowString_Back;
  rainbow_string->Length =RainbowString_Length;
}

int RainbowString_IsInitialized(RainbowString *rainbow_string)
{
  return rainbow_string->initialized;
}

void RainbowString_Clear(RainbowString *rainbow_string)
{
  RainbowVector_Clear(&(rainbow_string->string_vector));
  rainbow_string->size = 0;
}

void RainbowString_Destroy(RainbowString *rainbow_string)
{
  rainbow_string->initialized = 0;
  RainbowVector_Destroy(&(rainbow_string->string_vector));
  rainbow_string->size = 0;
}

void RainbowString_Append(RainbowString *rainbow_string, char ch)
{
  RainbowVector_PushBack(&(rainbow_string->string_vector), &ch);
  rainbow_string->size += 1;
  __RainbowString_ExtendForNullTerminating(rainbow_string);
}

void RainbowString_Pop(RainbowString *rainbow_string)
{
  if(rainbow_string->size > 0)
  {
    RainbowVector_PopBack(&(rainbow_string->string_vector));
    rainbow_string->size -= 1;
  }
}

void RainbowString_Insert(RainbowString *rainbow_string, int index, char ch)
{
  RainbowVector_Insert(&(rainbow_string->string_vector), index, &ch);
  rainbow_string->size += 1;
  __RainbowString_ExtendForNullTerminating(rainbow_string);
}

void RainbowString_Remove(RainbowString *rainbow_string, int index)
{
  RainbowVector_Remove(&(rainbow_string->string_vector), index);
  rainbow_string->size -= 1;
}

const char *RainbowString_CStr(RainbowString *rainbow_string)
{
  return (const char*)RainbowVector_At(&(rainbow_string->string_vector), 0);
}

char RainbowString_At(RainbowString *rainbow_string, int index)
{
  return *(char*)RainbowVector_At(&(rainbow_string->string_vector), index);
}

char *RainbowString_AtPtr(RainbowString *rainbow_string, int index)
{
  return (char*)RainbowVector_At(&(rainbow_string->string_vector), index);
}

char RainbowString_Front(RainbowString *rainbow_string)
{
  return *(char*)RainbowVector_Front(&(rainbow_string->string_vector));
}

char RainbowString_Back(RainbowString *rainbow_string)
{
  return *(char*)RainbowVector_Back(&(rainbow_string->string_vector));
}

int RainbowString_Length(RainbowString *rainbow_string)
{
  return rainbow_string->size;
}

//for test
// #include <stdio.h>
// #include "RainbowCall.h"
// int main()
// {
//   RainbowString string;
//   RainbowString_Initialize(&string, "Testasdf", 8);
//   string.Remove(&string, 4);
//   printf("%s\n",string.CStr(&string));
//   printf("%c\n",string.At(&string, 1));
//   string.Append(&string, 'a');
//   string.Append(&string, 'b');
//   RainbowCall(string, Insert, 2, 'd');
//   // string.Insert(&string, 2, 'd');
//   printf("%s\n",string.CStr(&string));
// }
