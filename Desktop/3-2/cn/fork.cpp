// fork call
/*
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/


#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <bits/stdc++.h>

using namespace std;
int main(){
	pid_t c;
	cout<<"this is main programm "<<endl;
	c=fork();
	if(c>0){
		cout<<"it is parent process ,child id is : "<<c<<" and parent id is "<<getpid()<<endl;
	}
	else if(c==0){
		cout<<"this is child process and its id is : "<<getpid()<<" and its parent id is  : "<<getppid()<<endl;
	}
	else {
		cout<<"fails to create child "<<endl;
	}
}