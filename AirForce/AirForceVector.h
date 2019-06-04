#ifndef AIRFORCE_VECTOR_H
#define AIRFORCE_VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>

#include "AirForceCall.h"

#define AIRFORCE_VECTOR_DEFAULT_CAPACITY 64

typedef struct __AirForce_Vector{
  int initialized;
  size_t unitsize;
  size_t capacity;
  size_t size;
  void *array;

  void (*Initialize)(struct __AirForce_Vector *, size_t);
  int (*IsInitialized)(struct __AirForce_Vector *);
  void (*Clear)(struct __AirForce_Vector *);
  void (*Destroy)(struct __AirForce_Vector *);
  void (*Shrink)(struct __AirForce_Vector *);
  void (*Resize)(struct __AirForce_Vector *, size_t);
  void (*Insert)(struct __AirForce_Vector *, int, const void *);
  void (*Remove)(struct __AirForce_Vector *, int);
  void * (*At)(struct __AirForce_Vector *, int);
  void * (*Front)(struct __AirForce_Vector *);
  void * (*Back)(struct __AirForce_Vector *);
  size_t (*Size)(struct __AirForce_Vector *);
  size_t (*Capacity)(struct __AirForce_Vector *);
  void (*PushBack)(struct __AirForce_Vector *, const void *);
  void (*PopBack)(struct __AirForce_Vector *);

} AirForceVector;

void __AirForceVector_Extend(AirForceVector *vector);
void __AirForceVector_RShift(AirForceVector *vector, int index);
void __AirForceVector_LShift(AirForceVector *vector, int index);

void AirForceVector_Initialize(AirForceVector *vector, size_t unitsize);
int AirForceVector_IsInitialized(AirForceVector *vector);
void AirForceVector_Clear(AirForceVector *vector);
void AirForceVector_Destroy(AirForceVector *vector);
void AirForceVector_Shrink(AirForceVector *vector);
void AirForceVector_Resize(AirForceVector *vector, size_t size);
void AirForceVector_Insert(AirForceVector *vector, int index, const void *x);
void AirForceVector_Remove(AirForceVector *vector, int index);
void* AirForceVector_At(AirForceVector *vector, int index);
void* AirForceVector_Front(AirForceVector *vector);
void* AirForceVector_Back(AirForceVector *vector);
size_t AirForceVector_Size(AirForceVector *vector);
size_t AirForceVector_Capacity(AirForceVector *vector);
void AirForceVector_PushBack(AirForceVector *vector, const void *x);
void AirForceVector_PopBack(AirForceVector *vector);
#endif
