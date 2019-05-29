#ifndef STRING_H
#define STRING_H
#include "Vector.h"
typedef struct _String
{
  Vector string_vector;
  size_t size;
} String;

void __string_extend_for_null_terminating(String *string);
void string_append(String *string, const char ch);
void string_pop(String *string);
void string_insert(String *string, int index, const char ch);
void string_remove(String *string, int index);
void string_init(String *string, const char *s, size_t length);
void string_clear(String *string);
void string_destroy(String *string);
const char *string_c_str(String *string);
char string_at(String *string, int index);
char string_front(String *string);
char string_back(String *string);
int string_length(String *string);
#endif
