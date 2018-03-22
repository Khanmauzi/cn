#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<semaphore.h>
#include<iostream>
using namespace std;
int main()
{
	cout<<"child opened"<<endl;
	sem_t *S1 = sem_open("mysem1", 0);
	sem_t *S2 = sem_open("mysem2", 0);

	int rfd;
	// int wfd;
	// dup2(0, rfd);
	// dup2(1, wfd);

	int i = 4;
	char buffer[100];
	while(i)
	{
		sem_wait(S2);
		read(0, buffer, 6);
		cout<<"Process2 :"<<buffer<<endl;

		sem_post(S1);
		i--;
	}


	return 0;
}