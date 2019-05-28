#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define VECTOR_DEFAULT_CAPACITY 64

typedef struct _Vector{
  size_t unitsize;
  size_t capacity;
  size_t size;
  void *array;
} Vector;
int __for_vector_min(int a, int b);
int __for_vector_max(int a, int b);

void __vector_extend(Vector *v);
void __vector_rshift(Vector *v, int index);
void __vector_lshift(Vector *v, int index);

void vector_init(Vector *v, size_t unitsize);
void vector_clear(Vector *v);
void vector_destroy(Vector *v);
void vector_shrink(Vector *v);
void vector_resize(Vector *v, size_t size);
void vector_insert(Vector *v, int index, const void *x);
void vector_remove(Vector *v, int index);
void* vector_at(Vector *v, int index);
void* vector_front(Vector *v);
void* vector_back(Vector *v);
size_t vector_size(Vector *v);
size_t vector_capacity(Vector *v);
void vector_push_back(Vector *v, const void *x);
void vector_pop_back(Vector *v);
#endif
