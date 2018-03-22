//client to interaact with the server
//take port number and ip from the address
//.client  portnumber

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>

using namespace std;

int main(int arg,char *argv[]){
	int cfd,len;
	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(atoi(argv[1]));
	client.sin_addr.s_addr=INADDR_ANY;
	len=sizeof(struct sockaddr_in);
	cfd=socket(AF_INET,SOCK_STREAM,0);
	if(cfd==-1){
		perror("socket : ");
		exit(-1);

	}
	if(connect(cfd,(struct sockaddr*)&client,len)==-1){
		perror("connect");
		exit(-1);
	}
	while(1){
		string s;
		cout<<"enter 1 for service1, 2 for service 2 : ";
		getline(cin,s);
		char buffer[1024];
		strcpy(buffer,s.c_str());
		send(cfd,buffer,strlen(buffer)+1,0);
		char buf[1024];
		recv(cfd,buf,1024,0);
		cout<<"from server : "<<buf<<endl;
	}

}