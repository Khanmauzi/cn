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
using namespace std;


int main(){
	ACE_INET_Addr client;

	ACE_SOCK_Acceptor client_acceptor;

	ACE_SOCK_Stream cli_stream;

	cout<<"Stuff"<<endl;

	//cout<<"Stuff"<<endl;
	ACE_LSOCK_Stream stream;
	ACE_LSOCK_Connector Connector;
	Connector.connect(stream, "/tmp/foo");
	ACE_HANDLE a;
	while(1){
	stream.recv_handle(a);
	cout<<"handle received\n";
	//client_acceptor.set_handle(a);
	//client_acceptor.accept(cli_stream,&client);
	//perror("accept ");
	int t=fork();
	if(t==0){
	


	char buf[100];
	char ans[100];
	while(1){
	recv(a,buf,100,0);
	cout<<"received"<<endl;
	cout<<buf<<endl;
	int i;
	for(i=0;i<strlen(buf);i++) 
		{ ans[i]=toupper(buf[i]); }
	ans[i]='\0';
	send(a,ans,100,0);
		}
	}
	else{
		close(a);
	}
  }
}