#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define MAX_CNT 100
#define BUF_SIZE 100



typedef struct clnt_userdata{
  char UID[30];
  int socket_index;
  ;
}clnt_userdata;

void error_handling(char *msg);
void *Relay_clnt(void *arg);
void close_handle_clnt(int sock, int index);
void close_recv_clnt(int sock, int index);
void pop_UID_array(char str[]);


int recv_cnt  = 0; // 접속한 recv클라이언트 숫자
int handle_cnt = 0; // 접속한 handle클라이언트 숫자

clnt_userdata handle_userdata[MAX_CNT];
clnt_userdata recv_userdata[MAX_CNT];

int recv_socks[MAX_CNT];
int handle_socks[MAX_CNT]; // 구분하기전에 들어오는 배열.

//생성된 쓰레드의 UID를 저장하는 배열
char thread_UID[100][30];
int thread_cnt = 0;

pthread_mutex_t mutex;


int main(int argc, char *argv[]){
  int serv_sock, clnt_sock;
  int insertFlag = -1;
  int errorFlag = 0;
  int clnt_adr_sz;
  int str_len = 0;


  struct sockaddr_in serv_adr, clnt_adr;
  char buffer[BUF_SIZE];
  char UID[30];
  pthread_t thread_id;

  if(argc != 2){
    printf("Usage : %s <port> \n", argv[0]);
    exit(1);
  }


  pthread_mutex_init(&mutex, NULL);
  serv_sock = socket(PF_INET, SOCK_STREAM, 0);

  printf("Socket : %d \n", serv_sock);

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_adr.sin_port = htons(atoi(argv[1]));

  if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
  error_handling("bind() error");

  if(listen(serv_sock, 5) == -1)
  error_handling("listen() error");

  while(1)
  {
    errorFlag = 0;

    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
    printf("client conntected... \n");

    // fdopen을 이용한 고수준 파일 입출력..
    FILE *file = fdopen(clnt_sock, "r+");
    if(file == NULL){
      error_handling("fdopen Error");
    }

	if(fgets(buffer, BUF_SIZE, file) == NULL)
		error_handling("fgets Error");

	if(sscanf(buffer, "%d, %s\n", &insertFlag, UID) == -1 ){
		error_handling("sscanf Error");
	}
	

	printf("insertFlag, UID : %d, %s \n", insertFlag, UID);


    // 1, handle sock 일때,그에 맞는 구조체 배열의 UID를 확인한다.
    if(insertFlag){
      pthread_mutex_lock(&mutex);
      for(int i = 0; i < handle_cnt; i++){
        if(strcmp(UID, handle_userdata[i].UID) == 0){
          printf("handle UID 중복, 다른 UID를 사용하십시오. \n");
          errorFlag = 1;
		}
      }
      pthread_mutex_unlock(&mutex);
      if(errorFlag != 1){
	pthread_mutex_lock(&mutex);

        handle_socks[handle_cnt] = clnt_sock;
        strcpy(handle_userdata[handle_cnt].UID, UID);
        handle_userdata[handle_cnt].socket_index = handle_cnt;
        handle_cnt++;
        printf("handle client conntected : %d \n", handle_cnt);

	pthread_mutex_unlock(&mutex);
      }
    }
    // recv 소켓 일 때,
    else{
      pthread_mutex_lock(&mutex);
      for(int i = 0; i < recv_cnt; i++){
        if(strcmp(UID, recv_userdata[i].UID) == 0){
          errorFlag = 1;
          printf("recv UID 중복, 다른 UID를 사용하십시오.\n");
          break;
        }
      }
      pthread_mutex_unlock(&mutex);
      // 중복 아니라면,
      if(errorFlag != 1)
      {
	pthread_mutex_lock(&mutex);

        recv_socks[recv_cnt] = clnt_sock;
        strcpy(recv_userdata[recv_cnt].UID, UID);
        recv_userdata[recv_cnt].socket_index = recv_cnt;
        recv_cnt++;
        printf("recv client conntected : %d \n", recv_cnt);

	pthread_mutex_unlock(&mutex);
      }
    }

    printf("\n==========Thread 확인==============\n");
    pthread_mutex_lock(&mutex);
    for(int i = 0; i < thread_cnt; i++){
      // 이미 해당하는 UID에 맞는 쓰레드를
      printf(" UID : %s , thread_UID[%d] : %s \n", UID, i , thread_UID[i]);
      if(strcmp(UID, thread_UID[i]) == 0){
        errorFlag = 1;
        printf("thread UID 중복, 쓰레드 생성 안한다. \n ");
        break;
      }
    }
    pthread_mutex_unlock(&mutex);
    printf("\n\n");


	// 쓰레드를 생성시키면 안되는 경우
    if(errorFlag == 1){
      printf("Thread Create Disband, Go to Next Routine \n");
      continue;
    }

    printf("thread_UID에 넣을 UID 값 : %s \n", UID);
    pthread_mutex_lock(&mutex);
    strcpy(thread_UID[thread_cnt++], UID);
    pthread_mutex_unlock(&mutex);
    pthread_create(&thread_id, NULL, Relay_clnt, (void*)UID);
    pthread_detach(thread_id);
    printf("matching Thread num : %d \n", thread_cnt);
  }

  close(serv_sock);
  return 0;
}



void* Relay_clnt(void* str)
{
  char UID[30];
  char errorMsg[30] = "Connect End";
  clnt_userdata recv_user;
  clnt_userdata handle_user;


  int recv_sock;
  int handle_sock;
  int time=0;
  char out='a';

  char command_buf[BUF_SIZE];
  char output_buf[1000];
  int command_len;
  int output_len;

  strcpy(UID, (char*)str);

  while(1)
  {
    int i=0;

    pthread_mutex_lock(&mutex);


    for(i=0; i<recv_cnt;i++)
    {
      //recv_clnt에 UID 있는 지 검사
      if(strcmp(UID,recv_userdata[i].UID)==0)
      {
        recv_user=recv_userdata[i];
        break;
      }
    }
    pthread_mutex_unlock(&mutex);

    pthread_mutex_lock(&mutex);
    for(i=0;i<handle_cnt;i++)
    {
      //hanldle_clnt에 UID 있는 지 검사
      if(strcmp(UID,handle_userdata[i].UID)==0)
      {
        handle_user=handle_userdata[i];
        break;
      }
    }
    pthread_mutex_unlock(&mutex);

    if((strcmp(UID,handle_user.UID)==0)&&(strcmp(UID,recv_user.UID)==0))
    {
      break;
    }


    sleep(1);

    if(time==300)
    {
      printf("쓰레드 대기시간 초과");
      return NULL;
    }
  }

  recv_sock=recv_socks[recv_user.socket_index];
  handle_sock=handle_socks[handle_user.socket_index];
  if(command_len=write(handle_sock,&out,sizeof(out))!=0)
	 printf("handler_clnt flag변환\n"); 

  while(1)
  {
    memset(&command_buf, 0, sizeof(command_buf));
    if((command_len=read(handle_sock,command_buf,BUF_SIZE))!=0)
    {
      printf("recv로 송신 : %s \n",command_buf);
      write(recv_sock,command_buf,command_len);
    }
    else{
      printf("handle Client 접속종료\n");
	  close_handle_clnt(handle_sock, handle_user.socket_index);
      break;
	}

    memset(&output_buf, 0, sizeof(output_buf));
    if((output_len=read(recv_sock,output_buf,1000))!=0)
    {
      printf("handle로 송신 : %s \n", output_buf);
      write(handle_sock,output_buf,output_len);
    }
    else{
      printf("recv Client 접속종료\n");
	  printf("handle로 종료 메시지 송신 : %s \n", errorMsg);
      write(handle_sock, errorMsg, sizeof(errorMsg));
	  close_recv_clnt(recv_sock, recv_user.socket_index);
      break;
    }
  }

  // 쓰레드 종료 단계, 중계되고 있는 소켓들 종료, 배열 정리
  pthread_mutex_lock(&mutex);
  pop_UID_array(UID);

  printf("Thread End : handle_cnt : %d, recv_cnt : %d, thread_cnt : %d \n\n\n", handle_cnt, recv_cnt, thread_cnt);
  pthread_mutex_unlock(&mutex);

  return NULL;
}

void error_handling(char *msg){
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}

void close_handle_clnt(int sock, int index)
{
  int h_sock=sock;
  int i=index;

  for(i;i<handle_cnt-1;i++)
  {
    handle_socks[i]=handle_socks[i+1];
    handle_userdata[i]=handle_userdata[i+1];
  }
  handle_cnt--;
  close(h_sock);
}

void close_recv_clnt(int sock, int index)
{
  int r_sock=sock;
  int i=index;

  for(i;i<recv_cnt-1;i++)
  {
    recv_socks[i]=recv_socks[i+1];
    recv_userdata[i]=recv_userdata[i+1];
  }
  recv_cnt--;
  close(r_sock);
}

void pop_UID_array(char str[])
{
  char UID[30];
  strcpy(UID, str);
  int index=0;
  int i=0;

  for(i=0;i<thread_cnt;i++)
  {
    if(strcmp(UID,thread_UID[i])==0)
    {
      index=i;
    }
  }
  for(i=index;i<thread_cnt-1;i++)
  {
    strcpy(thread_UID[i], thread_UID[i+1]);
  }
  thread_cnt--;
}
