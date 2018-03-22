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
int p2id;
int x;

void sigusr1handler(int sigid)
{
	cout<<sigid<<endl;
	cout<<"In p1"<<endl;
	x = ptr[0];
	ptr[1] = x + 1;
	cout<<"Val of y : "<<ptr[1]<<endl;
	kill(p2id, SIGUSR1);
}

int main()
{
	char myfifo[] = "/tmp/myfifo";
	mkfifo(myfifo, 0666);

	char buffer[100];
	sprintf(buffer, "%d", getpid());
	int ffd = open(myfifo, O_WRONLY);
	write(ffd, buffer, strlen(buffer) + 1);
	close(ffd);

	cout<<"In p1 p1id : "<<getpid()<<endl;

	ffd = open(myfifo, O_RDONLY);
	read(ffd, buffer, 100);
	close(ffd);

	p2id = atoi(buffer);
	cout<<"In P1 p2id : "<<p2id<<endl;


	int key = 67674;
	int segment_id;

	segment_id = shmget(key, 2*sizeof(int), 0666);
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

	kill(p2id, SIGUSR1);

	while(1)
	{
		sleep(1);
	}

	return 0;
}