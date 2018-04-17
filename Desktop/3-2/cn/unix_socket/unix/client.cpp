#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <stdio.h>
#define address "unix"

using namespace std;

int main(){
	struct sockaddr_un server;
	
	int cfd=socket(AF_UNIX,SOCK_STREAM,0);
	server.sun_family=AF_UNIX;
	strcpy(server.sun_path,address);
	unsigned int l=sizeof(server);
	if((connect(cfd,(struct sockaddr*)&server,l))==-1){
		perror("connect");
		exit(-1);
	}
	string s="hi this is client";
	char buffer[100];

	while(cfd){
		cin>>s;
		strcpy(buffer,s.c_str());
		write(cfd,buffer,strlen(buffer)+1);

	}
	return 0;
}