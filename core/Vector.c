#include <stdio.h>
#include "Vector.h"

int __for_vector_min(int a, int b)
{
  return a > b ? b : a;
}

int __for_vector_max(int a, int b)
{
  return a > b ? a : b;
}

void __vector_extend(Vector *v)
{
  if(v->array!=NULL)
  {
    void *newarray = calloc(v->capacity * 2, v->unitsize);
    v->capacity*=2;
    memcpy(newarray, v->array, v->size * v->unitsize);
    free(v->array);
    v->array = newarray;
  }
}

void __vector_rshift(Vector *v, int index)
{
  if(v->size > 0 && index >= 0 && index < v->size)
  {
    v->size += 1;
    if(v->size > v->capacity)
    {
      __vector_extend(v);
    }
    memmove((char*)v->array + (index + 1) * v->unitsize,
            (char*)v->array + index * v->unitsize,
            (v->size - index) * v->unitsize);
  }
}

void __vector_lshift(Vector *v, int index)
{
  if(index>=0 && index < v->size)
  {
    memmove((char*)v->array + index * v->unitsize,
            (char*)v->array + (index + 1) * v->unitsize,
            (v->size - index) * v->unitsize);
    v->size -= 1;
  }
}

void vector_init(Vector *v, size_t unitsize)
{
  v->unitsize = unitsize;
  v->size = 0;
  v->capacity = VECTOR_DEFAULT_CAPACITY;
  v->array = calloc(v->capacity, v->unitsize);
}

void vector_clear(Vector *v)
{
  free(v->array);
  vector_init(v, v->unitsize);
}

void vector_destroy(Vector *v)
{
  v->size = 0;
  v->capacity = 0;
  free(v->array);
  v->array = NULL;
}

void vector_shrink(Vector *v)
{
  if(v->capacity > VECTOR_DEFAULT_CAPACITY)
  {
    vector_resize(v, v->capacity / 2);
  }
}

void vector_resize(Vector *v, size_t size)
{
  v->capacity = size;
  void* resized_array = malloc(v->capacity * v->unitsize);
  memcpy(resized_array, v->array, v->capacity * v->unitsize);
  free(v->array);
  v->array = resized_array;
  v->size = __for_vector_min(v->size, v->capacity);
}

void vector_insert(Vector *v, int index, const void *x)
{
  if(index >= 0 && index < v->size)
  {
    __vector_rshift(v, index);
    memcpy((char*)v->array + index * v->unitsize, x, v->unitsize);
  }
  else if(index == v->size)
  {
    vector_push_back(v, x);
  }
}

void vector_remove(Vector *v, int index)
{
  __vector_lshift(v, index);
  if(v->size < v->capacity / 3)
  {
    vector_shrink(v);
  }
}

void* vector_at(Vector *v, int index)
{
  if(index >= 0 && index < v->size)
  {
    return (char*)v->array + index * v->unitsize;
  }
  else
  {
    return NULL;
  }
}

void* vector_front(Vector *v)
{
  return v->array;
}

void* vector_back(Vector *v)
{
  return (char*)v->array + (v->size - 1) * v->unitsize;
}

size_t vector_size(Vector *v)
{
  return v->size;
}

size_t vector_capacity(Vector *v)
{
  return v->capacity;
}

void vector_push_back(Vector *v, const void *x)
{
  v->size+=1;
  if(v->size > v->capacity)
  {
    __vector_extend(v);
  }
  memcpy((char*)v->array + (v->size - 1) * v->unitsize, x, v->unitsize);
}

void vector_pop_back(Vector *v)
{
  if(v->size > 0)
  {
    v->size -= 1;
  }
}

void __DEBUG_vector_print(Vector *v)
{
  printf("vector_size = %ld\n",vector_size(v));
  printf("vector_capacity = %ld\n",vector_capacity(v));
  for(int i = 0; i < v->size; i++)
  {
    printf("%d ",*(short*)vector_at(v, i));
  }
  puts("");
}

// for test
// int main()
// {
//   Vector v;
//   vector_init(&v, 2);
//   short a = 3, b = 10, c = 11, d = 50, e = 27, f = 15, g = 200;
//   printf("vector_insert(&v, 0, &a);\n");
//   vector_insert(&v, 0, &a);
//   __DEBUG_vector_print(&v);
//   printf("vector_push_back(&v, &b);\n");
//   vector_push_back(&v, &b);
//   __DEBUG_vector_print(&v);
//   printf("vector_insert(&v, 0, &c);\n");
//   vector_insert(&v, 0, &c);
//   __DEBUG_vector_print(&v);
//   printf("vector_insert(&v, 2, &d);\n");
//   vector_insert(&v, 2, &d);
//   __DEBUG_vector_print(&v);
//   printf("vector_insert(&v, 4, &e);\n");
//   vector_insert(&v, 4, &e);
//   __DEBUG_vector_print(&v);
//   printf("vector_insert(&v, 3, &f);\n");
//   vector_insert(&v, 3, &f);
//   __DEBUG_vector_print(&v);
//   printf("__vector_extend(&v);\n");
//   __vector_extend(&v);
//   __DEBUG_vector_print(&v);
//   printf("vector_shrink(&v);\n");
//   vector_shrink(&v);
//   __DEBUG_vector_print(&v);
//   printf("vector_push_back(&v, &g);\n");
//   vector_push_back(&v, &g);
//   __DEBUG_vector_print(&v);
//   printf("vector_remove(&v, 3);\n");
//   vector_remove(&v, 3);
//   __DEBUG_vector_print(&v);
//   printf("vector_clear(&v);\n");
//   vector_clear(&v);
//   __DEBUG_vector_print(&v);
// }
