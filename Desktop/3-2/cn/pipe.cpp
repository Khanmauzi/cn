// named pipe

/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/



	#include <iostream>
	#include <stdio.h>
	#include <string>
	#include <sys/types.h>
	#include <bits/stdc++.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	using namespace std;

	int main(){
		char *path="/tmp/myfifo";
		int fd;
		mkfifo(path,0666);
		int c=fork();
		char arr1[80],arr2[20];
		if(c>0){ 
			cout<<"this is parent process ,write message to child "<<endl;
			fd=open(path,O_WRONLY);
			fgets(arr1,80,stdin);
			write(fd,arr1,strlen(arr1)+1);
			close(fd);
		}
		else {
	
			fd=open(path,O_RDONLY);
			read(fd,arr2,80);
			cout<<"this is child process "<<endl;
			cout<<arr2<<endl;
			close(fd);
		}
		return 0;
	}