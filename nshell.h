#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_MAX_SIZE 16384

void replace_home_with_tilde(char *s);

#define TMPNAME_LIST_MAX_SIZE 30
int make_tempfile();
void remove_tempfile_all();

#define TOKEN_LIST_MAX_SIZE 10
#define METACHAR_LIST_MAX_SIZE 64
typedef struct _Tokenizer
{
  char *token_list[TOKEN_LIST_MAX_SIZE];
  int metachar_index_list[METACHAR_LIST_MAX_SIZE];
  int token_list_size;
  int metachar_list_size;
} Tokenizer;
void tokenize(Tokenizer *tokenizer, char *s, int len);
char* get_token(Tokenizer *tokenizer, int index);
char** get_token_list(Tokenizer *tokenizer);
int get_token_count(Tokenizer *tokenizer);
