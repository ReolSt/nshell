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
