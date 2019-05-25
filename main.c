#include "nshell.h"

void get_prompt(char *prompt)
{
  static char cwdbuf[CWDBUF_MAX_SIZE],
              hnamebuf[HNAMEBUF_MAX_SIZE];
  if(getcwd(cwdbuf, CWDBUF_MAX_SIZE-1)==NULL)
  {
    printf("getcwd : cannot get current working directory\n");
  }
  if(gethostname(hnamebuf, HNAMEBUF_MAX_SIZE-1) != 0)
  {
    printf("gethostname : cannot get host name\n");
  }
  char *usename = getenv("USER");
  replace_home_with_tilde(cwdbuf);
  sprintf(prompt, "%s@%s:%s$ ", usename, hnamebuf, cwdbuf);
}

int main()
{
  int fd = make_tempfile(), backup_stdout, flag=1;
  char buf[BUFFER_MAX_SIZE],
     prompt_string[PROMPT_STRING_MAX_SIZE];

  Tokenizer tokenizer;

  while(flag) {
    get_prompt(prompt_string);
    printf(prompt_string);
    fflush(stdout);

    fgets(buf,BUFFER_MAX_SIZE-1,stdin);
    tokenize(&tokenizer, buf, strlen(buf));
    
    swapin_stdout(&fd, &backup_stdout);
    off_t prev = lseek(STDOUT_FILENO, 0, SEEK_CUR);


    if(get_token_count(&tokenizer))
    {
      flag = interpret(&tokenizer);
    }


    off_t current = lseek(STDOUT_FILENO, 0, SEEK_CUR);
    off_t offlen = current - prev;

    lseek(STDOUT_FILENO, prev, SEEK_SET);

    swapout_stdout(&fd, &backup_stdout);
    while(offlen > 0)
    {
      memset(buf, 0, BUFFER_MAX_SIZE * sizeof(char));
      int len = read(fd,buf,offlen);
      offlen -= len;
      printf("%s",buf);
    }
    fflush(stdout);
    lseek(fd, 0, SEEK_END);
  }
  close(fd);
  remove_tempfile_all();
}
