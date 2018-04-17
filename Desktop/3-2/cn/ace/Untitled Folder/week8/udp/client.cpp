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
	ACE_INET_Addr server("127.0.0.1:3000"),client("127.0.0.1:6000");
	ACE_SOCK_Dgram data(client);

	while(1)
	{
		char buf[100],ans[100];
		cin.getline(buf,100,'\n');
		data.send(buf,100,server);
		data.recv(ans,100,server);
		cout<<"result : "<<ans<<endl;
	}

	return 0;
}