#ifndef NSHELL_H
#define NSHELL_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "core/Vector/Vector.h"
#include "core/String/String.h"

#define CMD_BUF_MAX_SIZE 256
#define OUTPUT_BUF_MAX_SIZE 16384
#define CWDBUF_MAX_SIZE 512
#define HNAMEBUF_MAX_SIZE 256
#define PROMPT_STRING_MAX_SIZE 1024

//SYSTEM
typedef struct _history
{
  int last;
  Vector cmd_list;
  FILE* history_file;
} History;
void replace_home_with_tilde(char *s);
void swapout_stdout(int* fd, int* backup);
void swapin_stdout(int* fd, int* backup);
int get_prompt(char *prompt_buf);

//FILE
#define TMPNAME_LIST_MAX_SIZE 30
int make_tempfile();
void remove_tempfile_all();
// FILE* open_history_file();

//PARSING
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

//INTERPRET
int interpret(Tokenizer *tokenizer);

#endif
