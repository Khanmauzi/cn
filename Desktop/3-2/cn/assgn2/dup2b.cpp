// programm to read text file from two different process simultaneosly

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

using namespace std;
int main(){
	char *path="/tmp/fifo";
	mkfifo(path,0666);
	int flag;
	char buffer[100];
	int i=0;
	while(flag!=0){
		int fd=open(path,O_RDONLY);
		char fifo[1];
		fifo[0]='0';
		read(fd,fifo,1);
		char ch[1];
		int i=0;
		while(1){
			flag=read(0,ch,1);
			if(ch[0]=='\n')
				break;
			buffer[i++]=ch[0];

		}
		cout<<"second : "<<buffer<<endl;
		memset(buffer,0,sizeof(buffer));
		close(fd);
		fd=open(path,O_WRONLY);
		write(fd,fifo,strlen(fifo)+1);
		close(fd);
	}
	return 0;
}