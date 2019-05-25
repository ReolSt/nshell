#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#define VECTOR_DEFAULT_CAPACITY 10

typedef struct _Vector{
  size_t capacity;
  size_t size;
  int *array;
} Vector;

int __for_vector_min(int a, int b);
int __for_vector_max(int a, int b);

void __vector_extend(Vector *v);
void __vector_rshift(Vector *v, int index);
void __vector_lshift(Vector *v, int index);

void vector_init(Vector *v);
void vector_clear(Vector *v);
void vector_shrink(Vector *v);
void vector_insert(Vector *v, int index, int x);
void vector_remove(Vector *v, int index);
int vector_at(Vector *v, int index);
int vector_front(Vector *v);
int vector_back(Vector *v);
size_t vector_size(Vector *v);
size_t vector_capacity(Vector *v);
void vector_push_back(Vector *v, int x);
void vector_pop_back(Vector *v);
