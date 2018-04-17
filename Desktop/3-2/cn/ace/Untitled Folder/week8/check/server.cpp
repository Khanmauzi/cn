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
using namespace std;

int main()
{
	ACE_INET_Addr server("127.0.0.1:3000"),client;
	ACE_SOCK_Acceptor client_acceptor(server);
	ACE_SOCK_Stream cli_stream;

	client_acceptor.accept(cli_stream,&client);
	perror("accept ");
	cout<<"client address:"<<client.get_host_name()<<":"<<client.get_port_number()<<endl;
	ACE_HANDLE fd = cli_stream.get_handle();

	while(1)
	{
		char buf[100],ans[100];
		recv(fd,buf,100,0);
		cout<<"client : "<<buf<<endl;
		int i; for(i=0;i<strlen(buf);i++) { ans[i]=toupper(buf[i]); }
		ans[i]='\0';
		send(fd,ans,100,0);
	}
	return 0;
}