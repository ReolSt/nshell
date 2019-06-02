#ifndef RAINBOW_VECTOR_H
#define RAINBOW_VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>

#include "RainbowCall.h"

#define RAINBOW_VECTOR_DEFAULT_CAPACITY 64

typedef struct __Rainbow_Vector{
  int initialized;
  size_t unitsize;
  size_t capacity;
  size_t size;
  void *array;

  void (*Initialize)(struct __Rainbow_Vector *, size_t);
  int (*IsInitialized)(struct __Rainbow_Vector *);
  void (*Clear)(struct __Rainbow_Vector *);
  void (*Destroy)(struct __Rainbow_Vector *);
  void (*Shrink)(struct __Rainbow_Vector *);
  void (*Resize)(struct __Rainbow_Vector *, size_t);
  void (*Insert)(struct __Rainbow_Vector *, int, const void *);
  void (*Remove)(struct __Rainbow_Vector *, int);
  void * (*At)(struct __Rainbow_Vector *, int);
  void * (*Front)(struct __Rainbow_Vector *);
  void * (*Back)(struct __Rainbow_Vector *);
  size_t (*Size)(struct __Rainbow_Vector *);
  size_t (*Capacity)(struct __Rainbow_Vector *);
  void (*PushBack)(struct __Rainbow_Vector *, const void *);
  void (*PopBack)(struct __Rainbow_Vector *);

} RainbowVector;

void __RainbowVector_Extend(RainbowVector *rainbow_vector);
void __RainbowVector_RShift(RainbowVector *rainbow_vector, int index);
void __RainbowVector_LShift(RainbowVector *rainbow_vector, int index);

void RainbowVector_Initialize(RainbowVector *rainbow_vector, size_t unitsize);
int RainbowVector_IsInitialized(RainbowVector *rainbow_vector);
void RainbowVector_Clear(RainbowVector *rainbow_vector);
void RainbowVector_Destroy(RainbowVector *rainbow_vector);
void RainbowVector_Shrink(RainbowVector *rainbow_vector);
void RainbowVector_Resize(RainbowVector *rainbow_vector, size_t size);
void RainbowVector_Insert(RainbowVector *rainbow_vector, int index, const void *x);
void RainbowVector_Remove(RainbowVector *rainbow_vector, int index);
void* RainbowVector_At(RainbowVector *rainbow_vector, int index);
void* RainbowVector_Front(RainbowVector *rainbow_vector);
void* RainbowVector_Back(RainbowVector *rainbow_vector);
size_t RainbowVector_Size(RainbowVector *rainbow_vector);
size_t RainbowVector_Capacity(RainbowVector *rainbow_vector);
void RainbowVector_PushBack(RainbowVector *rainbow_vector, const void *x);
void RainbowVector_PopBack(RainbowVector *rainbow_vector);
#endif
