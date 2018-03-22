//signal and wait system call practice




#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

using namespace std;


int pid;

void FN1(int sigpid){
	cout<<"call from child process "<<endl;
	cout<<"calling child process "<<endl;
	kill(pid,SIGUSR2);
}
int main(){
	signal(SIGUSR1,FN1);

	pid=fork();
	if(pid==0){
		char *argv[]={"./signal2",NULL};
		execvp(argv[0],argv);
	}
	char *path="/tmp/s";
	mkfifo(path,0666);
	int fd=open(path,O_WRONLY);
	char buffer[100];
	sprintf(buffer,"%d",getpid());
	write(fd,buffer,strlen(buffer)+1);
	//cout<<"parent id : "<<buffer<<"   child id "<<pid<<endl;
	close(fd);
	while(1);
}