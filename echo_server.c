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
	int serv_sock, clnt_sock;
	char message[BUF_SIZE];
	int str_len, i;
	
	struct sockaddr_in serv_adr; //내가 접속할 서버의 정보 
	struct sockaddr_in clnt_adr;
	socklen_t clnt_adr_sz; 
	//clnt_addr 구조체(address_in) 변수 call by reference로 넘기게 되면 , 접근요청을 클라이언트의 ip,port번호가 채워짐, 
	//
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);   
	if(serv_sock==-1)
		error_handling("socket() error");
	

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));//[1]루프백 주소 -> 정수값으로 inet_Addr = network order으로 변경 24분

	//bind함수
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	

	//listen 함수 ; 2개로 나눠지는건 맞는데 그러면 다른게 전달되는거 아닌가  
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	clnt_adr_sz=sizeof(clnt_adr);

	//이중루프가 돌아감 
	for(i=0; i<5; i++)
	{
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		if(clnt_sock==-1)
			error_handling("accept() error");
		else
			printf("Connected client %d \n", i+1);
	
		while((str_len=read(clnt_sock, message, BUF_SIZE))!=0)
			write(clnt_sock, message, str_len);

	close(serv_sock);
	return 0;
		close(clnt_sock);
	}

}
//뒤늦게 남아있는거 처리하는거는 버퍼가 처리되는거 ;
// backlog < for이면 back에 저장해서 처리가능 ......................

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
