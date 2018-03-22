//test1.cpp first receive then write

#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
int main(){
	char *path="/tmp/test1";
	mkfifo(path,0666);
	int fd=open(path,O_RDWR);
	while(1){
		char buff[100];
		int n=read(fd,buff,100);
		buff[n]='\0';
		cout<<"rec : "<<buff<<endl;
		string s;
		cin>>s;
		char buffer[100];
		strcpy(buffer,s.c_str());
		write(fd,buffer,strlen(buffer));
	}
	return 0;
}