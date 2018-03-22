//client side code for select system call

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

using namespace std;
int main(){
	char *path1="/tmp/select1";
	char *path2="/tmp/select2";
	char *path3="/tmp/writepath1";
	char *path4="/tmp/writepath2";
	int n;
	mkfifo(path3,0666);
	mkfifo(path4,0666);
	
	cout<<"enter 1 to communicate through channel1 and 2 for channel2 : ";
	cin>>n;
	if(n==1){
		mkfifo(path1,0666);
		int fd1=open(path1,O_RDWR);
		cout<<"enter 1 for function1 2 for funcion2 and 3 for function 3 : "<<endl;
		while(1){
		string s;
		
		char buffer[100];
		cin>>s;
		strcpy(buffer,s.c_str());
		//cout<<"bufferr : "<<buffer<<endl;
		write(fd1,buffer,strlen(buffer)+1);
		//cout<<"hi "<<endl;
		char buff[100];
		int wfd1=open(path3,O_RDONLY);
		read(wfd1,buff,100);
		cout<<"return : "<<buff<<endl;
		close(wfd1);
		}
		close(fd1);
	}
	 else if(n==2){
		mkfifo(path2,0666);
		int fd2=open(path2,O_RDWR);
		
		cout<<"enter 1 for to execute process 1 and 2 to execute process 2 : ";
		while(1){
		string s;
		char buffer[100];
		cin>>s;
		strcpy(buffer,s.c_str());
		write(fd2,buffer,strlen(buffer)+1);
		char buffer1[100];
		int wfd2=open(path4,O_RDONLY);
		read(wfd2,buffer1,100);
		cout<<buffer1<<endl;
		close(wfd2);
		}
	}
}