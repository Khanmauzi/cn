#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<semaphore.h>
#include<iostream>
#include <sys/types.h>
using namespace std;
int main()
{
	// int fd = open("test.txt", O_WRONLY);
	int fd2 = open("test.txt", O_RDONLY);
	
	sem_t *S1 = sem_open("mysem1", O_CREAT, 0644, 1);
	sem_t *S2 = sem_open("mysem2", O_CREAT, 0644, 0);

	pid_t pid = fork();

	if(pid == 0)
	{
		// dup2(fd, 1);
		dup2(fd2, 0);
		cout<<"child123"<<endl;
		char *path[]={"./sema12",NULL};
		execvp(path[0],path);
	}
	else
	{

		cout<<"parent"<<endl;

		char buffer[100];
		int i = 4;
		while(i)
		{
			cout<<"#####"<<endl;
			sem_wait(S1);
			cout<<"sdka"<<endl;
			read(fd2, buffer, 6);
			cout<<"P1 :"<<buffer<<endl;
			sem_post(S2);
			// sleep(1000);
			
			i--;
		}
	
	}

	return 0;
}