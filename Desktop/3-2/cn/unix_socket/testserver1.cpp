//unix socket simple example
/*
	NAME :MOJAMMIL
	ROLL :157238
	BATCH :2015-19 CSE
	NIT WARANGAL
*/

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>

using namespace std;

int main(){

	int sfd=socket(AF_UNIX,SOCK_STREAM,0);
	struct sockaddr_un server,client;
	server.sun_family=AF_UNIX;
	strcpy(server.sun_path,"./s1");
	bind(sfd,(struct sockaddr*)&server,sizeof(server));
	listen(sfd,10);
	while(1){
		int l=sizeof(client);
		int nsfd=accept(sfd,(struct sockaddr*)&client,(socklen_t *)&l);
		//cout<<"connected "<<endl;
		char r[100];
		char w[100]="this is server";
		read(nsfd,r,100);
		cout<<"client : "<<r<<endl;
		write(nsfd,w,100);
		close(nsfd);
	}
}