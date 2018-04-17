#include <ace/Reactor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Stream.h>
#include <ace/Thread.h>
#include <ace/Synch.h>
#include <ace/Log_Msg.h>
#include <ace/streams.h>
#include <ace/INET_Addr.h>
#include <bits/stdc++.h>
#include <errno.h>
using namespace std;

ACE_SOCK_Stream cli_streams[20];

void *service(void *arg)
{
	int k = *(int*)arg;
	cout<<k<<endl;
	while(1)
	{
		char buf[100],ans[100];
		if(cli_streams[k].recv_n(buf,100,0)<1) { break; }
		int i; for(i=0;i<strlen(buf);i++) { ans[i]=toupper(buf[i]); }
		ans[i]='\0';
		cli_streams[k].send_n(ans,100,0);
	}
}

int main()
{
	ACE_INET_Addr server("127.0.0.1:5000"),client;
	ACE_SOCK_Acceptor client_acceptor(server);
	int n=0;
	int a[10];
	while(1)
	{
		a[n] = n;
		client_acceptor.accept(cli_streams[n],&client);
		perror("accept ");
		cout<<"client address:"<<client.get_host_name()<<":"<<client.get_port_number()<<endl;
		ACE_Thread::spawn((ACE_THR_FUNC)service,&a[n]);
		// pthread_t t;
		// pthread_create(&t,NULL,service,&a[n]);
		n++;
	}
	
	return 0;
}