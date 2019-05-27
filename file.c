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
  if(history_file == NULL)
  {
    return 0;
  }
  history->history_file = history_file;
  string_init(&(history->history_path), history_path, strlen(history_path));
  vector_init(&(history->cmd_list), sizeof(String));
  char cmd_buf[CMD_BUF_MAX_SIZE];
  fseek(history->history_file, 0, SEEK_SET);
  while(fgets(cmd_buf, CMD_BUF_MAX_SIZE - 1, history_file) != NULL)
  {
    String cmd_string;
    string_init(&cmd_string, cmd_buf, strlen(cmd_buf));
    vector_push_back(&(history->cmd_list), &cmd_string);
    history->size += 1;
  }
  return 1;
}

void history_close(History *history)
{
  string_destroy(&(history->history_path));
  int len = vector_size(&(history->cmd_list));
  for(int i = 0; i < len; ++i)
  {
    string_destroy(vector_at(&(history->cmd_list), i));
  }
  vector_destroy(&(history->cmd_list));
  if(history->history_file != NULL)
  {
    fclose(history->history_file);
  }
}

const char* history_get_by_index(History *history, int index)
{
  return string_c_str(vector_at(&(history->cmd_list),index));
}

const char* hitory_get_last(History *history)
{
  return string_c_str(vector_at(&(history->cmd_list), history->size - 1));
}

int history_count(History *history)
{
  return history->size;
}

void history_update(History *history, const char *cmd, size_t len)
{
  if(len)
  {
      String cmd_string;
      string_init(&cmd_string, cmd, len);
      vector_push_back(&(history->cmd_list), &cmd_string);
      fprintf(history->history_file, "%s\n", string_c_str(&cmd_string));
      history->size += 1;
  }
}
