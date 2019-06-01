#include "HanzoVector.h"

#ifndef max
#define max(a,b) (((a) (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif


void __HanzoVector_Extend(HanzoVector *hanzo_vector)
{
  if(hanzo_vector->array!=NULL)
  {
    void *newarray = calloc(hanzo_vector->capacity * 2, hanzo_vector->unitsize);
    hanzo_vector->capacity*=2;
    memcpy(newarray, hanzo_vector->array, hanzo_vector->size * hanzo_vector->unitsize);
    free(hanzo_vector->array);
    hanzo_vector->array = newarray;
  }
}

void __HanzoVector_RShift(HanzoVector *hanzo_vector, int index)
{
  if(hanzo_vector->size > 0 && index >= 0 && index < hanzo_vector->size)
  {
    hanzo_vector->size += 1;
    if(hanzo_vector->size > hanzo_vector->capacity)
    {
      __HanzoVector_Extend(hanzo_vector);
    }
    memmove((char*)hanzo_vector->array + (index + 1) * hanzo_vector->unitsize,
            (char*)hanzo_vector->array + index * hanzo_vector->unitsize,
            (hanzo_vector->size - index) * hanzo_vector->unitsize);
  }
}

void __HanzoVector_LShift(HanzoVector *hanzo_vector, int index)
{
  if(index>=0 && index < hanzo_vector->size)
  {
    memmove((char*)hanzo_vector->array + index * hanzo_vector->unitsize,
            (char*)hanzo_vector->array + (index + 1) * hanzo_vector->unitsize,
            (hanzo_vector->size - index) * hanzo_vector->unitsize);
    hanzo_vector->size -= 1;
  }
}

void HanzoVector_Initialize(HanzoVector *hanzo_vector, size_t unitsize)
{
  hanzo_vector->initialized = 1;
  hanzo_vector->unitsize = unitsize;
  hanzo_vector->size = 0;
  hanzo_vector->capacity = HANZO_VECTOR_DEFAULT_CAPACITY;
  hanzo_vector->array = calloc(hanzo_vector->capacity, hanzo_vector->unitsize);
//function pointers
  hanzo_vector->Initialize = HanzoVector_Initialize;
  hanzo_vector->IsInitialized = HanzoVector_IsInitialized;
  hanzo_vector->Clear = HanzoVector_Clear;
  hanzo_vector->Destroy = HanzoVector_Destroy;
  hanzo_vector->Shrink = HanzoVector_Shrink;
  hanzo_vector->Resize = HanzoVector_Resize;
  hanzo_vector->Insert = HanzoVector_Insert;
  hanzo_vector->Remove = HanzoVector_Remove;
  hanzo_vector->At = HanzoVector_At;
  hanzo_vector->Front = HanzoVector_Front;
  hanzo_vector->Back = HanzoVector_Back;
  hanzo_vector->Size = HanzoVector_Size;
  hanzo_vector->Capacity = HanzoVector_Capacity;
  hanzo_vector->PushBack = HanzoVector_PushBack;
  hanzo_vector->PopBack = HanzoVector_PopBack;
}

int HanzoVector_IsInitialized(HanzoVector *hanzo_vector)
{
  return hanzo_vector->initialized;
}

void HanzoVector_Clear(HanzoVector *hanzo_vector)
{
  free(hanzo_vector->array);
  HanzoVector_Initialize(hanzo_vector, hanzo_vector->unitsize);
}

void HanzoVector_Destroy(HanzoVector *hanzo_vector)
{
  hanzo_vector->initialized = 0;
  hanzo_vector->size = 0;
  hanzo_vector->capacity = 0;
  free(hanzo_vector->array);
  hanzo_vector->array = NULL;
}

void HanzoVector_Shrink(HanzoVector *hanzo_vector)
{
  if(hanzo_vector->capacity > HANZO_VECTOR_DEFAULT_CAPACITY)
  {
    HanzoVector_Resize(hanzo_vector, hanzo_vector->size + 1);
  }
}

void HanzoVector_Resize(HanzoVector *hanzo_vector, size_t size)
{
  hanzo_vector->capacity = size;
  void* resized_array = malloc(hanzo_vector->capacity * hanzo_vector->unitsize);
  memcpy(resized_array, hanzo_vector->array, hanzo_vector->capacity * hanzo_vector->unitsize);
  free(hanzo_vector->array);
  hanzo_vector->array = resized_array;
  hanzo_vector->size = min(hanzo_vector->size, hanzo_vector->capacity);
}

void HanzoVector_Insert(HanzoVector *hanzo_vector, int index, const void *x)
{
  if(index >= 0 && index < hanzo_vector->size)
  {
    __HanzoVector_RShift(hanzo_vector, index);
    memcpy((char*)hanzo_vector->array + index * hanzo_vector->unitsize, x, hanzo_vector->unitsize);
  }
  else if(index == hanzo_vector->size)
  {
    HanzoVector_PushBack(hanzo_vector, x);
  }
}

void HanzoVector_Remove(HanzoVector *hanzo_vector, int index)
{
  __HanzoVector_LShift(hanzo_vector, index);
}

void* HanzoVector_At(HanzoVector *hanzo_vector, int index)
{
  if(index >= 0 && index < hanzo_vector->size)
  {
    return (char*)hanzo_vector->array + index * hanzo_vector->unitsize;
  }
  else
  {
    return NULL;
  }
}

void* HanzoVector_Front(HanzoVector *hanzo_vector)
{
  return hanzo_vector->array;
}

void* HanzoVector_Back(HanzoVector *hanzo_vector)
{
  return (char*)hanzo_vector->array + (hanzo_vector->size - 1) * hanzo_vector->unitsize;
}

size_t HanzoVector_Size(HanzoVector *hanzo_vector)
{
  return hanzo_vector->size;
}

size_t HanzoVector_Capacity(HanzoVector *hanzo_vector)
{
  return hanzo_vector->capacity;
}

void HanzoVector_PushBack(HanzoVector *hanzo_vector, const void *x)
{
  hanzo_vector->size+=1;
  if(hanzo_vector->size > hanzo_vector->capacity)
  {
    __HanzoVector_Extend(hanzo_vector);
  }
  memcpy((char*)hanzo_vector->array + (hanzo_vector->size - 1) * hanzo_vector->unitsize, x, hanzo_vector->unitsize);
}

void HanzoVector_PopBack(HanzoVector *hanzo_vector)
{
  if(hanzo_vector->size > 0)
  {
    hanzo_vector->size -= 1;
  }
}

#include <stdio.h>
void __DEBUG_HanzoVector_Print(HanzoVector *hanzo_vector)
{
  printf("HanzoVector_Size = %ld\n",HanzoVector_Size(hanzo_vector));
  printf("HanzoVector_Capacity = %ld\n",HanzoVector_Capacity(hanzo_vector));
  for(int i = 0; i < hanzo_vector->size; i++)
  {
    printf("%d ",*(short*)HanzoVector_At(hanzo_vector, i));
  }
  puts("");
}

// for test
// int main()
// {
//   HanzoVector vector;
//   HanzoVector_Initialize(&vector, 2);
//   short a = 3, b = 10, c = 11, d = 50, e = 27, f = 15, g = 200;
//   printf("HanzoVector_Insert(&vector, 0, &a);\n");
//   vector.Insert(&vector, 0, &a);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_PushBack(&vector, &b);\n");
//   vector.PushBack(&vector, &b);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Insert(&vector, 0, &c);\n");
//   vector.Insert(&vector, 0, &c);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Insert(&vector, 2, &d);\n");
//   vector.Insert(&vector, 2, &d);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Insert(&vector, 4, &e);\n");
//   vector.Insert(&vector, 4, &e);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Insert(&vector, 3, &f);\n");
//   vector.Insert(&vector, 3, &f);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("__HanzoVector_Extend(&vector);\n");
//   __HanzoVector_Extend(&vector);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Shrink(&vector);\n");
//   vector.Shrink(&vector);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_PushBack(&vector, &g);\n");
//   vector.PushBack(&vector, &g);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Remove(&vector, 3);\n");
//   vector.Remove(&vector, 3);
//   __DEBUG_HanzoVector_Print(&vector);
//   printf("HanzoVector_Clear(&vector);\n");
//   vector.Clear(&vector);
//   __DEBUG_HanzoVector_Print(&vector);
// }
