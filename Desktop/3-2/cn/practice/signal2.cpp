//signal and wait system call practice


#include <iostream>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

using namespace std;

int pid;

void FN2(int sigpid){
	cout<<"signal from parent "<<endl;
	cout<<"sending signal to parent "<<endl;
	kill(pid,SIGUSR1);
}
int main(){
	signal(SIGUSR2,FN2);
	char *path="/tmp/s";
	mkfifo(path,0666);
	char buffer[100];
	int fd=open(path,O_RDONLY);
	read(fd,buffer,100);
	pid=atoi(buffer);
	//cout<<"parent id : "<<pid<<"   child id "<<getpid()<<endl;
	kill(pid,SIGUSR1);
	int i=3;
	while(i){
		sleep(1);
		i--;
	}
	return 0;
}