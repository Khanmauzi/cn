#include <bits/stdc++.h>
#include <iostream>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main(){
	sem_t *s1=sem_open("mysem1",O_CREAT,0644,1);
	sem_t *s2=sem_open("mysem2",O_CREAT,0644.0);
	int t=fork();
	if(t==0){
		char *path[]={"./sema22",NULL};
		execvp(path[0],path);
	}
	else{
		sem_wait(s1);
		cout<<"this is parent process "<<endl;
		sem_post(s2);
	}
}