#include <ace/Reactor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Stream.h>
#include <ace/Synch.h>
#include <ace/Log_Msg.h>
#include <ace/streams.h>
#include <ace/INET_Addr.h>
#include <bits/stdc++.h>
#include <errno.h>
#include "ace/LSOCK_Stream.h"
#include "ace/LSOCK_Connector.h"
#include "ace/LSOCK.h"
#include "ace/OS.h"
#include <vector>
#include <ctime>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

vector<bool>flag;

bool l=true;
/*void *fn(void *arg){
	cout<<" press X to stop receiving client "<<endl;
	char ch;
	cin>>ch;
	if(ch=='x'||ch=='X'){
		l=false;
	}
	return NULL;
}*/
int cnt=0;
int m=50;
char test[100];
string s="this is test";
int pid1;						//process id of server.
int pid2;						//process id of client.
int main(){
	strcpy(test,s.c_str());
	srand(time(NULL));	
	ACE_INET_Addr client;

	ACE_SOCK_Acceptor client_acceptor;

	ACE_SOCK_Stream cli_stream;

	//********fifo*************

	/*char myfifo[] = "/tmp/myfifo";
	int pfd = open(myfifo, O_RDONLY);
	char buffer[100];
	read(pfd, buffer, 100);
	pid1=atoi(buffer);
	close(pfd);
	pfd=open(myfifo,O_WRONLY);
	char buffer1[100];
	pid2=getpid();
	sprintf(buffer1, "%d", getpid());
	write(pfd, buffer1, strlen(buffer1) + 1);
	close(pfd);
	cout<<"pid of server "<<pid1<<endl;
	cout<<"pid of giver "<<pid2<<endl;*/



	cout<<"**********NUMBER DISTRIBUTOR SERVER ******************"<<endl;

	//cout<<"Stuff"<<endl;
	ACE_LSOCK_Stream stream;
	ACE_LSOCK_Connector Connector;
	Connector.connect(stream, "/tmp/foo");
	ACE_HANDLE a;

	//pthread_t t1;
	//pthread_create(&t1,NULL,fn,NULL);
	//int n;
	//stream.recv_handle(n);
	//cout<<n<<endl;
	vector <ACE_HANDLE>v;
	int cnt=3;
	while(cnt>0){
	stream.recv_handle(a);
	cout<<"handle received\n";
	send(a,test,100,0);
	perror("send");
	v.push_back(a);
	flag.push_back(true);
	cnt--;
	/*for(int i=0;i<v.size();i++){
		send(v[i],test,100,0);
	}*/
  }



	//pthread_join(t1,NULL);
	cout<<"out of the loop"<<endl;
	int n=0;

	/*while(1){
		int k=rand()%m;
		char buff[10];
		char buff2[10];
		string st=to_string(k);
		cout<<st<<endl;
		strcpy(buff,st.c_str());
		for(int i=0;i<v.size();i++){
			cout<<"i : "<<i<<endl;
			if(flag[i]==true){
				send(v[i],buff,10,0);
				perror("sending ");
				recv(v[i],buff2,10,0);
				perror("received res");
				if(buff2[0]=='y'){
					n++;
					flag[i]=false;
				}
			}
		}
		if(n==v.size()){
			cout<<"game over "<<endl;
			break;
		}

	}*/
}