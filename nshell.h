#ifndef NSHELL_H
#define NSHELL_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "AirForce/AirForceSocket.h"
#include "AirForce/AirForceCall.h"
#include "AirForce/AirForceVector.h"
#include "AirForce/AirForceString.h"
#include "AirForce/AirForceFileStream.h"

#define Call AirForceCall
#define CallP AirForceCallP

#define CMD_BUF_MAX_SIZE 512
#define OUTPUT_BUF_MAX_SIZE 16384
#define CWD_BUF_MAX_SIZE 512
#define HNAME_BUF_MAX_SIZE 256
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
void swapout_descriptor(int original, int *fd, int *backup);
void swapin_descriptor(int original, int *fd, int *backup);
int get_prompt(char *prompt_buf);

//FILE
#define TMPNAME_LIST_MAX_SIZE 30
typedef struct _File_Info
{
  AirForceFileStream file_stream;
  AirForceString name;
  int is_open;
} FileInfo;
void temp_file_list_initialize(AirForceVector * temp_file_list);
FileInfo * make_tempfile(AirForceVector * temp_file_list, const char * mode);
void remove_temp_file_all(AirForceVector * temp_file_list);
void close_temp_file_all(AirForceVector * temp_file_list);

typedef struct _History
{
  int size;
  AirForceString history_path;
  AirForceVector cmd_list;
  FILE *history_file;
} History;

int history_open(History *history);
void history_close(History *history);
const char* history_get_by_index(History *history, int index);
const char* hitory_get_last(History *history);
int history_count(History *history);
void history_update(History *history, const char *cmd, size_t len);

//PARSING
#define TOKEN_MAX_COUNT 64
typedef struct _Tokenizer
{
  char *token_ptr_list[TOKEN_MAX_COUNT];
  AirForceVector token_list;
} Tokenizer;

void tokenizer_init(Tokenizer *tokenizer);
void tokenizer_tokenize(Tokenizer *tokenizer, char *s, size_t len);
const char *tokenizer_get(Tokenizer *tokenizer, int index);
char * const *tokenizer_get_list(Tokenizer *tokenizer);
int tokenizer_get_count(Tokenizer *tokenizer);
void tokenizer_clear(Tokenizer *tokenizer);
void tokenizer_destroy(Tokenizer *tokenizer);

//INTERPRET
typedef struct _Interpret_Context
{
  History *history;
  Tokenizer *tokenizer;
} InterpretContext;
void interpret_context_init
(
  InterpretContext *icontext,
  History *history,
  Tokenizer *tokenizer;
);
int interpret(InterpretContext *icontext);

#endif
