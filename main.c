#include "nshell.h"

int main(int argc, char *argv[])
{
  int flag=1;
  char prompt_string[PROMPT_STRING_MAX_SIZE];

  Tokenizer tokenizer;
  tokenizer_init(&tokenizer);

  History history;
  history_open(&history);

  InterpretContext icontext;
  interpret_context_init(&icontext, &history, &tokenizer);

  while(flag) {
    get_prompt(prompt_string);
    char *cmd = readline(prompt_string);
    int cmd_len = strlen(cmd);

    tokenizer_tokenize(&tokenizer, cmd, cmd_len);
    add_history(cmd);
    history_update(&history, cmd, cmd_len);
    free(cmd);

    if(tokenizer_get_count(&tokenizer) > 0)
    {
      flag = interpret(&icontext);
    }
  }
  tokenizer_destroy(&tokenizer);
  history_close(&history);
  remove_tempfile_all();
}
