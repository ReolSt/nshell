#include "nshell.h"

void tokenizer_init(Tokenizer *tokenizer)
{
  memset(tokenizer->token_ptr_list, 0, TOKEN_MAX_COUNT * sizeof(char*));
  vector_init(&(tokenizer->token_list), sizeof(String));
}

void tokenize(Tokenizer *tokenizer, char *s, size_t len) {
  clear_tokens(tokenizer);
  char copy[CMD_BUF_MAX_SIZE];
  char *sptr = copy;
  memset(copy, 0, CMD_BUF_MAX_SIZE * sizeof(char));
  strncpy(copy, s, len);
  char *token = NULL;
  int index = 0;
  while((token = strsep(&sptr, " \t\n")) != NULL)
  {
    int tlen = strlen(token);
    if(tlen)
    {
      String ts;
      string_init(&ts, token, tlen);
      vector_push_back(&(tokenizer->token_list), &ts);
      tokenizer->token_ptr_list[index] =
        vector_at(&((String*)vector_at(&(tokenizer->token_list), index))->string_vector, 0);
      index += 1;
    }
  }
  printf("%s\n",get_token(tokenizer, 0));
}

const char* get_token(Tokenizer *tokenizer, int index)
{
  return string_c_str(vector_at(&(tokenizer->token_list), index));
}

char* const* get_token_list(Tokenizer *tokenizer)
{
  return tokenizer->token_ptr_list;
}

int get_token_count(Tokenizer *tokenizer)
{
  return vector_size(&(tokenizer->token_list));
}

void clear_tokens(Tokenizer *tokenizer)
{
  memset(tokenizer->token_ptr_list, 0, TOKEN_MAX_COUNT * sizeof(char*));
  size_t vsize = vector_size(&(tokenizer->token_list));
  for(int i = 0; i < vsize; ++i)
  {
    string_destroy(vector_at(&(tokenizer->token_list), i));
  }
  vector_clear(&(tokenizer->token_list));
}

void tokenizer_destroy(Tokenizer *tokenizer)
{
  clear_tokens(tokenizer);
  vector_destroy(&(tokenizer->token_list));
}
