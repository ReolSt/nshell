#include "AirForceVector.h"

#ifndef max
#define max(a,b) (((a) (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif


void __AirForceVector_Extend(AirForceVector *vector)
{
  if(vector->array!=NULL)
  {
    void *newarray = calloc(vector->capacity * 2, vector->unitsize);
    vector->capacity*=2;
    memcpy(newarray, vector->array, vector->size * vector->unitsize);
    free(vector->array);
    vector->array = newarray;
  }
}

void __AirForceVector_RShift(AirForceVector *vector, int index)
{
  if(vector->size > 0 && index >= 0 && index < vector->size)
  {
    vector->size += 1;
    if(vector->size > vector->capacity)
    {
      __AirForceVector_Extend(vector);
    }
    memmove((char*)vector->array + (index + 1) * vector->unitsize,
            (char*)vector->array + index * vector->unitsize,
            (vector->size - index) * vector->unitsize);
  }
}

void __AirForceVector_LShift(AirForceVector *vector, int index)
{
  if(index>=0 && index < vector->size)
  {
    memmove((char*)vector->array + index * vector->unitsize,
            (char*)vector->array + (index + 1) * vector->unitsize,
            (vector->size - index) * vector->unitsize);
    vector->size -= 1;
  }
}

void AirForceVector_Initialize(AirForceVector *vector, size_t unitsize)
{
  vector->unitsize = unitsize;
  vector->size = 0;
  vector->capacity = AIRFORCE_VECTOR_DEFAULT_CAPACITY;
  vector->array = calloc(vector->capacity, vector->unitsize);
//function pointers
  vector->Initialize = AirForceVector_Initialize;
  vector->IsInitialized = AirForceVector_IsInitialized;
  vector->Clear = AirForceVector_Clear;
  vector->Destroy = AirForceVector_Destroy;
  vector->Shrink = AirForceVector_Shrink;
  vector->Resize = AirForceVector_Resize;
  vector->Insert = AirForceVector_Insert;
  vector->Remove = AirForceVector_Remove;
  vector->At = AirForceVector_At;
  vector->Front = AirForceVector_Front;
  vector->Back = AirForceVector_Back;
  vector->Size = AirForceVector_Size;
  vector->Capacity = AirForceVector_Capacity;
  vector->PushBack = AirForceVector_PushBack;
  vector->PopBack = AirForceVector_PopBack;
//
  vector->initialized = 1;
}

int AirForceVector_IsInitialized(AirForceVector *vector)
{
  return vector->initialized;
}

void AirForceVector_Clear(AirForceVector *vector)
{
  free(vector->array);
  AirForceVector_Initialize(vector, vector->unitsize);
}

void AirForceVector_Destroy(AirForceVector *vector)
{
  vector->initialized = 0;
  vector->size = 0;
  vector->capacity = 0;
  free(vector->array);
  vector->array = NULL;
}

void AirForceVector_Shrink(AirForceVector *vector)
{
  if(vector->capacity > AIRFORCE_VECTOR_DEFAULT_CAPACITY)
  {
    AirForceVector_Resize(vector, vector->size + 1);
  }
}

void AirForceVector_Resize(AirForceVector *vector, size_t size)
{
  vector->capacity = size;
  void* resized_array = malloc(vector->capacity * vector->unitsize);
  memcpy(resized_array, vector->array, vector->capacity * vector->unitsize);
  free(vector->array);
  vector->array = resized_array;
  vector->size = min(vector->size, vector->capacity);
}

void AirForceVector_Insert(AirForceVector *vector, int index, const void *x)
{
  if(index >= 0 && index < vector->size)
  {
    __AirForceVector_RShift(vector, index);
    memcpy((char*)vector->array + index * vector->unitsize, x, vector->unitsize);
  }
  else if(index == vector->size)
  {
    AirForceVector_PushBack(vector, x);
  }
}

void AirForceVector_Remove(AirForceVector *vector, int index)
{
  __AirForceVector_LShift(vector, index);
}

void* AirForceVector_At(AirForceVector *vector, int index)
{
  if(index >= 0 && index < vector->size)
  {
    return (char*)vector->array + index * vector->unitsize;
  }
  else
  {
    return NULL;
  }
}

void* AirForceVector_Front(AirForceVector *vector)
{
  return vector->array;
}

void* AirForceVector_Back(AirForceVector *vector)
{
  return (char*)vector->array + (vector->size - 1) * vector->unitsize;
}

size_t AirForceVector_Size(AirForceVector *vector)
{
  return vector->size;
}

size_t AirForceVector_Capacity(AirForceVector *vector)
{
  return vector->capacity;
}

void AirForceVector_PushBack(AirForceVector *vector, const void *x)
{
  vector->size+=1;
  if(vector->size > vector->capacity)
  {
    __AirForceVector_Extend(vector);
  }
  memcpy((char*)vector->array + (vector->size - 1) * vector->unitsize, x, vector->unitsize);
}

void AirForceVector_PopBack(AirForceVector *vector)
{
  if(vector->size > 0)
  {
    memset((char*)vector->array + (vector->size - 1) * vector->unitsize, 0, vector->unitsize);
    vector->size -= 1;
  }
}

#include <stdio.h>
void __DEBUG_AirForceVector_Print(AirForceVector *vector)
{
  printf("AirForceVector_Size = %ld\n",AirForceVector_Size(vector));
  printf("AirForceVector_Capacity = %ld\n",AirForceVector_Capacity(vector));
  for(int i = 0; i < vector->size; i++)
  {
    printf("%d ",*(short*)AirForceVector_At(vector, i));
  }
  puts("");
}

// for test
// int main()
// {
//   AirForceVector vector;
//   AirForceVector_Initialize(&vector, 2);
//   short a = 3, b = 10, c = 11, d = 50, e = 27, f = 15, g = 200;
//   printf("AirForceVector_Insert(&vector, 0, &a);\n");
//   vector.Insert(&vector, 0, &a);
//   __DEBUG_AirForceVector_Print(&vector);
//   printf("AirForceVector_PushBack(&vector, &b);\n");
//   vector.PushBack(&vector, &b);
//   __DEBUG_AirForceVector_Print(&vector);
//   printf("AirForceVector_Insert(&vector, 0, &c);\n");
//   vector.Insert(&vector, 0, &c);
//   __DEBUG_AirForceVector_Print(&vector);
//   printf("AirForceVector_Insert(&vector, 2, &d);\n");
//   vector.Insert(&vector, 2, &d);
//   __DEBUG_AirForceVector_Print(&vector);
//   printf("AirForceVector_Insert(&vector, 4, &e);\n");
//   vector.Insert(&vector, 4, &e);
//   __DEBUG_AirForceVector_Print(&vector);
//   printf("AirForceVector_Insert(&vector, 3, &f);\n");
//   vector.Insert(&vector, 3, &f);
//   __DEBUG_AirForceVector_Print(&vector);
//   printf("__AirForceVector_Extend(&vector);\n");
//   __AirForceVector_Extend(&vector);
//   __DEBUG_AirForceVector_Print(&vector);
//   printf("AirForceVector_Shrink(&vector);\n");
//   vector.Shrink(&vector);
//   __DEBUG_AirForceVector_Print(&vector);
//   printf("AirForceVector_PushBack(&vector, &g);\n");
//   vector.PushBack(&vector, &g);
//   __DEBUG_AirForceVector_Print(&vector);
//   printf("AirForceVector_Remove(&vector, 3);\n");
//   vector.Remove(&vector, 3);
//   __DEBUG_AirForceVector_Print(&vector);
//   printf("AirForceVector_Clear(&vector);\n");
//   vector.Clear(&vector);
//   __DEBUG_AirForceVector_Print(&vector);
// }
