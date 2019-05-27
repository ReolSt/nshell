#include "nshell.h"
int interpret(InterpretContext *icontext)
{
  Tokenizer *tokenizer = icontext->tokenizer;
  History *history = icontext->history;

  if(!strcmp(tokenizer_get(tokenizer, 0),"cd"))
  {
    char *home = getenv("HOME");
    if(tokenizer_get_count(tokenizer)== 1 || strcmp(tokenizer_get(tokenizer, 1), "~") == 0)
    {
      chdir(home);
    }
    else
    {
      chdir(tokenizer_get(tokenizer, 1));
    }
  }
  else if(!strcmp(tokenizer_get(tokenizer, 0), "pwd"))
  {
    char cwdbuf[CWD_BUF_MAX_SIZE];
    getcwd(cwdbuf,CWD_BUF_MAX_SIZE-1);
    printf("%s\n",cwdbuf);
  }
  else if(!strcmp(tokenizer_get(tokenizer, 0), "history"))
  {
    int count = history_count(history);
    for(int i=0; i < count; ++i)
    {
      printf("  %d  %s", i, history_get_by_index(history, i));
    }
  }
  else if(!strcmp(tokenizer_get(tokenizer, 0), "exit"))
  {
    return 0;
  }
  else
  {
    pid_t pid = fork();
    int status = 0;
    if(pid == -1)
    {
      perror("fork error: ");
      exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
      if(execvp(tokenizer_get(tokenizer, 0), tokenizer_get_list(tokenizer))==-1)
      {
        printf("NShell: %s: command not found\n", tokenizer_get(tokenizer, 0));
        kill(getpid(), SIGKILL);
      }
      _exit(EXIT_SUCCESS);
    }
    else
    {
      if(wait(&status) == -1)
      {
        perror("wait error");
        return 0;
      }
    }
  }
  return 1;
}
