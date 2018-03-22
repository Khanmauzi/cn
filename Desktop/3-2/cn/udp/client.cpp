//client code 

/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/

	#include <iostream>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <arpa/inet.h>


	using namespace std;

	int main(){
		int sfd,cfd;
		unsigned int clen,slen;
		struct sockaddr_in server,client;
		clen=sizeof(struct sockaddr_in);
		slen=sizeof(struct sockaddr_in);
		server.sin_family=AF_INET;
		server.sin_addr.s_addr=INADDR_ANY;
		server.sin_port=htons(33333);			//port number
		bzero(server.sin_zero,8);
		cfd=socket(AF_INET,SOCK_DGRAM,0);
		if(cfd<0){
			perror( "socket : ");
		}
		while(1){
			string s;
			char buffer[100];
			char buffer1[100];
			cout<<"enter the message to be send : ";
			getline(cin,s);
			strcpy(buffer,s.c_str());
			sendto(cfd,buffer,strlen(buffer)+1,0,(struct sockaddr*)&server,slen);
			recvfrom(cfd,buffer1,100,0,(struct sockaddr*)&server,&slen);
			cout<<"server  : "<<buffer1<<endl;
		}
	}