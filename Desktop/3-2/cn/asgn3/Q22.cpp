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
#include <stdlib.h>
#include <sys/shm.h>
using namespace std;

int *ptr;
int p1id, y;

void sigusr1handler(int sigid)
{
	cout<<sigid<<endl;
	cout<<"In p2"<<endl;
	y = ptr[1];
	cout<<"Pass"<<endl;
	ptr[0] = y + 1;
	cout<<"Val of x : "<<ptr[0]<<endl;
	kill(p1id, SIGUSR1);
}

int main()
{
	char myfifo[] = "/tmp/myfifo";
	char buffer[100];
	int ffd = open(myfifo, O_RDONLY);
	read(ffd, buffer, 100);
	close(ffd);

	p1id = atoi(buffer);
	cout<<"In P2 p1id : "<<p1id<<endl;

	sprintf(buffer, "%d", getpid());
	ffd = open(myfifo, O_WRONLY);
	write(ffd, buffer, strlen(buffer) + 1);
	close(ffd);

	cout<<"In p2 p2id : "<<getpid()<<endl;


	int key = 67674;
	int segment_id;
	segment_id = shmget(key, 2*sizeof(int), IPC_CREAT | 0666);
	if(segment_id == -1 )
	{
		cout<<"Error"<<endl;
		return -1;
	}

  	ptr = (int*) shmat(segment_id, 0, 0);

  	if(ptr == (void*)-1)
  	{
		cout<<"Error"<<endl;
		return -1;
	}

	signal(SIGUSR1, sigusr1handler);

	// kill(p1id, SIGUSR1);

	while(1)
	{
		sleep(1);
	}
	return 0;
}