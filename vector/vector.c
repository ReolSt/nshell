#include "vector.h"
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
    int *newarray = (int*)malloc(v->capacity*2*sizeof(int));
    v->capacity*=2;
    for(int i=0;i<v->size;i++)
    {
      newarray[i] = v->array[i];
    }
    free(v->array);
    v->array=newarray;
  }
}

void __vector_rshift(Vector *v, int index)
{
  if(v->size > 0 && index >= 0 && index < v->size)
  {
    v->size+=1;
    if(v->size>v->capacity)
    {
      __vector_extend(v);
    }
    for(int i=v->size-1;i>=index;i--)
    {
      v->array[i+1]=v->array[i];
    }
  }
}

void __vector_lshift(Vector *v, int index)
{
  if(index>=0 && index<v->size)
  {
    for(int i=index;i<v->size;i++)
    {
      v->array[i]=v->array[i+1];
    }
    v->size -= 1;
  }
}

void vector_init(Vector *v)
{
  v->size=0;
  v->capacity=VECTOR_DEFAULT_CAPACITY;
  v->array=(int*)malloc(v->capacity*sizeof(int));
}

void vector_clear(Vector *v)
{
  free(v->array);
  vector_init(v);
}

void vector_shrink(Vector *v)
{
  if(v->capacity > VECTOR_DEFAULT_CAPACITY)
  {
    v->capacity /= 2;
    int *shrinked_array = (int*)malloc(v->capacity*sizeof(int));
    memcpy(shrinked_array, v->array, v->capacity*sizeof(int));
    free(v->array);
    v->array = shrinked_array;
    v->size = __for_vector_min(v->size, v->capacity);
  }
}

void vector_insert(Vector *v, int index, int x)
{
  if(index >= 0 && index < v->size)
  {
    __vector_rshift(v, index);
    v->array[index]=x;
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

int vector_at(Vector *v, int index)
{
  if(index >= 0 && index < v->size)
  {
    return v->array[index];
  }
  else
  {
    return -2147483648;
  }
}

int vector_front(Vector *v)
{
  return v->array[0];
}

int vector_back(Vector *v)
{
  return v->array[v->size-1];
}

size_t vector_size(Vector *v)
{
  return v->size;
}

size_t vector_capacity(Vector *v)
{
  return v->capacity;
}

void vector_push_back(Vector *v, int x)
{
  v->size+=1;
  if(v->size>v->capacity)
  {
    __vector_extend(v);
  }
  v->array[v->size-1]=x;
}

void vector_pop_back(Vector *v)
{
  if(v->size > 0)
  {
    v->size-=1;
  }
}

void __DEBUG_vector_print(Vector *v)
{
  printf("vector_size = %d\n",vector_size(v));
  printf("vector_capacity = %d\n",vector_capacity(v));
  for(int i=0;i<v->size;i++)
  {
    printf("%d ",vector_at(v, i));
  }
  puts("");
}

int main()
{
  Vector v;
  vector_init(&v);
  vector_insert(&v, 0, 3);
  __DEBUG_vector_print(&v);
  vector_push_back(&v, 10);
  __DEBUG_vector_print(&v);
  vector_insert(&v, 0, 11);
  __DEBUG_vector_print(&v);
  vector_insert(&v, 2, 50);
  __DEBUG_vector_print(&v);
  vector_insert(&v, 4, 27);
  __DEBUG_vector_print(&v);
  vector_insert(&v, 3, 15);
  __DEBUG_vector_print(&v);
  __vector_extend(&v);
  __DEBUG_vector_print(&v);
  vector_shrink(&v);
  __DEBUG_vector_print(&v);
  vector_push_back(&v, 200);
  vector_push_back(&v, 200);
  vector_push_back(&v, 200);
  vector_push_back(&v, 200);
  vector_push_back(&v, 200);
  vector_push_back(&v, 200);
  vector_push_back(&v, 200);
  __DEBUG_vector_print(&v);
  vector_clear(&v);
  __DEBUG_vector_print(&v);
}
