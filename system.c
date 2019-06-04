#include "nshell.h"

void replace_home_with_tilde(char *s)
{
  char *home = getenv("HOME");
  int len = strlen(home);
  if(strncmp(s, home, len) == 0)
  {
    memmove(s + 1, s + len, len);
    s[0] = '~';
  }
}

void swapout_descriptor(int original, int *fd, int *backup)
{
  *backup = dup(original);
  close(original);
  dup2(*fd, original);
  close(*fd);
}

void swapin_descriptor(int original, int *fd, int *backup)
{
  dup2(original, *fd);
  close(original);
  dup2(*backup, original);
  close(*backup);
}

int get_prompt(char *prompt_buf)
{
  static char cwd_buf[CWD_BUF_MAX_SIZE],
              hname_buf[HNAME_BUF_MAX_SIZE];
  if(getcwd(cwd_buf, CWD_BUF_MAX_SIZE-1)==NULL)
  {
    printf("getcwd : cannot get current working directory\n");
    return 0;
  }
  if(gethostname(hname_buf, HNAME_BUF_MAX_SIZE-1) != 0)
  {
    printf("gethostname : cannot get host name\n");
    return 0;
  }
  char *username = getenv("USER");
  replace_home_with_tilde(cwd_buf);
  sprintf(prompt_buf, "%s%s@%s %s%s%s\n$ ", GRN, username, hname_buf, YEL, cwd_buf, RESET);
  return 1;
}
