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

void swapout_stdout(int *fd, int *backup)
{
  *backup = dup(STDOUT_FILENO);
  close(STDOUT_FILENO);
  dup2(*fd, STDOUT_FILENO);
  close(*fd);
}

void swapin_stdout(int *fd, int *backup)
{
  dup2(STDOUT_FILENO, *fd);
  close(STDOUT_FILENO);
  dup2(*backup, STDOUT_FILENO);
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
  sprintf(prompt_buf, "%s%s@%s %s%s%s $ ", GRN, username, hname_buf, YEL, cwd_buf, RESET);
  return 1;
}
