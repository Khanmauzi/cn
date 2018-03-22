// select system call that will read input given from other process

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>


using namespace std;
 int main(){
 	char *path="/tmp/s1";
 	fd_set rfds;
 	FD_ZERO(&rfds);
 	mkfifo(path,0666);
 	int fd=open(path,O_RDWR);
 	FD_SET(fd,&rfds);
 	struct timeval tv;
 	tv.tv_sec=10;
 	tv.tv_usec=0;
 	int retval;
 	//cout<<"Fd "<<fd<<endl;
 	while(1){
 		//cout<<"hi "<<endl;
 	retval=select(fd+1,&rfds,NULL,NULL,NULL);
 	if(retval==-1){
 		cout<<"error";
 	}
 	else{
 		if(FD_ISSET(fd,&rfds)){
 			//cout<<"it is set "<<endl;
 			char buffer[100];
 			read(fd,buffer,100);
 			cout<<buffer<<endl;
 		}
 	}
 	}
 	return 0;

 }