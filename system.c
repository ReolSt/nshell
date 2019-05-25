#include "nshell.h"

void replace_home_with_tilde(char *s)
{
  char *home = getenv("HOME");
  int len = strlen(home);
  if(strncmp(s, home, len) == 0)
  {
    strcpy(s + 1, s + len);
    s[0] = '~';
  }
}

void swapin_stdout(int *fd, int *backup)
{
  *backup = dup(STDOUT_FILENO);
  close(STDOUT_FILENO);
  dup2(*fd, STDOUT_FILENO);
  close(*fd);
}

void swapout_stdout(int *fd, int *backup)
{
  dup2(STDOUT_FILENO, *fd);
  close(STDOUT_FILENO);
  dup2(*backup, STDOUT_FILENO);
  close(*backup);
}
