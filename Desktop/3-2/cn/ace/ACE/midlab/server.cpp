// Mojammil

#include "ace/SOCK_Acceptor.h"
#include "ace/SOCK_Stream.h"
#include "ace/LSOCK_Stream.h"
#include "ace/LSOCK_Acceptor.h"
#include "ace/LSOCK.h"
#include "ace/OS.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>

#include <sys/types.h>
#include <fcntl.h>
#include <csignal>
#include <stdlib.h>
using namespace std;
int m=9;
int cnt=0;
bool l=true;
int pid1;			//pid of server
int pid2;			//pid of giver

int main(){
	//*******fifo*//
	/*char myfifo[] = "/tmp/myfifo";
	mkfifo(myfifo, 0666);
	char buffer[100];
	sprintf(buffer, "%d", getpid());
	int pfd = open(myfifo, O_WRONLY);
	write(pfd, buffer, strlen(buffer) + 1);
	pid1=getpid();
	close(pfd);

	 pfd = open(myfifo, O_RDONLY);
	char buffer1[100];
	read(pfd, buffer1, 100);
	pid2=atoi(buffer1);
	close(pfd);
	cout<<"pid of server "<<pid1<<endl;
	cout<<"pid of giver "<<pid2<<endl;*/
	srand(time(NULL));						// to generate random number
	ACE_OS::unlink("/tmp/foo");	
	cout<<"**************MAIN SERVER *********************"<<endl;
	ACE_LSOCK_Stream stream;
	ACE_LSOCK_Acceptor acceptor;
	acceptor.open((ACE_UNIX_Addr)"/tmp/foo");
	acceptor.accept(stream);

	
	
	ACE_SOCK_Stream cli_stream;
	//ACE_INET_Addr client;
	ACE_INET_Addr s("127.0.0.1:5000"),client;
	ACE_SOCK_Acceptor a(s);

	/*time_t endwait;
	time_t start = time(NULL);
	time_t second = 120; 			// for how many second you want this loop to be executed
	cout<<"enter time for while loop "<<endl;
	cin>>second;
	endwait = start + second; */

	//cout<<" server start time is "<<start<<endl;
	//int clientnum;
	//cout<<"enter the number of clinet to be accepted "<<endl;
	//cin>>clientnum;
	//stream.send_handle(clientnum);
	int n=3;
	//vector<ACE_HANDLE>v;			//to store the handle
	while(1) {
		  a.accept(cli_stream,&client);
	  	  cout<<"client address:"<<client.get_host_name()<<":"<<client.get_port_number()<<endl;
	  	  cnt++;
	  	  cout<<cnt<<" : "<<n<<endl;
	      ACE_HANDLE fd = cli_stream.get_handle();		//getting handle
	      char a[2];
	      int x=rand()%m;
	      //cout<<x<<endl;
	      string s=to_string(x+1);
	      //cout<<s<<endl;
	      strcpy(a,s.c_str());
	      send(fd,a,2,0);
	      perror("sending ");
	      stream.send_handle(fd);
	     // v.push_back(fd);
	   }
	   //sleep(50);
	 cout<<"out of the loop ";
	 int k=0;
	 while(1){
	 	cout<<"hihihihi"<<endl;
	 }
}

