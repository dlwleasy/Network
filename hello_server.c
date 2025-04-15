#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message); 

int main(int argc, char *argv[])
{
	int serv_sock;//소켛만들고 리턴값
	int clnt_sock;

	struct sockaddr_in serv_addr; //바인드함수에 넘겨줄 구조체
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char message[]="Hello World!";
	
	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0); //소켓은 tcp,iv]pv4
	if(serv_sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));//0으로 안 채워도되는이유 : 자동으로 0으로 세팅된 상태
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); //INADDR_AN:자기자신을 의미하는 거: 바뀐주소를 바로바로 하기 위히ㅐ서
	//구조체안에 구조체
	serv_addr.sin_port=htons(atoi(argv[1]));
	//16비트의 포트번호를 넣어줌 ,argv[1] : sin_port로 넘어감
	// argv[0]현위치 argv[1]포트번호? .은 main함수에 argv[2]
	//
	
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1 ) //sockaddr을 이용해서 타입캐스팅이용?
		error_handling("bind() error");
	
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	clnt_addr_size=sizeof(clnt_addr);  
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock==-1)
		error_handling("accept() error");  
	
	write(clnt_sock, message, sizeof(message));
	close(clnt_sock);	
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
