#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "AirForce/AirForceVector.h"
#include "AirForce/AirForceFileStream.h"
#include "AirForce/AirForceSocket.h"
#include "AirForce/AirForceString.h"

#define Call AirForceCall
#define CallP AirForceCallP

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
  int sock;
  int insertFlag= 1;
  int relayFlag=0;
  char UID[30];
  char message[BUF_SIZE];
  int str_len, recv_len, recv_cnt;
  struct sockaddr_in serv_adr;

  if(argc!=4) {
    printf("Usage : %s <IP> <port> <UID>\n", argv[0]);
    exit(1);
  }
  strcpy(UID,argv[3]);

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
    exit(1);
  }
  AirForceFileStream * socket_file_stream = Call(socket_tcp, GetFileStream);
  if(CallP(socket_file_stream, Printf, "%d, %s\n", insertFlag, argv[3]) <= 0)
  {
    printf("플래그, UID 전송에 오류가 발생하였습니다.\n");
    exit(1);
  }
  else
  {
    printf("데이터 전송 : %d, %s\n", insertFlag, UID);
  }

  while(1)
  {
    if(relayFlag==0)
      {
        while(1)
          {
            if(CallP(socket_file_stream, Gets, message, BUF_SIZE - 1) != NULL)
              {
                printf("From server : %s\n",message);
                if(strcmp(message, "a\n") == 0)
                {
                  printf("recv_client과 연결이 되었습니다.\n");
                  relayFlag=1;
                  break;
                }
                else if(strcmp(message, "b\n") == 0)
                {
                  printf("UID가 중복되었습니다.\n");
                  exit(1);
                }
                else
                {
                  printf("올바르지 않은 플래그입니다.\n");
                  exit(1);
                }
              }
            else
              {
                printf("상대 측 클라이언트와 연결하지 못했습니다.\n");
                Call(socket_tcp, Destroy);
                exit(1);
              }
          }
      }
    if(relayFlag==1)
    {
      while(1)
      {
        int plength = 0;
        if(CallP(socket_file_stream, Gets, message, BUF_SIZE - 1) != NULL)
        {
          plength = atoi(message);
        }
        else
        {
          printf("Prompt String의 라인수를 받아오는 데 실패하였습니다.\n");
          Call(socket_tcp, Destroy);
          exit(1);
        }
        AirForceString prompt_string;
        AirForceString_Initialize(&prompt_string, "", 0);
        for(int i = 0; i < plength; ++i)
        {
          if(CallP(socket_file_stream, Gets, message, BUF_SIZE - 1) != NULL)
          {
            Call(prompt_string, Append, message, strlen(message));
          }
          else
          {
            printf("Prompt String을 받아오는 데 실패하였습니다.\n");
          }
        }
        while(Call(prompt_string, Back) == '\n')
        {
          Call(prompt_string, PopBack);
        }

        const char * prompt_cstring = Call(prompt_string, CStr);
        int is_correct_command = 0;
        char * cmd = NULL;
        while(is_correct_command == 0)
        {
          cmd = readline(prompt_cstring);
          if(strcmp(cmd, "vi") == 0 || strncmp(cmd, "vi ", 3) == 0)
          {
            printf("올바르지 않은 명령어입니다.\n");
            free(cmd);

          }
          else if(strcmp(cmd, "emacs") == 0 || strncmp(cmd, "emacs ", 5) == 0)
          {
            printf("당신은 연봉이 5억입니다.\n");
            free(cmd);
          }
          else
          {
            is_correct_command = 1;
          }
        }
        add_history(cmd);
        Call(prompt_string, Destroy);

        // 혹시 fprintf가 출력부분인가? 맞나보네..
        if(CallP(socket_file_stream, Printf, "%s\n", cmd) < strlen(cmd))
        {
          printf("Command Srting이 정상적으로 보내지지 않았습니다.\n");
          free(cmd);
          exit(1);
        }

        if(strcmp(cmd,"exit") == 0 || strcmp(cmd,"quit") == 0)
        {
          Call(socket_tcp, Destroy);
          return 0;
        }

        free(cmd);

        // 문제의 부분 fgets..
        int dlength = 0;
        if(CallP(socket_file_stream, Gets, message, BUF_SIZE - 1) != NULL)
        {
          dlength = atoi(message);
        }
        else
        {
          printf("서버로부터 output 길이를 받아오는데 실패했습니다.\n");
          Call(socket_tcp, Destroy);
          exit(1);
        }
        int count = 0;
        for(int i = 0; i < dlength; ++i)
        {
          if(CallP(socket_file_stream, Gets, message, BUF_SIZE - 1) != NULL)
          {
            count += 1;
            printf("%s", message);
          }
          else
          {
            printf("데이터를 올바르게 수신하지 못했습니다.\n");
          }
        }
        if(count < dlength)
        {
          printf("서버로부터 모든 데이터를 받아오는 데 실패하였습니다.\n");
          exit(1);
        }
        if(dlength == 0)
        {
          printf("상대 측 클라이언트와의 연결이 끊긴 것 같습니다.\n");
          Call(socket_tcp, Destroy);
          exit(1);
        }
      }
    }
  }
  Call(socket_tcp, Destroy);
  return 0;
}

void error_handling(char *message)
{
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
