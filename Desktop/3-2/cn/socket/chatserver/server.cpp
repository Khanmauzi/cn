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

#define IP "172.30.102.129"

using namespace std;
string s="service ";
int sfd;
int cfd;
unsigned int len;
unsigned int clen;
struct sockaddr_in server,client;
void *read(void *arg){
	int rfd=*((int *)arg);
	//pthread_t t;
	//pthread_create(&t,NULL,rfd,)
	while(1){
		char buffer[100];
		recv(rfd,buffer,100,0);
		getpeername(rfd,(struct sockaddr*)&client,&clen);
		cout<<"msg from "<<inet_ntoa(client.sin_addr)<<"  : "<<ntohs(client.sin_port)<<"  : "<<buffer<<endl;
		string s;
		getline(cin,s);
		strcpy(buffer,s.c_str());
		send(rfd,buffer,strlen(buffer)+1,0);
		if(!sfd){
			break;
		}
	}
	return NULL;
}

/*void *write(void *arg){
	int wfd=*((int *)arg);
	while(1){
		char buffer[100];
		string s;
		getline(cin,s);
		strcpy(buffer,s.c_str());
		send(wfd,buffer,strlen(buffer)+1,0);
		if(!wfd)
			break;
	}
	return NULL;
}*/
int main(int arg,char *argv[]){
	//int sfd;
	//int cfd;
	/*unsigned int len;
	unsigned int clen;
	struct sockaddr_in server,client;*/
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=INADDR_ANY;//inet_addr(IP);//INADDR_ANY;
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
	getsockname(sfd,(struct sockaddr*)&server,&len);					//to get server ip address and port numbr
	cout<<" Server address "<<inet_ntoa(server.sin_addr)<<" : "<<ntohs(server.sin_port)<<endl;
	if(listen(sfd,5)==-1){
		perror("listen");
		exit(-1);
	}
	//cout<<inet_ntoa(server.sin_addr)<<endl;
	while(1){
		cfd=accept(sfd,(struct sockaddr*)&client,&clen);
		if(cfd==-1){
			perror("client connection fail ");
			exit(-1);
		}
		else{
			//cout<<"connection established from "<<inet_ntoa(client.sin_addr)<<ntohs(client.sin_port)<<endl;
			getpeername(cfd,(struct sockaddr*)&client,&clen);				//to get the client details
			cout<<"connection established from "<<inet_ntoa(client.sin_addr)<<" : "<<ntohs(client.sin_port)<<endl;
			int t=fork();

			if(t==0){
				close(sfd);					//child process ,close socket descriptor in this 						
				pthread_t t1,t2;	
				pthread_create(&t1,NULL,read,&cfd);
				//pthread_create(&t2,NULL,write,&cfd);
				pthread_join(t1,NULL);
				//pthread_join(t2,NULL);
				close(cfd);
				break;
				}

			else{
				close(cfd);
			}
		}
	}
	close(sfd);	

}