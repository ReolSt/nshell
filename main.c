#include "nshell.h"
int main()
{
  int fd, backup_stdout, flag=1;
  char buf[BUFFER_MAX_SIZE],
       cwdbuf[CWDBUF_MAX_SIZE],
       hnamebuf[HNAMEBUF_MAX_SIZE];
  char *username;

  memset(buf, 0, BUFFER_MAX_SIZE * sizeof(char));
  memset(cwdbuf, 0, CWDBUF_MAX_SIZE * sizeof(char));
  memset(hnamebuf, 0, CWDBUF_MAX_SIZE * sizeof(char));

  fd = make_tempfile();

  Tokenizer tokenizer;
  while(flag) {
    if(getcwd(cwdbuf, CWDBUF_MAX_SIZE-1)==NULL)
    {
      printf("getcwd : cannot get current working directory\n");
    }

    if(gethostname(hnamebuf, HNAMEBUF_MAX_SIZE) != 0)
    {
      printf("gethostname : cannot get host name\n");
    }

    username = getenv("USER");
    replace_home_with_tilde(cwdbuf);
    printf("%s@%s:%s$ ", username, hnamebuf, cwdbuf);
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
