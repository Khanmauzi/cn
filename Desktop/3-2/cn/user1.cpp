//named fifo
// this process will write message to pipe and the read the message sent by other process
/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/


	#include <iostream>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
	#include <fcntl.h>
	#include <string>
	#include <bits/stdc++.h>

	using namespace std;

	int main(){
		char *path="/tmp/myfifo";
		mkfifo(path,0666);
		int fd;
		char arr1[80],arr2[80];
		while(1){
			fd=open(path,O_WRONLY);
			fgets(arr1,80,stdin);
			write(fd,arr1,strlen(arr1)+1);
			close(fd);
			fd=open(path,O_RDONLY);
			read(fd,arr2,80);
			cout<<"USER2 : "<<arr2<<endl;
			close(fd);
		}
		return 0;
	}