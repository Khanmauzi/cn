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
	ACE_INET_Addr s1(3000,"127.0.0.1"),s2(4000,"127.0.0.1"),s3(5000,"127.0.0.1");
	ACE_SOCK_Stream cli_stream;
	ACE_SOCK_Connector connection_obj;

	char sn[5];
	cout<<"Enter service number u want to use : ";
	cin.getline(sn,5,'\n');
	if(sn[0]=='1'){ connection_obj.connect(cli_stream,s1); }
	else if(sn[0]=='2') { connection_obj.connect(cli_stream,s2); }
	else if(sn[0]=='3') { connection_obj.connect(cli_stream,s3); }
	perror("connect ");

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