/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/


#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <csignal>
#include <stdlib.h>
using namespace std;


int ppid;
void p2chandler(int pid)
{
	cout<<"From Parent"<<endl;
	char buffer[100];
	int chk = read(0, buffer, 7);
	cout<<buffer<<"l"<<endl;
	if(chk != 0)
	{
		kill(ppid, SIGUSR1);
	}
}

int main(){
	char myfifo[] = "/tmp/myfifo";
	int nfd = open(myfifo, O_RDONLY);
	char buffer[100];
	read(nfd, buffer, 100);
	signal(SIGUSR2, p2chandler);
	// cout<<"bac"<<getpid()<<endl;
	cout<<"In child : "<<getppid()<<endl;
	ppid = atoi(buffer);
	// cout<<ppid<<endl;
	kill(ppid, SIGUSR1);

	int i= 3;
	while(i)
	{
		sleep(1);
		i--;
	}

	cout<<"child dies"<<endl;
	return 0;
}