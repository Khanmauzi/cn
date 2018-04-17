//coupon server
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
#include <sys/un.h>
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>

#define IP "172.30.102.129"
#define ADDRESS     "mysocket"

using namespace std;
string s="service ";
int sfd;
int cfd;
unsigned int len;
unsigned int clen;
struct sockaddr_in server,client;
int cpid,gpid;


int send_fd(int socket, int fd_to_send)
 {
 	getpeername(fd_to_send,(struct sockaddr*)&client,&clen);
 	cout<<"sending fd for child with ip and port is "<<inet_ntoa(client.sin_addr)<<":"<<ntohs(client.sin_port)<<endl;
  struct msghdr socket_message;
  struct iovec io_vector[1];
  struct cmsghdr *control_message = NULL;
  char message_buffer[1];
  /* storage space needed for an ancillary element with a paylod of length is CMSG_SPACE(sizeof(length)) */
  char ancillary_element_buffer[CMSG_SPACE(sizeof(int))];
  int available_ancillary_element_buffer_space;

  /* at least one vector of one byte must be sent */
  message_buffer[0] = 'F';
  io_vector[0].iov_base = message_buffer;
  io_vector[0].iov_len = 1;

  /* initialize socket message */
  memset(&socket_message, 0, sizeof(struct msghdr));
  socket_message.msg_iov = io_vector;
  socket_message.msg_iovlen = 1;

  /* provide space for the ancillary data */
  available_ancillary_element_buffer_space = CMSG_SPACE(sizeof(int));
  memset(ancillary_element_buffer, 0, available_ancillary_element_buffer_space);
  socket_message.msg_control = ancillary_element_buffer;
  socket_message.msg_controllen = available_ancillary_element_buffer_space;

  /* initialize a single ancillary data element for fd passing */
  control_message = CMSG_FIRSTHDR(&socket_message);
  control_message->cmsg_level = SOL_SOCKET;
  control_message->cmsg_type = SCM_RIGHTS;
  control_message->cmsg_len = CMSG_LEN(sizeof(int));
  *((int *) CMSG_DATA(control_message)) = fd_to_send;

  return sendmsg(socket, &socket_message, 0);
 }




int main(int arg,char *argv[]){
	//int sfd;
	//int cfd;
	/*unsigned int len;
	unsigned int clen;
	struct sockaddr_in server,client;*/
	//--------------------------------------------------------------------------unix socket

	int usfd;
	struct sockaddr_un userv_addr;
  	unsigned int userv_len,ucli_len;

  	usfd = socket(AF_UNIX, SOCK_STREAM, 0);

  	if(usfd==-1)
  	perror("\nsocket  ");

  	bzero(&userv_addr,sizeof(userv_addr));
  	userv_addr.sun_family = AF_UNIX;
   	strcpy(userv_addr.sun_path,ADDRESS);

	userv_len = sizeof(userv_addr);

	if(connect(usfd,(struct sockaddr *)&userv_addr,userv_len)==-1)
	perror("\n connect ");

	else printf("\n unix socket connect succesful \n");


	//--------------------------------------------------------------------------------unix socket





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
	cout<<" socket sfd "<<endl;
	
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
				send_fd(usfd,cfd);
				while(1);
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