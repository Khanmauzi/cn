//multiport ,multiservice ,threaded server


//single port multiservice multiple process threadede server server
// run : server1 port_number1,port_number2
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
#include <sys/select.h>


using namespace std;
string s="service ";
void *service1(void *arg){
	s="";
	s="providing threaded service1";
	return NULL;
}

void *service2(void *arg){
	s="";
	s="providing threadedr service2";
	return NULL;
}

int max(int a,int b){
	if(a>b)
		return a;
	else
		return b;
}
int main(int arg,char *argv[]){
	int sfd1,sfd2;
	int cfd;
	unsigned int len;
	unsigned int clen;
	struct sockaddr_in server1,server2,client;
	server1.sin_family=AF_INET;
	server1.sin_port=htons(atoi(argv[1]));
	server1.sin_addr.s_addr=INADDR_ANY;
	bzero(server1.sin_zero,8);
	len=sizeof(struct sockaddr_in);
	sfd1=socket(AF_INET,SOCK_STREAM,0);
	if(sfd1==-1){
		perror("socket");
		exit(-1);
	}
	if(bind(sfd1,(struct sockaddr*)&server1,len)==-1){
		perror("bind ");
		exit(-1);
	}
	if(listen(sfd1,5)==-1){
		perror("listen");
		exit(-1);
	}

		// for second port.
	server2.sin_family=AF_INET;
	server2.sin_port=htons(atoi(argv[2]));
	server2.sin_addr.s_addr=INADDR_ANY;
	bzero(server2.sin_zero,8);

		sfd2=socket(AF_INET,SOCK_STREAM,0);
	if(sfd2==-1){
		perror("socket");
		exit(-1);
	}
	if(bind(sfd2,(struct sockaddr*)&server2,len)==-1){
		perror("bind ");
		exit(-1);
	}
	if(listen(sfd2,5)==-1){
		perror("listen");
		exit(-1);
	}
	
	int mxfd=max(sfd1,sfd2)+1;
	while(1){
		struct timeval tv;
		tv.tv_sec=5;
		tv.tv_usec=0;
		fd_set rfds;

			FD_ZERO(&rfds);
			FD_SET(sfd1,&rfds);
			FD_SET(sfd2,&rfds);
			int ret=select(mxfd,&rfds,NULL,NULL,&tv);
			if(ret==-1){
				perror("select : ");
			}
			else{

				if(FD_ISSET(sfd1,&rfds)){
					cfd=accept(sfd1,(struct sockaddr*)&client,&clen);
					if(cfd==-1){
						perror("client connection fail ");
						exit(-1);
					}
					else{
						cout<<"connection established from "<<inet_ntoa(client.sin_addr)<<" : "<<ntohs(client.sin_port)<<endl;
						int t=fork();

						if(t==0){
							close(sfd1);					//child process ,close socket descriptor in this 
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
								pthread_join(t2,NULL);
							}
							//char *msg="message is recieved \n";
							char buffer1[100];
							strcpy(buffer1,s.c_str());
							cout<<buffer1<<endl;
							send(cfd,buffer1,strlen(buffer1)+1,0);
							}
							break;

						}
						else{
							close(cfd);
						}
					}
				}
					if(FD_ISSET(sfd2,&rfds)){
					cfd=accept(sfd2,(struct sockaddr*)&client,&clen);
					if(cfd==-1){
						perror("client connection fail ");
						exit(-1);
					}
					else{
						cout<<"connection established from "<<inet_ntoa(client.sin_addr)<<" : "<<ntohs(client.sin_port)<<endl;
						int t=fork();

						if(t==0){
							close(sfd2);					//child process ,close socket descriptor in this 
							while(cfd){						
								
							char buffer[100];
							recv(cfd,buffer,100,0);
							cout<<"message from "<<inet_ntoa(client.sin_addr)<<" : "<<buffer<<endl;
							int n=atoi(buffer);
							
							pthread_t t1,t2;
							if(n==1){
								pthread_create(&t1,NULL,service1,NULL);
								//pthread_join(t1,NULL);
							}
							else if(n==2){
								pthread_create(&t2,NULL,service2,NULL);
								//pthread_join(t2,NULL);
							}
							//char *msg="message is recieved \n";
							char buffer1[100];
							strcpy(buffer1,s.c_str());
							cout<<buffer1<<endl;
							send(cfd,buffer1,strlen(buffer1)+1,0);
							}
							break;

						}
						else{
							close(cfd);
						}
					}
				}
				/*else{
					cout<<"no request in given time : "<<endl;
				}*/
			}


	}
	close(sfd1);
	close(sfd2);	

}