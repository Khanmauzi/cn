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

int main()
{
	ACE_INET_Addr server("127.0.0.1:3000"),client,s("127.0.0.1:5000");
	ACE_SOCK_Acceptor client_acceptor;
	//,a(s);
	ACE_SOCK_Stream cli_stream;

	cout<<"Stuff"<<endl;
	ACE_LSOCK_Stream stream;
	ACE_LSOCK_Connector Connector;
	Connector.connect(stream, "/tmp/foo");
	ACE_HANDLE a;
	stream.recv_handle(a);
	cout<<"handle received\n";

	// client_acceptor.set_handle(a.get_handle());
	client_acceptor.set_handle(a);
	client_acceptor.accept(cli_stream,&client);
	// cli_stream.set_handle(a);
	perror("accept ");
	cout<<"client address:"<<client.get_host_name()<<":"<<client.get_port_number()<<endl;

	while(1)
	{
		char buf[100],ans[100];
		cli_stream.recv_n(buf,100,0);
		cout<<"client : "<<buf<<endl;
		int i; 
		for(i=0;i<strlen(buf);i++) 
		{ ans[i]=toupper(buf[i]); }
		ans[i]='\0';
		cli_stream.send_n(ans,100,0);
	}
	return 0;
}