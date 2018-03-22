//server side program file for multi-service server

#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>


using namespace std;



int fd1;
int fd2;
int wfd;
int wfd2;



int max(int a,int b){
	if(a>b)
		return a;
	else 
		return b;
}


string function1(void){
	return "this is function 1 ";
}

string function2(void){
	return "this is function 2 ";
}

string function3(void){
	return "this is function 3 ";

}

void *f1(void *arg){
	int n=*((int *)arg);
	//cout<<"n : "<<n<<endl;
		if(n==1){
				char *path[]={"./process1",NULL};
				execvp(path[0],path);
			}
			if(n==2){
				char *path[]={"./process2",NULL};
				execvp(path[0],path);
			}
			else{
				write(wfd2,"invalid input \n",16);
			}
			
}
int main(){
	char *path1="/tmp/select1";
	char *path2="/tmp/select2";
	char *path3="/tmp/writepath1";
	char *path4="/tmp/writepath2";
	
	mkfifo(path1,0666);
	mkfifo(path2,0666);
	
	fd1=open(path1,O_RDWR);
    fd2=open(path2,O_RDWR);
 
  

	fd_set rfds;
	fd_set wrfds;
	struct timeval tv;
	
	int mxfd=max(fd1,fd2)+1;
	while(1){
		tv.tv_sec=5;
		tv.tv_usec=0;

		FD_ZERO(&rfds);
	//	FD_ZERO(&wrfds);
		FD_SET(fd1,&rfds);
	//	FD_SET(fd1,&wrfds);
		FD_SET(fd2,&rfds);
	//	FD_SET(fd2,&wrfds);
		int ret=select(mxfd,&rfds,NULL,NULL,&tv);
		if(ret==-1){
			cout<<"error "<<endl;
		}
		else if(ret){
			if(FD_ISSET(fd1,&rfds)){
				cout<<"fd1 set "<<path1<<endl;
				char buffer[100];
				read(fd1,buffer,100);
				//cout<<buffer<<endl;
				string s="";
				int n=atoi(buffer);
				//cout<<n<<endl;
				if(n==1){
					s=function1();
				}
				else if(n==2){
					s=function2();
				}
				else if(n==3){
					s=function3();
				}
				char buffer2[100];
				strcpy(buffer2,s.c_str());
				mkfifo(path3,0666);
				wfd=open(path3,O_WRONLY);
				//cout<<s<<endl;
				write(wfd,buffer2,strlen(buffer2)+1);
				close(wfd);

			}
			if(FD_ISSET(fd2,&rfds)){
				cout<<"fd2 is set "<<path2<<endl;
				char buffer[100];
				read(fd2,buffer,100);
				int n=atoi(buffer);
				//cout<<n<<endl;
				mkfifo(path4,0666);
				wfd2=open(path4,O_WRONLY);
				dup2(wfd2,0);
			pthread_t t1;
			pthread_create(&t1,NULL,f1,&n);
			pthread_join(t1,NULL);

			}
		}
		else cout<<"no data within given time : "<<endl;
	}
	return 0;
}