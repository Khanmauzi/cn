// Mojammil

#include "ace/SOCK_Acceptor.h"
#include "ace/SOCK_Stream.h"
#include "ace/LSOCK_Stream.h"
#include "ace/LSOCK_Acceptor.h"
#include "ace/LSOCK.h"
#include "ace/OS.h"
#include<iostream>
using namespace std;
int main(){
	ACE_OS::unlink("/tmp/foo");	
	cout<<"Stuff"<<endl;
	ACE_LSOCK_Stream stream;
	ACE_LSOCK_Acceptor acceptor;
	acceptor.open((ACE_UNIX_Addr)"/tmp/foo");
	acceptor.accept(stream);

	ACE_SOCK_Stream cli_stream;
	//ACE_INET_Addr client;
	ACE_INET_Addr s("127.0.0.1:5001"),client;
	ACE_SOCK_Acceptor a(s);
	while(1) {
	  a.accept(cli_stream,&client);
	  cout<<"client address:"<<client.get_host_name()<<":"<<client.get_port_number()<<endl;
	  ACE_HANDLE fd = cli_stream.get_handle();		//getting handle
	  char a[2];
	  a[0]='9';
	  a[1]='\n';
	  send(fd,a,2,0);
	  perror("sending ");
	  stream.send_handle(fd);

	 }
}

