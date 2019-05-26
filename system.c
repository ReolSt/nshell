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
  static char cwd_buf[CWDBUF_MAX_SIZE],
              hname_buf[HNAMEBUF_MAX_SIZE];
  if(getcwd(cwd_buf, CWDBUF_MAX_SIZE-1)==NULL)
  {
    printf("getcwd : cannot get current working directory\n");
    return false;
  }
  if(gethostname(hname_buf, HNAMEBUF_MAX_SIZE-1) != 0)
  {
    printf("gethostname : cannot get host name\n");
    return false;
  }
  char *username = getenv("USER");
  replace_home_with_tilde(cwd_buf);
  sprintf(prompt_buf, "%s@%s:%s$ ", username, hname_buf, cwd_buf);
  return true;
}
