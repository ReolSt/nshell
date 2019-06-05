#include "nshell.h"

int main(int argc, char *argv[])
{
  if(argc!=4)
  {
    printf("Usage : %s <IP> <port> <UID>\n", argv[0]);
    exit(1);
  }
  AirForceSocketTCP socket_tcp;
  if(AirForceSocketTCP_Initialize(&socket_tcp, AirForceProtocolFamily_IPv4, AirForceAddressFamily_IPv4) < 0)
  {
    perror("AirForceSocketTCP_Initialize: ");
    exit(1);
  }
  Call(socket_tcp, SetPort, atoi(argv[2]));
  if(Call(socket_tcp, Connect, argv[1], strlen(argv[1]) < 0))
  {
    perror("AirForceSocketTCP_Connect: ");
    Call(socket_tcp, Destroy);
    exit(1);
  }
  AirForceFileStream * socket_file_stream = Call(socket_tcp, GetFileStream);
  if(CallP(socket_file_stream, Printf, "0, %s\n", argv[3]) <= 0)
  {
    printf("Failed to Transfer Flag, UID\n");
    Call(socket_tcp, Destroy);
    exit(1);
  }

  int stdout_backup, runflag=1;

  char cmd[CMD_BUF_MAX_SIZE],
  output_buf[OUTPUT_BUF_MAX_SIZE],
  prompt_string[PROMPT_STRING_MAX_SIZE];

  Tokenizer tokenizer;
  tokenizer_init(&tokenizer);

  History history;
  history_open(&history);

  InterpretContext icontext;
  interpret_context_init(&icontext, &history, &tokenizer);

  AirForceVector temp_file_list;
  temp_file_list_initialize(&temp_file_list);
  FileInfo * output_file = make_tempfile(&temp_file_list, "r+");
  int output_fd = Call(output_file->file_stream, GetDescriptor);

  while(runflag)
  {
    get_prompt(prompt_string);
    printf("%s", prompt_string);
    fflush(stdout);
    size_t prompt_length = strlen(prompt_string);
    int plength = 1;
    for(size_t i = 0; i < prompt_length; ++i)
    {
      if(prompt_string[i] == '\n')
      {
        plength += 1;
      }
    }

    if(CallP(socket_file_stream, Printf, "%d\n", plength) <= 0)
    {
      printf("An Error occured during plength tranfer\n");
      plength = 0;
      break;
    }

    if(CallP(socket_file_stream, Printf, "%s\n", prompt_string) < prompt_length)
    {
      printf("An Error occured during prompt string tranfer\n");
      break;
    }

    if(CallP(socket_file_stream, Gets, cmd, CMD_BUF_MAX_SIZE - 1) == NULL)
    {
      printf("An Error occured while receiving command string\n");
      printf("Recv Client maybe disconnected.\n");
      break;
    }

    printf("%s\n", cmd);
    int cmd_len = strlen(cmd);

    tokenizer_tokenize(&tokenizer, cmd, cmd_len);
    history_update(&history, cmd, cmd_len);

    swapout_descriptor(fileno(stdout), &output_fd, &stdout_backup);

    off_t prev_stdout = lseek(fileno(stdout), 0, SEEK_CUR);

    if(tokenizer_get_count(&tokenizer) > 0)
    {
      runflag = interpret(&icontext);
    }
    puts("");

    off_t current_stdout = lseek(fileno(stdout), 0, SEEK_CUR);
    off_t offlen_stdout = current_stdout - prev_stdout;

    lseek(fileno(stdout), prev_stdout, SEEK_SET);

    swapin_descriptor(fileno(stdout), &output_fd, &stdout_backup);

    AirForceVector result;
    AirForceVector_Initialize(&result, sizeof(AirForceString));

    AirForceString string;
    char * start_message = "\x1B[36mRecvClient : Command Result\x1B[0m\n";
    AirForceString_Initialize(&string, start_message, strlen(start_message));
    Call(result, PushBack, &string);

    while(offlen_stdout > 0 && Call(output_file->file_stream, Gets, output_buf, OUTPUT_BUF_MAX_SIZE) != NULL)
    {
      AirForceString string;
      AirForceString_Initialize(&string, output_buf, strlen(output_buf));
      Call(result, PushBack, &string);
      printf("%s", output_buf);
      offlen_stdout -= strlen(output_buf);
    }

    size_t vlength = Call(result, Size);
    if(CallP(socket_file_stream, Printf, "%d\n", vlength) <= 0)
    {
      printf("failed to transfer line.\n");
      break;
    }
    for(int i = 0; i < vlength; ++i)
    {
      AirForceString * string = Call(result, At, i);
      const char * cstring = CallP(string, CStr);
      if(CallP(socket_file_stream, Printf, "%s", cstring) < strlen(cstring))
      {
        printf("failed to transfer line.\n");
      }
      CallP(string, Destroy);
    }
    Call(result, Destroy);

    fflush(stdout);

    lseek(output_fd, 0, SEEK_END);
  }
  tokenizer_destroy(&tokenizer);
  history_close(&history);
  remove_temp_file_all(&temp_file_list);
  Call(socket_tcp, Destroy);
}
