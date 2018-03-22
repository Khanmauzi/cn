// programm to read text file from two different process simultaneosly


#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

using namespace std;

int main(){
		pid_t pid;
		char *path="/tmp/fifo";
		int fd=open("dup.txt",O_RDONLY);
		pid=fork();
		if(pid==0){
			dup2(fd,0);
			char *arg[]={"./dup2b",NULL};
			execvp(arg[0],arg);
		}
		else{
			int cnt=1;
			int flag;
			mkfifo(path,0666);
			int fd1=open(path,O_WRONLY);
			char buffer[100];
			int i=0;
			while(1){
				char ch[1];
				flag=read(fd,ch,1);
				if(ch[0]=='\n')
					break;
				buffer[i++]=ch[0];
			}
			cout<<"first : "<<buffer<<endl;
			memset(buffer,0,sizeof(buffer));
			char fifo[1];
			fifo[0]='0';
			write(fd1,fifo,strlen(fifo)+1);
			close(fd1);
			while(flag!=0){
				fd1=open(path,O_RDONLY);
				read(fd1,fifo,1);
				i=0;
				while(1){
					char ch[1];
					flag=read(fd,ch,1);
					if(ch[0]=='\n')
						break;
					buffer[i++]=ch[0];
				}
			cout<<"first : "<<buffer<<endl;
			memset(buffer,0,sizeof(buffer));
			close(fd1);
			fd1=open(path,O_WRONLY);
			write(fd1,fifo,strlen(fifo)+1);
			close(fd1);
			}
		}
		return 0;
}