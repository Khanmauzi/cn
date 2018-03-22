//simple socket programme with port 10000


#include <iostream>
#include <unistd.h>				//for close system call
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>				//for perror
#include <sys/types.h>			//socket
#include <sys/socket.h>			//socket
#include <netinet/in.h>			//address struct 
#include <arpa/inet.h>			//for inet_ntoa system call


using namespace std;


int main(){
	int sfd;			//file descriptor for socket
	int cfd;			//file descriptor for client

	struct sockaddr_in server,client;
	unsigned int len,clen;
	char *msg="hello client \n";
	server.sin_family =AF_INET;							//DOMAIN TYPE 
	server.sin_port=htons(10000);						//PORT
	server.sin_addr.s_addr=INADDR_ANY;					//IP FROM INTERFACE
	bzero(&server.sin_zero,8);
	len=sizeof(struct sockaddr_in);
	if((sfd=socket(AF_INET,SOCK_STREAM,0))==-1){					//end point of communicatioin
		perror("socket : ");
		exit(-1);
	}

	if(bind(sfd,(struct sockaddr*)&server,len)==-1){			//binding ip and port to the socket
		perror("binnd : ");
		exit(-1);
	}

	if(listen(sfd,5)==-1){									//waiting for the client
		perror("listen");
		exit(-1);
	}
	while(1){

		if((cfd=accept(sfd,(struct sockaddr*)&client,&clen))==-1){
			perror("Accept");
			exit(-1);
		}
		cout<<"connection request from : "<<inet_ntoa(client.sin_addr)<<endl;
		send(cfd,msg,strlen(msg)+1,0);
		close(cfd);
	}

	return 0;

}