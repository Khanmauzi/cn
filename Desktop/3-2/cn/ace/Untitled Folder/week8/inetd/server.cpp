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

class Myio : public ACE_Event_Handler{
	public :
	Myio(int n)
	{
		x = n;
		cout<<"constructor\n";
	}

	int handle_input(ACE_HANDLE)
	{
		char buf[100],ans[100];
		if(this->cli_stream.recv_n(buf,100,0)<1) { return -1; }
		cout<<"client : "<<buf<<endl;
		if(x==1)
		{
			int i; for(i=0;i<strlen(buf);i++) { ans[i]=toupper(buf[i]); }
			ans[i]='\0';
		}
		else if(x==2)
		{
			int i; for(i=0;i<strlen(buf);i++) { ans[i]=tolower(buf[i]); }
			ans[i]='\0';
		}
		else if(x==3)
		{
			int i; 
			for(i=0;i<strlen(buf);i++) 
			{ 
				if(i%2) { ans[i]=tolower(buf[i]); }
				else { ans[i]=toupper(buf[i]); }
			}
			ans[i]='\0';
		}
		this->cli_stream.send_n(ans,100,0);
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
	int x;
};

class Myaccpetclass : public ACE_Event_Handler{
	public : 
	Myaccpetclass(ACE_INET_Addr &server)
	{
		this->port = server.get_port_number();
		this->client_acceptor.open(server);
	}

	int handle_input(ACE_HANDLE)
	{
		cout<<"Strated\n"; int n;
		if(port==3000) { n=1; }
		else if(port==4000) { n=2; }
		else if(port==5000) { n=3; }
		Myio *clihandler = new Myio(n);
		client_acceptor.accept(clihandler->peer_i(),0,0);
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
	int port;
};

int main()
{
	ACE_INET_Addr s1("127.0.0.1:3000"),s2("127.0.0.1:4000"),s3("127.0.0.1:5000");
	Myaccpetclass *accObj1 = new Myaccpetclass(s1);
	Myaccpetclass *accObj2 = new Myaccpetclass(s2);
	Myaccpetclass *accObj3 = new Myaccpetclass(s3);
	ACE_Reactor::instance()->register_handler(accObj1,ACE_Event_Handler::ACCEPT_MASK);
	ACE_Reactor::instance()->register_handler(accObj2,ACE_Event_Handler::ACCEPT_MASK);
	ACE_Reactor::instance()->register_handler(accObj3,ACE_Event_Handler::ACCEPT_MASK);

	while(1)
	{
		ACE_Reactor::instance()->handle_events();
		// cout<<"again\n";
	}
	return 0;
}