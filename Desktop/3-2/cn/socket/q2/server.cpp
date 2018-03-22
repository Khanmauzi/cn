//single port multiservice multiple process threadede server server
// run : server1 port_number
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
#include <pthread.h>


using namespace std;
string s="service ";
void *service1(void *arg){
	s="";
	s="providing threaded service1";
}

void *service2(void *arg){
	s="";
	s="providing threaded service2";
}
int main(int arg,char *argv[]){
	int sfd;
	int cfd;
	unsigned int len;
	unsigned int clen;
	struct sockaddr_in server,client;
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=INADDR_ANY;
	bzero(server.sin_zero,8);
	len=sizeof(struct sockaddr_in);
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1){
		perror("socket");
		exit(-1);
	}
	if(bind(sfd,(struct sockaddr*)&server,len)==-1){
		perror("bind ");
		exit(-1);
	}
	if(listen(sfd,5)==-1){
		perror("listen");
		exit(-1);
	}
	cout<<inet_ntoa(server.sin_addr)<<endl;
	while(1){
		cfd=accept(sfd,(struct sockaddr*)&client,&clen);
		if(cfd==-1){
			perror("client connection fail ");
			exit(-1);
		}
		else{
			cout<<"connection established from "<<inet_ntoa(client.sin_addr)<<ntohs(client.sin_port)<<endl;
			int t=fork();

			if(t==0){
				close(sfd);					//child process ,close socket descriptor in this 
				while(cfd){						
					
				char buffer[100];
				recv(cfd,buffer,100,0);
				cout<<"message from "<<inet_ntoa(client.sin_addr)<<" : "<<buffer<<endl;
				int n=atoi(buffer);
				
				pthread_t t1,t2;
				if(n==1){
					pthread_create(&t1,NULL,service1,NULL);
					pthread_join(t1,NULL);
				}
				else if(n==2){
					pthread_create(&t2,NULL,service2,NULL);
				}
				//char *msg="message is recieved \n";
				char buffer1[100];
				strcpy(buffer1,s.c_str());
				send(cfd,buffer1,strlen(buffer1)+1,0);
				}
				break;

			}
			else{
				close(cfd);
			}
		}
	}
	close(sfd);	

}