//unix socket simple example
/*
	NAME :MOJAMMIL
	ROLL :157238
	BATCH :2015-19 CSE
	NIT WARANGAL
*/

#include <iostream>
	#include <string.h>
	#include <unistd.h>
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <sys/un.h>

	using namespace std;

	int main(){
		int cfd=socket(AF_UNIX,SOCK_STREAM,0);
		struct sockaddr_un server;
		server.sun_family=AF_UNIX;
		strcpy(server.sun_path,"./s1");
		connect(cfd,(struct sockaddr*)&server,sizeof(server));
		char r[100];
		char w[100]="this is client";
		write(cfd,w,100);
		read(cfd,r,100);
		cout<<"server : "<<r<<endl;
		return 0;

	}