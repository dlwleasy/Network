#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(void)
{

	int fd, fd1;
	char buf[]="Computer Network 2025 ZZANG!\n";
	char read_buf[1024];
	int read_len=0;

	fd=open("data.txt", O_CREAT|O_WRONLY|O_TRUNC);

	printf("file descritor: %d\n",fd);

	write(fd, buf, sizeof(buf)); /char buf[]="Computer Network 2025 ZZANG!\n"; 버퍼내용 fd에 write

	fd1=open("read_data_file.txt",O_RDONLY);   /값은 1씩증가,3부터 증가? -> 처음 디스크립터 3 

		/ 0,1,2, : 각각 존재함
		/ 0 : 키보드 . 표준입력 ,1 : 모니터 . 표준출력, 2 표준에러

	read_len=read(fd1,read_buf,sizeof(read_buf));
	
	/읽어줌, ("read_data_file.txt") 이 내용

	printf("Read result: %s",read_buf);

	close(fd);
	close(fd1);

	return 0;
}
