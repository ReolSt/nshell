#include "nshell.h"
char tmpname_list[TMPNAME_LIST_MAX_SIZE][24];
int tmpname_list_size;

int make_tempfile() {
  static char template[24]="/tmp/NshellXXXXXX";
  strncpy(tmpname_list[tmpname_list_size], template, 24);
  return mkstemp(tmpname_list[tmpname_list_size++]);
}
void remove_tempfile_all()
{
  for(int i=0;i<tmpname_list_size;i++)
    {
      remove(tmpname_list[i]);
    }
}

int history_open(History *history)
{
  char *home = getenv("HOME");
  char history_path[256];
  sprintf(history_path, "%s/.nshell_history", home);
  FILE* history_file = fopen(history_path, "a+");
  history->history_file = history_file;
  return history_file != NULL ? true : false;
}

void history_get_all(History *history)
{

}
void history_get_by_index(History *history, int index)
{

}

void hitory_get_last()
{

}

void history_update(char *cmd)
{

}
