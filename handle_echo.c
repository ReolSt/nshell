#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
	FILE *file;
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
	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock==-1)
	{
		error_handling("socket() error");
	}
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("connect() error!");
	else
	{
		printf("Conntected.... \n" );
	}

	file = fdopen(sock, "r+");
	if(file == NULL){
		printf("fdopen() error\n");
	}
	setvbuf(file, NULL, _IOLBF, 0);

	sprintf(message, "%d, %s\n", insertFlag, UID);

	if(fprintf(file, "%s", message) == 1){
		printf("fprintf() error \n");
	}
	else{
		printf("데이터 전송 : %s \n", message);
	}
	while(1)
	{
		if(relayFlag==0)
		{
			while(1)
			{
				// 여기가 fgets != NULL 였을 때, printf들을 통해 검토해본 결과, 정상동작하지 않아, 일단 read로 바꿨다.
				if((str_len=read(sock,message,strlen(message)))!=0)
				{
					message[str_len]='\0';
					printf("From server:%s\n",message);
					printf("recv_client과 연결이 되었습니다.\n");
					relayFlag=1;
					break;
				}
				else
				{	
					printf("err:TIME_OUT | 상대 측 클라이언트와 연결하지 못했습니다.\n");
					return -1;
				}
			}
		}
		if(relayFlag==1)
		{
			while(1)
			{
				fputs("Input message(Q to quit): ", stdout);
				fgets(message, BUF_SIZE, stdin);
	
				if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
				{
					fclose(file);
					return 0;
				}
	
	
				fprintf(file, message);
	
				if(fgets(message, BUF_SIZE, file)!=NULL)
					printf("Message from server: %s", message);
				else
				{
					printf("상대 측 클라이언트와의 연결이 끊겼습니다.\n");
					relayFlag=0;
					break;
				}
			}
		}
	}
	fclose(file);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
