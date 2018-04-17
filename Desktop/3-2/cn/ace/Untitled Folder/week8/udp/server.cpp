#include <ace/Reactor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Dgram.h>
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
	ACE_SOCK_Dgram data(server);

	while(1)
	{
		char buf[100],ans[100];
		data.recv(buf,100,client);
		cout<<client.get_host_name()<<" "<<client.get_port_number()<<"\n";
		cout<<"client : "<<buf<<endl;
		int i; for(i=0;i<strlen(buf);i++) { ans[i]=toupper(buf[i]); }
		ans[i]='\0';
		data.send(ans,100,client);
	}

	return 0;
}