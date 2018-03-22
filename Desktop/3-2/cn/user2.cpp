//named fifo
// this process will read first the message in the pipe and the send the message
/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/


	#include <iostream>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
	#include <string>
	#include <fcntl.h>
	#include <bits/stdc++.h>


	using namespace std;

	int main(){
		char *path="/tmp/myfifo";
		mkfifo(path,0666);
		int fd;
		char arr1[80],arr2[80];
		while(1){
			fd=open(path,O_RDONLY);
			read(fd,arr1,80);
			cout<<"USER1 : "<<arr1<<endl;
			close(fd);
			fd=open(path,O_WRONLY);
			fgets(arr2,80,stdin);
			write(fd,arr2,strlen(arr2)+1);
			close(fd);
		}
		return 0;
	}