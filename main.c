#include "nshell.h"

int main()
{
  if(argc!=4) {
		printf("Usage : %s <IP> <port> <UID>\n", argv[0]);
		exit(1);
	}

  SocketTCP socket_tcp;
  if(socket_tcp_create(&socket_tcp, ProtocolFamily_IPv4, AddressFamily_IPv4) < 0)
  {
    perror("socket_tcp_create: ");
    exit(1);
  }
  socket_tcp_set_port(&socket_tcp, atoi(argv[2]));
  if(socket_tcp_connect(&socket_tcp, argv[1], strlen(argv[1])) < 0)
  {
    perror("socket_tcp_connect: ");
    exit(1);
  }
  FILE *socket_file = socket_tcp_get_file(&socket_tcp);
  fprintf(socket_file, "%c", '0');
  fprintf(socket_file, "%s", argv[3]);

  int output_fd = make_tempfile(), stdout_backup, flag=1;

  char output_buf[OUTPUT_BUF_MAX_SIZE],
       prompt_string[PROMPT_STRING_MAX_SIZE];

  Tokenizer tokenizer;
  tokenizer_init(&tokenizer);

  History history;
  history_open(&history);

  InterpretContext icontext;
  icontext.tokenizer = &tokenizer;
  icontext.history = &history;

  while(flag) {
    get_prompt(prompt_string);
    char *cmd = readline(prompt_string);
    int cmd_len = strlen(cmd);
    tokenize(&tokenizer, cmd, cmd_len);
    add_history(cmd);
    history_update(&history, cmd, cmd_len);
    swapout_stdout(&output_fd, &stdout_backup);

    off_t prev = lseek(STDOUT_FILENO, 0, SEEK_CUR);
    if(get_token_count(&tokenizer) > 0)
    {
      flag = interpret(&icontext);
    }

    free(cmd);


    off_t current = lseek(STDOUT_FILENO, 0, SEEK_CUR);
    off_t offlen = current - prev;

    lseek(STDOUT_FILENO, prev, SEEK_SET);

    swapin_stdout(&output_fd, &stdout_backup);

    while(offlen > 0)
    {
      memset(output_buf, 0, OUTPUT_BUF_MAX_SIZE * sizeof(char));
      int len = read(output_fd,output_buf,offlen);
      offlen -= len;
      printf("%s\n",output_buf);
    }
    fflush(stdout);

    lseek(output_fd, 0, SEEK_END);
  }

  tokenizer_destroy(&tokenizer);
  close(output_fd);
  history_close(&history);
  remove_tempfile_all();

  socket_tcp_close(&socket);
}
