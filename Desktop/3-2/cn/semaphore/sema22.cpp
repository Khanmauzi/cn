#include <bits/stdc++.h>
#include <iostream>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
using namespace std;
int main(){
	sem_t *s1=sem_open("mysem1",0);
	sem_t *s2=sem_open("mysem2",0);

	while(1){
		sem_wait(s2);
		cout<<"this is child process"<<endl;
		sem_post(s1);
	}
}