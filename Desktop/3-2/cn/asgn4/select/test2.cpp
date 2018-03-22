//test2.cpp first write then recv

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
		string s;
		cin>>s;
		char buffer[100];
		strcpy(buffer,s.c_str());
		write(fd,buffer,strlen(buffer));
		char buff[100];
		read(fd,buff,100);
		cout<<"rec : "<<buff<<endl;
	}
	return 0;
}