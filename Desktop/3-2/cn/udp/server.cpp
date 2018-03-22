/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/

	#include <iostream>
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <netinet/in.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <arpa/inet.h>
	//#include <pthread.h>
	using namespace std;


	int main(){
		struct sockaddr_in server,client;
		unsigned int slen,clen;
		slen=sizeof(sockaddr_in);
		clen=sizeof(sockaddr_in);
		int sfd,cfd;
		sfd=socket(AF_INET,SOCK_DGRAM,0);
		server.sin_port=htons(33333);					//port is 33333
		server.sin_addr.s_addr=INADDR_ANY;
		server.sin_family=AF_INET;
		bzero(server.sin_zero,8);
		if(bind(sfd,(struct sockaddr*)&server,slen)==-1){
			perror(" bind : ");
		}
		else{			//successful bounding
			char buffer[100];
			char buff[100];
			string s="message recieved ";
			strcpy(buff,s.c_str());

			while(1){
				recvfrom(sfd,buffer,100,0,(struct sockaddr*)&client,&clen);
				cout<<"recieving from  :"<<inet_ntoa(client.sin_addr)<<" : "<<ntohs(client.sin_port)<<endl;
				cout<<buffer<<endl;
				sendto(sfd,buff,strlen(buff)+1,0,(struct sockaddr*)&client,clen);

			}

		}
	}