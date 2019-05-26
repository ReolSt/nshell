#include "nshell.h"


int main()
{
  int output_fd = make_tempfile(), stdout_backup, flag=1;

  char cmd_buf[CMD_BUF_MAX_SIZE],
       output_buf[OUTPUT_BUF_MAX_SIZE],
       prompt_string[PROMPT_STRING_MAX_SIZE];

  Tokenizer tokenizer;
  History history;
  history_open(&history);
  InterpretContext icontext;
  icontext.tokenizer = &tokenizer;
  icontext.history = &history;

  while(flag) {
    get_prompt(prompt_string);
    printf(prompt_string);
    fflush(stdout);

    fgets(cmd_buf,CMD_BUF_MAX_SIZE-1,stdin);
    history_update(&history, cmd_buf);
    tokenize(&tokenizer, cmd_buf, strlen(cmd_buf));

    swapout_stdout(&output_fd, &stdout_backup);

    off_t prev = lseek(STDOUT_FILENO, 0, SEEK_CUR);


    if(get_token_count(&tokenizer))
    {
      flag = interpret(&icontext);
    }

    off_t current = lseek(STDOUT_FILENO, 0, SEEK_CUR);
    off_t offlen = current - prev;

    lseek(STDOUT_FILENO, prev, SEEK_SET);

    swapin_stdout(&output_fd, &stdout_backup);

    while(offlen > 0)
    {
      memset(output_buf, 0, OUTPUT_BUF_MAX_SIZE * sizeof(char));
      int len = read(output_fd,output_buf,offlen);
      offlen -= len;
      printf("%s",output_buf);
    }
    fflush(stdout);

    lseek(output_fd, 0, SEEK_END);
  }

  close(output_fd);
  history_close(&history);
  remove_tempfile_all();
}
