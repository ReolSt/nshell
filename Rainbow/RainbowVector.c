#include "RainbowVector.h"

#ifndef max
#define max(a,b) (((a) (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif


void __RainbowVector_Extend(RainbowVector *rainbow_vector)
{
  if(rainbow_vector->array!=NULL)
  {
    void *newarray = calloc(rainbow_vector->capacity * 2, rainbow_vector->unitsize);
    rainbow_vector->capacity*=2;
    memcpy(newarray, rainbow_vector->array, rainbow_vector->size * rainbow_vector->unitsize);
    free(rainbow_vector->array);
    rainbow_vector->array = newarray;
  }
}

void __RainbowVector_RShift(RainbowVector *rainbow_vector, int index)
{
  if(rainbow_vector->size > 0 && index >= 0 && index < rainbow_vector->size)
  {
    rainbow_vector->size += 1;
    if(rainbow_vector->size > rainbow_vector->capacity)
    {
      __RainbowVector_Extend(rainbow_vector);
    }
    memmove((char*)rainbow_vector->array + (index + 1) * rainbow_vector->unitsize,
            (char*)rainbow_vector->array + index * rainbow_vector->unitsize,
            (rainbow_vector->size - index) * rainbow_vector->unitsize);
  }
}

void __RainbowVector_LShift(RainbowVector *rainbow_vector, int index)
{
  if(index>=0 && index < rainbow_vector->size)
  {
    memmove((char*)rainbow_vector->array + index * rainbow_vector->unitsize,
            (char*)rainbow_vector->array + (index + 1) * rainbow_vector->unitsize,
            (rainbow_vector->size - index) * rainbow_vector->unitsize);
    rainbow_vector->size -= 1;
  }
}

void RainbowVector_Initialize(RainbowVector *rainbow_vector, size_t unitsize)
{
  rainbow_vector->initialized = 1;
  rainbow_vector->unitsize = unitsize;
  rainbow_vector->size = 0;
  rainbow_vector->capacity = HANZO_VECTOR_DEFAULT_CAPACITY;
  rainbow_vector->array = calloc(rainbow_vector->capacity, rainbow_vector->unitsize);
//function pointers
  rainbow_vector->Initialize = RainbowVector_Initialize;
  rainbow_vector->IsInitialized = RainbowVector_IsInitialized;
  rainbow_vector->Clear = RainbowVector_Clear;
  rainbow_vector->Destroy = RainbowVector_Destroy;
  rainbow_vector->Shrink = RainbowVector_Shrink;
  rainbow_vector->Resize = RainbowVector_Resize;
  rainbow_vector->Insert = RainbowVector_Insert;
  rainbow_vector->Remove = RainbowVector_Remove;
  rainbow_vector->At = RainbowVector_At;
  rainbow_vector->Front = RainbowVector_Front;
  rainbow_vector->Back = RainbowVector_Back;
  rainbow_vector->Size = RainbowVector_Size;
  rainbow_vector->Capacity = RainbowVector_Capacity;
  rainbow_vector->PushBack = RainbowVector_PushBack;
  rainbow_vector->PopBack = RainbowVector_PopBack;
}

int RainbowVector_IsInitialized(RainbowVector *rainbow_vector)
{
  return rainbow_vector->initialized;
}

void RainbowVector_Clear(RainbowVector *rainbow_vector)
{
  free(rainbow_vector->array);
  RainbowVector_Initialize(rainbow_vector, rainbow_vector->unitsize);
}

void RainbowVector_Destroy(RainbowVector *rainbow_vector)
{
  rainbow_vector->initialized = 0;
  rainbow_vector->size = 0;
  rainbow_vector->capacity = 0;
  free(rainbow_vector->array);
  rainbow_vector->array = NULL;
}

void RainbowVector_Shrink(RainbowVector *rainbow_vector)
{
  if(rainbow_vector->capacity > HANZO_VECTOR_DEFAULT_CAPACITY)
  {
    RainbowVector_Resize(rainbow_vector, rainbow_vector->size + 1);
  }
}

void RainbowVector_Resize(RainbowVector *rainbow_vector, size_t size)
{
  rainbow_vector->capacity = size;
  void* resized_array = malloc(rainbow_vector->capacity * rainbow_vector->unitsize);
  memcpy(resized_array, rainbow_vector->array, rainbow_vector->capacity * rainbow_vector->unitsize);
  free(rainbow_vector->array);
  rainbow_vector->array = resized_array;
  rainbow_vector->size = min(rainbow_vector->size, rainbow_vector->capacity);
}

void RainbowVector_Insert(RainbowVector *rainbow_vector, int index, const void *x)
{
  if(index >= 0 && index < rainbow_vector->size)
  {
    __RainbowVector_RShift(rainbow_vector, index);
    memcpy((char*)rainbow_vector->array + index * rainbow_vector->unitsize, x, rainbow_vector->unitsize);
  }
  else if(index == rainbow_vector->size)
  {
    RainbowVector_PushBack(rainbow_vector, x);
  }
}

void RainbowVector_Remove(RainbowVector *rainbow_vector, int index)
{
  __RainbowVector_LShift(rainbow_vector, index);
}

void* RainbowVector_At(RainbowVector *rainbow_vector, int index)
{
  if(index >= 0 && index < rainbow_vector->size)
  {
    return (char*)rainbow_vector->array + index * rainbow_vector->unitsize;
  }
  else
  {
    return NULL;
  }
}

void* RainbowVector_Front(RainbowVector *rainbow_vector)
{
  return rainbow_vector->array;
}

void* RainbowVector_Back(RainbowVector *rainbow_vector)
{
  return (char*)rainbow_vector->array + (rainbow_vector->size - 1) * rainbow_vector->unitsize;
}

size_t RainbowVector_Size(RainbowVector *rainbow_vector)
{
  return rainbow_vector->size;
}

size_t RainbowVector_Capacity(RainbowVector *rainbow_vector)
{
  return rainbow_vector->capacity;
}

void RainbowVector_PushBack(RainbowVector *rainbow_vector, const void *x)
{
  rainbow_vector->size+=1;
  if(rainbow_vector->size > rainbow_vector->capacity)
  {
    __RainbowVector_Extend(rainbow_vector);
  }
  memcpy((char*)rainbow_vector->array + (rainbow_vector->size - 1) * rainbow_vector->unitsize, x, rainbow_vector->unitsize);
}

void RainbowVector_PopBack(RainbowVector *rainbow_vector)
{
  if(rainbow_vector->size > 0)
  {
    rainbow_vector->size -= 1;
  }
}

#include <stdio.h>
void __DEBUG_RainbowVector_Print(RainbowVector *rainbow_vector)
{
  printf("RainbowVector_Size = %ld\n",RainbowVector_Size(rainbow_vector));
  printf("RainbowVector_Capacity = %ld\n",RainbowVector_Capacity(rainbow_vector));
  for(int i = 0; i < rainbow_vector->size; i++)
  {
    printf("%d ",*(short*)RainbowVector_At(rainbow_vector, i));
  }
  puts("");
}

// for test
// int main()
// {
//   RainbowVector vector;
//   RainbowVector_Initialize(&vector, 2);
//   short a = 3, b = 10, c = 11, d = 50, e = 27, f = 15, g = 200;
//   printf("RainbowVector_Insert(&vector, 0, &a);\n");
//   vector.Insert(&vector, 0, &a);
//   __DEBUG_RainbowVector_Print(&vector);
//   printf("RainbowVector_PushBack(&vector, &b);\n");
//   vector.PushBack(&vector, &b);
//   __DEBUG_RainbowVector_Print(&vector);
//   printf("RainbowVector_Insert(&vector, 0, &c);\n");
//   vector.Insert(&vector, 0, &c);
//   __DEBUG_RainbowVector_Print(&vector);
//   printf("RainbowVector_Insert(&vector, 2, &d);\n");
//   vector.Insert(&vector, 2, &d);
//   __DEBUG_RainbowVector_Print(&vector);
//   printf("RainbowVector_Insert(&vector, 4, &e);\n");
//   vector.Insert(&vector, 4, &e);
//   __DEBUG_RainbowVector_Print(&vector);
//   printf("RainbowVector_Insert(&vector, 3, &f);\n");
//   vector.Insert(&vector, 3, &f);
//   __DEBUG_RainbowVector_Print(&vector);
//   printf("__RainbowVector_Extend(&vector);\n");
//   __RainbowVector_Extend(&vector);
//   __DEBUG_RainbowVector_Print(&vector);
//   printf("RainbowVector_Shrink(&vector);\n");
//   vector.Shrink(&vector);
//   __DEBUG_RainbowVector_Print(&vector);
//   printf("RainbowVector_PushBack(&vector, &g);\n");
//   vector.PushBack(&vector, &g);
//   __DEBUG_RainbowVector_Print(&vector);
//   printf("RainbowVector_Remove(&vector, 3);\n");
//   vector.Remove(&vector, 3);
//   __DEBUG_RainbowVector_Print(&vector);
//   printf("RainbowVector_Clear(&vector);\n");
//   vector.Clear(&vector);
//   __DEBUG_RainbowVector_Print(&vector);
// }
