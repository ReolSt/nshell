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
  history->size = 0;
  history->history_file = NULL;
  char *home = getenv("HOME");
  char history_path[256];
  sprintf(history_path, "%s/.nshell_history", home);
  FILE* history_file = fopen(history_path, "a+");
  if(history_file == NULL)
  {
    return 0;
  }
  history->history_file = history_file;
  AirForceString_Initialize(&(history->history_path), history_path, strlen(history_path));
  AirForceVector_Initialize(&(history->cmd_list), sizeof(AirForceString));
  char cmd_buf[CMD_BUF_MAX_SIZE];
  fseek(history->history_file, 0, SEEK_SET);
  while(fgets(cmd_buf, CMD_BUF_MAX_SIZE - 1, history_file) != NULL)
  {
    AirForceString cmd_string;
    AirForceString_Initialize(&cmd_string, cmd_buf, strlen(cmd_buf));
    Call(history->cmd_list, PushBack, &cmd_string);
    history->size += 1;
  }
  return 1;
}

void history_close(History * history)
{
  Call(history->history_path, Destroy);
  int len = Call(history->cmd_list, Size);
  for(int i = 0; i < len; ++i)
  {
    AirForceString * string = Call(history->cmd_list, At, i);
    CallP(string, Destroy);
  }
  Call(history->cmd_list, Destroy);
  if(history->history_file != NULL)
  {
    fclose(history->history_file);
  }
  history->size = 0;
  history->history_file = NULL;
}

const char * history_get_by_index(History *history, int index)
{
  AirForceString * string = Call(history->cmd_list ,At, index);
  return CallP(string, CStr);
}

const char * hitory_get_last(History *history)
{
  AirForceString * string = Call(history->cmd_list, At, history->size - 1);
  return CallP(string, CStr);
}

int history_count(History *history)
{
  return history->size;
}

void history_update(History *history, const char *cmd, size_t len)
{
  if(len)
  {
      AirForceString cmd_string;
      AirForceString_Initialize(&cmd_string, cmd, len);
      Call(cmd_string, PushBack, '\n');
      Call(history->cmd_list, PushBack, &cmd_string);
      fprintf(history->history_file, "%s\n", Call(cmd_string, CStr));
      history->size += 1;
  }
}
