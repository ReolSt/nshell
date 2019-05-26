#ifndef NSHELL_H
#define NSHELL_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "core/Vector.h"
#include "core/String.h"

#define CMD_BUF_MAX_SIZE 256
#define OUTPUT_BUF_MAX_SIZE 16384
#define CWDBUF_MAX_SIZE 512
#define HNAMEBUF_MAX_SIZE 256
#define PROMPT_STRING_MAX_SIZE 1024

//SYSTEM
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
void replace_home_with_tilde(char *s);
void swapout_stdout(int *fd, int *backup);
void swapin_stdout(int *fd, int *backup);
int get_prompt(char *prompt_buf);

//FILE
#define TMPNAME_LIST_MAX_SIZE 30
int make_tempfile();
void remove_tempfile_all();

typedef struct _history
{
  int size;
  String history_path;
  Vector cmd_list;
  FILE *history_file;
} History;
int history_open(History *history);
void history_close(History *history);
const char* history_get_by_index(History *history, int index);
const char* hitory_get_last(History *history);
int history_count(History *history);
void history_update(History *history, const char *cmd);

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
char *get_token(Tokenizer *tokenizer, int index);
char **get_token_list(Tokenizer *tokenizer);
int get_token_count(Tokenizer *tokenizer);

//INTERPRET
typedef struct _interpret_context
{
  History *history;
  Tokenizer *tokenizer;
} InterpretContext;
int interpret(InterpretContext *icontext);

#endif
