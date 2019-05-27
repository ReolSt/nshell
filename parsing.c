#include "nshell.h"

void tokenizer_init(Tokenizer *tokenizer)
{
  vector_init(&tokenizer->token_list, sizeof(String));
}

void tokenize(Tokenizer *tokenizer, char *s, size_t len) {
  clear_tokens(tokenizer);
  char copy[CMD_BUF_MAX_SIZE];
  char *sptr = copy;
  strncpy(copy, s, len);
  if(copy[len-1]=='\n')
  {
      copy[len-1]='\0';
      len-=1;
  }
  char *token = NULL;
  int index = 0;
  while((token = strsep(&sptr, " ")) != NULL)
  {
    int tlen = strlen(token);
    if(tlen)
    {
      String ts;
      string_init(&ts, token, tlen);
      vector_push_back(&(tokenizer->token_list), &ts);
      tokenizer->token_ptr_list[index] =
        vector_at(&(((String*)vector_at(&(tokenizer->token_list), index))->string_vector), 0);
      index += 1;
    }
  }
}

const char* get_token(Tokenizer *tokenizer, int index)
{
  if(index < get_token_count(tokenizer))
  {
    return string_c_str(vector_at(&(tokenizer->token_list), index));
  }
  else
  {
    return NULL;
  }
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
  int vsize = vector_size(&(tokenizer->token_list));
  for(int i = 0; i < vsize; ++i)
  {
    string_destroy(vector_at(&(tokenizer->token_list), i));
    tokenizer->token_ptr_list[i] = NULL;
  }
}

void tokenizer_destroy(Tokenizer *tokenizer)
{
  clear_tokens(tokenizer);
  vector_destroy(&(tokenizer->token_list));
}
