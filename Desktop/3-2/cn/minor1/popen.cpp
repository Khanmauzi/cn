#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


using namespace std;

int main(){
	FILE * f=popen("./p6","w");
	int fd=fileno(f);						//convert file pointer to f
	int t;
	t=fork();
	if(t==0){
		dup2(fd,1);
		//write(1,"hello\n",7);
		char *path[]={"./p2",NULL};
		execvp(path[0],path);
	}
	t=fork();
	if(t==0){
		dup2(fd,1);
		char *path[]={"./p3",NULL};
		execvp(path[0],path);
	}
	t=fork();
	if(t==0){
		dup2(fd,1);
		char *path[]={"./p4",NULL};
		execvp(path[0],path);
	}
	while(1){
		
	}



}