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
	ACE_INET_Addr server(5001,"127.0.0.1");
	ACE_SOCK_Stream cli_stream;
	ACE_SOCK_Connector connection_obj;

	connection_obj.connect(cli_stream,server);
	perror("connect ");
	char x[2];
	cli_stream.recv_n(x,2,0);
	//perror("recieving ");
	cout<<x<<endl;

	while(1)
	{
		char buf[100],ans[100];
		cin.getline(buf,100,'\n');
		cout<<buf<<endl;
		cli_stream.send_n(buf,100,0);
		perror("sending ");
		cli_stream.recv_n(ans,100,0);
		cout<<"Result from client : "<<ans<<endl;
	}
	return 0;
}