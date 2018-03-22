#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>


using namespace std;

int main(){
	FILE * f=popen("./p6","w");
	int fd=fileno(f);						//convert file pointer to f
	struct pollfd fds[3];
	FILE * f2=popen("./p2","r");
	fds[0].fd=fileno(f2);
	FILE * f3=popen("./p3","r");
	fds[1].fd=fileno(f3);
	FILE * f4=popen("./p4","r");
	fds[2].fd=fileno(f4);
	for(int i=0;i<3;i++){
		fds[i].events=POLLIN;
	}
	while(1){
		int ret=poll(fds,3,1000);
		cout<<"hi "<<endl;
		if(ret>0){
			cout<<"data is there "<<endl;
			for(int i=0;i<3;i++){
				cout<<"checking polling "<<endl;
				if(fds[i].revents & POLLIN){			//DATA IS THERE
					dup2(fds[i].fd,1);
					cout<<"dup2"<<endl;
				}
			}
		}
	}



}