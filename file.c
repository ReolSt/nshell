#include "nshell.h"
char tmpname_list[TMPNAME_LIST_MAX_SIZE][24];
int tmpname_list_size;

int make_tempfile() {
  static char template[24]="/tmp/NshellXXXXXX";
  strcpy(tmpname_list[tmpname_list_size],template);
  return mkstemp(tmpname_list[tmpname_list_size++]);
}
void remove_tempfile_all()
{
  for(int i=0;i<tmpname_list_size;i++)
    {
      remove(tmpname_list[i]);
    }
}
