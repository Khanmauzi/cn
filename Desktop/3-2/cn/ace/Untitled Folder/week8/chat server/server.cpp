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
#include <pthread.h>
using namespace std;

ACE_SOCK_Stream clients[20];
int n,live[20];

class Myio : public ACE_Event_Handler{
	public :
	Myio(int k)
	{
		number = k;
	}

	int handle_input(ACE_HANDLE)
	{
		char buf[100],ans[100];
		if(this->cli_stream.recv_n(buf,100,0)<1) { live[number]=0; return -1; }
		cout<<"client "<<number<<" : "<<buf<<endl;
		for(int i=0;i<n;i++)
		{
			if(i!=number && live[i])
			{ clients[i].send_n(buf,100,0); }
		}
		return 0;
	}

	ACE_HANDLE get_handle()const{
		return this->cli_stream.get_handle();
	}

	ACE_SOCK_Stream & peer_i(){
		return this->cli_stream;
	}

	private :
	ACE_SOCK_Stream cli_stream;
	int number;
};

class Myaccpetclass : public ACE_Event_Handler{
	public : 
	Myaccpetclass(ACE_INET_Addr &server)
	{
		this->client_acceptor.open(server);
	}

	int handle_input(ACE_HANDLE)
	{
		// cout<<"Strated\n";
		Myio *clihandler = new Myio(n);
		client_acceptor.accept(clihandler->peer_i(),0,0);
		clients[n] = clihandler->peer_i(); live[n] = 1; n++;
		perror("accept ");
		ACE_Reactor::instance()->register_handler(clihandler,ACE_Event_Handler::READ_MASK);
		perror("register ");
		return 0;
	}

	ACE_HANDLE get_handle()const{
		return this->client_acceptor.get_handle();
	}

	private : 
	ACE_SOCK_Acceptor client_acceptor;
};

int main()
{
	n=0;
	ACE_INET_Addr server("127.0.0.1:3000");
	Myaccpetclass *accObj = new Myaccpetclass(server);
	ACE_Reactor::instance()->register_handler(accObj,ACE_Event_Handler::ACCEPT_MASK);

	while(1)
	{
		ACE_Reactor::instance()->handle_events();
		// cout<<"again\n";
	}
	return 0;
}