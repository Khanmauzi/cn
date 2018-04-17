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
#include <pthread.h>

#define IP "172.30.102.129"

using namespace std;
void *read(void *arg){
	int rfd=*((int *)arg);
	while(rfd){
		char buffer[100];
		recv(rfd,buffer,100,0);
		cout<<"mesg : "<<buffer<<endl;
	}
	return NULL;
}
void *write(void *arg){
	int wfd=*((int *)arg);
	while(wfd){
		char buffer[100];
		string s;
		getline(cin,s);
		strcpy(buffer,s.c_str());
		send(wfd,buffer,strlen(buffer)+1,0);
	}
}
int main(int arg,char *argv[]){
	int cfd,len;
	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_port=htons(atoi(argv[1]));
	client.sin_addr.s_addr=INADDR_ANY;//inet_addr(IP);//INADDR_ANY;
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
	cout<<"connected to the network .. "<<endl;

	pthread_t t1,t2;
	pthread_create(&t1,NULL,read,&cfd);
	pthread_create(&t2,NULL,write,&cfd);
	pthread_join(t1,NULL); 
	pthread_join(t2,NULL);
	close(cfd);
	return 0;

}