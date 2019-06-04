#include "nshell.h"

void tokenizer_init(Tokenizer *tokenizer)
{
  memset(tokenizer->token_ptr_list, 0, TOKEN_MAX_COUNT * sizeof(char*));
  AirForceVector_Initialize(&(tokenizer->token_list), sizeof(AirForceString));
}

void tokenizer_tokenize(Tokenizer *tokenizer, char *s, size_t len) {
  tokenizer_clear(tokenizer);
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
      AirForceString ts;
      AirForceString_Initialize(&ts, token, tlen);
      Call(tokenizer->token_list, PushBack, &ts);
      tokenizer->token_ptr_list[index] = AirForceVector_At(&((AirForceString*)AirForceVector_At(&(tokenizer->token_list), index))->string_vector, 0);
      index += 1;
    }
  }
}

const char* tokenizer_get(Tokenizer *tokenizer, int index)
{
  AirForceString * string = Call(tokenizer->token_list, At, index);
  return CallP(string, CStr);
}

char* const* tokenizer_get_list(Tokenizer *tokenizer)
{
  return tokenizer->token_ptr_list;
}

int tokenizer_get_count(Tokenizer *tokenizer)
{
  return Call(tokenizer->token_list, Size);
}

void tokenizer_clear(Tokenizer *tokenizer)
{
  memset(tokenizer->token_ptr_list, 0, TOKEN_MAX_COUNT * sizeof(char*));
  size_t vsize = Call(tokenizer->token_list, Size);
  for(int i = 0; i < vsize; ++i)
  {
    AirForceString * string = Call(tokenizer->token_list, At, i);
    CallP(string, Destroy);
  }
  Call(tokenizer->token_list, Clear);
}

void tokenizer_destroy(Tokenizer *tokenizer)
{
  tokenizer_clear(tokenizer);
  Call(tokenizer->token_list, Destroy);
}
