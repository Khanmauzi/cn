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

ACE_SOCK_Stream cli_stream;

void *receive(void *arg)
{
	while(1)
	{
		char ans[100];
		cli_stream.recv_n(ans,100,0);
		cout<<"Message : "<<ans<<endl;
	}
}

void *sending(void *arg)
{
	while(1)
	{
		char buf[100],ans[100];
		cin.getline(buf,100,'\n');
		cli_stream.send_n(buf,100,0);
	}
}

int main()
{
	ACE_INET_Addr server(3000,"127.0.0.1");
	ACE_SOCK_Connector connection_obj;

	connection_obj.connect(cli_stream,server);
	perror("connect ");

	pthread_t t1,t2;
	pthread_create(&t1,NULL,sending,NULL);
	pthread_create(&t2,NULL,receive,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}