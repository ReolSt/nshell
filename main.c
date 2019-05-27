#include "nshell.h"

int main(int argc, char *argv[])
{
  int output_fd = make_tempfile(), stdout_backup, flag=1;

  char output_buf[OUTPUT_BUF_MAX_SIZE],
       prompt_string[PROMPT_STRING_MAX_SIZE];

  Tokenizer tokenizer;
  tokenizer_init(&tokenizer);

  History history;
  history_open(&history);

  InterpretContext icontext;
  icontext.tokenizer = &tokenizer;
  icontext.history = &history;

  while(flag) {
    get_prompt(prompt_string);
    char *cmd = readline(prompt_string);
    int cmd_len = strlen(cmd);

    tokenizer_tokenize(&tokenizer, cmd, cmd_len);
    add_history(cmd);
    history_update(&history, cmd, cmd_len);

    if(tokenizer_get_count(&tokenizer) > 0)
    {
      flag = interpret(&icontext);
    }

    free(cmd);
  }
  tokenizer_destroy(&tokenizer);
  close(output_fd);
  history_close(&history);
  remove_tempfile_all();
}
