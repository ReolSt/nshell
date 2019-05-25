#include "nshell.h"
int interpret(Tokenizer *tokenizer)
{
  if(!strcmp(get_token(tokenizer, 0),"cd"))
  {
    char *home = getenv("HOME");
    if(get_token_count(tokenizer)== 1 || strcmp(get_token(tokenizer, 1), "~") == 0)
    {
      chdir(home);
    }
    else
    {
      chdir(get_token(tokenizer, 1));
    }
  }
  else if(!strcmp(get_token(tokenizer, 0),"pwd"))
  {
    char cwdbuf[CWDBUF_MAX_SIZE];
    getcwd(cwdbuf,CWDBUF_MAX_SIZE-1);
    printf("%s\n",cwdbuf);
  }
  else if(!strcmp(get_token(tokenizer, 0), "exit"))
  {
    return 0;
  }
  else
  {
    pid_t pid = fork();
    int status;
    if(pid == -1)
    {
      perror("fork error: ");
      exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
      if(execvp(get_token(tokenizer, 0), get_token_list(tokenizer))==-1)
      {
        printf("NShell: %s: command not found\n", get_token(tokenizer, 0));
        kill(getpid(), SIGKILL);
      }
      _exit(EXIT_SUCCESS);
    }
    else
    {
      if(wait(&status) == -1)
      {
        perror("wait error");
        return 1;
      }
      if (WIFEXITED(status) == 0) {
        printf("Child process did not exit normally.");
      }
    }
  }
  return 1;
}
