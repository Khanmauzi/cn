// Harsha

#include "ace/SOCK_Acceptor.h"
#include "ace/SOCK_Stream.h"
#include "ace/LSOCK_Stream.h"
#include "ace/LSOCK_Acceptor.h"
#include "ace/LSOCK.h"
#include "ace/OS.h"
#include<iostream>
using namespace std;
int main(){
	ACE_OS::unlink("/tmp/foo");	
	cout<<"Stuff"<<endl;
	ACE_LSOCK_Stream stream;
	ACE_LSOCK_Acceptor acceptor;
	ACE_INET_Addr s("127.0.0.1:5000"),client;
	ACE_SOCK_Acceptor a(s);
	acceptor.open((ACE_UNIX_Addr)"/tmp/foo");
	acceptor.accept(stream);
	stream.send_handle(a.get_handle());
	while(1) { ; }
}

