//Normal fifo file which will write something to the select2fiel

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  


using namespace std;
 int main(){
 	char *path="/tmp/s1";
 	mkfifo(path,0666);
 	int fd=open(path,O_RDWR);
 	while(1){
 		char buffer[100];
 		string s;

 		getline(cin,s);
 		strcpy(buffer,s.c_str());
 		write(fd,buffer,strlen(buffer)+1);
 	}
 	return 0;
 }