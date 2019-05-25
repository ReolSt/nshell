#include "nshell.h"
char buf[BUFFER_MAX_SIZE];

#define CWDBUF_MAX_SIZE 1024
char cwdbuf[CWDBUF_MAX_SIZE];

#define HNAMEBUF_MAX_SIZE 512
char hnamebuf[HNAMEBUF_MAX_SIZE];

char *username;

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
    getcwd(buf,BUFFER_MAX_SIZE-1);
    printf("%s\n",buf);
  }
  else if(!strcmp(get_token(tokenizer, 0), "exit"))
  {
    return 0;
  }
  else
  {
    pid_t pid = fork();
    int status;
    if(pid == 0)
    {
      if(execvp(get_token(tokenizer, 0), get_token_list(tokenizer))==-1)
      {
        printf("NShell: %s: command not found\n", get_token(tokenizer, 0));
        kill(getpid(), SIGKILL);
      }
    }
    wait(&status);
  }
  return 1;
}

int main()
{
  int fd, backup_stdout, flag=1;


  fd = make_tempfile();

  Tokenizer tokenizer;
  while(flag) {
    if(getcwd(cwdbuf, CWDBUF_MAX_SIZE-1)==NULL)
    {
      printf("getcwd : cannot get current working directory\n");
    }

    if(gethostname(hnamebuf, HNAMEBUF_MAX_SIZE) != 0)
    {
      printf("gethostname : cannot get host name\n");
    }

    username = getenv("USER");
    replace_home_with_tilde(cwdbuf);
    printf("%s@%s:%s$ ", username, hnamebuf, cwdbuf);
    fflush(stdout);

    fgets(buf,BUFFER_MAX_SIZE-1,stdin);
    tokenize(&tokenizer, buf, strlen(buf));
    backup_stdout = dup(STDOUT_FILENO);
    close(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    close(fd);

    off_t prev = lseek(STDOUT_FILENO, 0, SEEK_CUR);

    if(get_token_count(&tokenizer))
    {
      flag = interpret(&tokenizer);
    }

    off_t current = lseek(STDOUT_FILENO, 0, SEEK_CUR);
    off_t offlen = current - prev;

    lseek(STDOUT_FILENO, prev, SEEK_SET);

    dup2(STDOUT_FILENO, fd);
    close(STDOUT_FILENO);
    dup2(backup_stdout, STDOUT_FILENO);
    close(backup_stdout);

    while(offlen > 0)
    {
      memset(buf, 0, BUFFER_MAX_SIZE * sizeof(char));
      int len = read(fd,buf,offlen);
      offlen -= len;
      printf("%s",buf);
    }
    fflush(stdout);
    lseek(fd, 0, SEEK_END);
  }
  close(fd);
  remove_tempfile_all();
}
