#include "String.h"

void __string_extend_for_null_terminating(String *string)
{
  if(string->string_vector.size + 2 >= string->string_vector.capacity)
  {
    __vector_extend(&(string->string_vector));
  }
}

void string_append(String *string, char ch)
{
  vector_push_back(&(string->string_vector), &ch);
  string->size += 1;
  __string_extend_for_null_terminating(string);
}

void string_pop(String *string)
{
  if(string->size > 0)
  {
    vector_pop_back(&(string->string_vector));
    string->size -= 1;
  }
}

void string_insert(String *string, int index, char ch)
{
  vector_insert(&(string->string_vector), index, &ch);
  string->size += 1;
  __string_extend_for_null_terminating(string);
}

void string_remove(String *string, int index)
{
  vector_remove(&(string->string_vector), index);
  string->size -= 1;
}

void string_init(String *string, const char *s, size_t length)
{
  vector_init(&(string->string_vector), sizeof(char));
  for(int i=0;i<length;++i)
  {
    vector_push_back(&(string->string_vector), s + i);
  }
  string->size = length;
}

void string_clear(String *string)
{
  vector_clear(&(string->string_vector));
  string->size = 0;
}

void string_destroy(String *string)
{
  vector_destroy(&(string->string_vector));
  string->size = 0;
}

const char *string_c_str(String *string)
{
  return (const char*)vector_at(&(string->string_vector), 0);
}

char string_at(String *string, int index)
{
  return *(char*)vector_at(&(string->string_vector), index);
}

char string_front(String *string)
{
  return *(char*)vector_front(&(string->string_vector));
}

char string_back(String *string)
{
  return *(char*)vector_back(&(string->string_vector));
}

int string_length(String *string)
{
  return string->size;
}

//for test
// int main()
// {
//   String string;
//   string_init(&string, "Testasdf", 8);
//   string_remove(&string, 4);
//   printf("%s\n",string_c_str(&string));
//   printf("%c\n",string_at(&string, 1));
//   string_append(&string, 'a');
//   string_append(&string, 'b');
//   string_insert(&string, 2, 'd');
//   printf("%s\n",string_c_str(&string));
// }
