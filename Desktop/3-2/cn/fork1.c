// fork call
/*
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/




//#include <iostream.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){
	pid_t c;
	

	printf("this is main process %d\n",getpid());
	c=fork();
	if(c>0){
		printf("this is parent process \n");
		printf("child process id is : %d \n",c);
		wait();
		//printf("parent process id is : %d \n",getpid());
	}
	else{
		printf("this is child process , its id is: %d\n",getpid());
		printf("parents id is : %d\n",getppid());
		printf("this is fork process, going to call postfix calculation process \n");
		char *arg[]={"./post",NULL};
		execvp(arg[0],arg);
		
	}

}