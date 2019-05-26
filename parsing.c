#include "nshell.h"

void tokenizer_reset(Tokenizer *tokenizer)
{
  memset(tokenizer->token_list, 0, TOKEN_LIST_MAX_SIZE * sizeof(char*));
  tokenizer->token_list_size = 0;
}

void tokenize(Tokenizer *tokenizer, char *s, int len) {
  tokenizer_reset(tokenizer);
  if(s[len-1]=='\n')
  {
      s[len-1]='\0';
      len-=1;
  }
  char *token = NULL;
  while((token = strsep(&s, " ")) != NULL)
  {
    if(strlen(token))
    {
        tokenizer->token_list[tokenizer->token_list_size++] = token;
    }
  }
}

char* get_token(Tokenizer *tokenizer, int index)
{
  if(index < tokenizer->token_list_size)
  {
    return tokenizer->token_list[index];
  }
  else
  {
    return NULL;
  }
}

char** get_token_list(Tokenizer *tokenizer)
{
  return tokenizer->token_list;
}

int get_token_count(Tokenizer *tokenizer)
{
  return tokenizer->token_list_size;
}
