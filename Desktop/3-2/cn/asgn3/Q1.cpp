/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/





#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <csignal>
using namespace std;



int fd;
pid_t pid;

void c2phandler(int sigpid)
{
	cout<<"Sig From child"<<endl;
	char buffer[100];
	int chk = read(fd, buffer, 7);
	cout<<buffer<<endl;
	cout<<pid<<endl;
	if(chk != 0)
	{
		kill(pid, SIGUSR2);
	}
}



int main(){
	
	fd = open("file.txt", O_RDONLY);

	signal(SIGUSR1, c2phandler);

	char myfifo[] = "/tmp/myfifo";
	mkfifo(myfifo, 0666);
	pid = fork();
	if(pid == 0)
	{
		dup2(fd, 0);
		char * arg[]={"./q12",NULL};
		execvp(arg[0],NULL);
	}
	cout<<"In parent : "<<getpid()<<endl;
	char buffer[100];
	sprintf(buffer, "%d", getpid());
	int pfd = open(myfifo, O_WRONLY);
	write(pfd, buffer, strlen(buffer) + 1);


	// cout<<"Pro"<<getpid()<<endl;
	//cin>>buffer;

	
	return 0;
}