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
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);

		if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
			break;

		fprintf(file, message);

		fgets(message, BUF_SIZE, file);
		printf("Message from server: %s", message);
	}
	fclose(file);
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
