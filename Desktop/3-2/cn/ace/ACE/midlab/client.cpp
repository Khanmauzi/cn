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
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

int m=50;
vector<int>v;
int main()
{
	srand(time(NULL));
	ACE_INET_Addr server(5000,"127.0.0.1");
	ACE_SOCK_Stream cli_stream;
	ACE_SOCK_Connector connection_obj;

	connection_obj.connect(cli_stream,server);
	perror("connect ");
	char x[2];
	cli_stream.recv_n(x,2,0);
	//perror("recieving ");
	//cout<<x<<endl;
	int n=int(x[0])-'0';
	//cout<<n<<endl;;
	int k;
	for(int i=0;i<n;i++){
		k=rand()%m;
		cout<<k<<endl;
		v.push_back(k);
		}

	int size=v.size();
	cout<<"##################################"<<endl;
	char ans1[2],ans[100];
	char ans2[2];
	ans1[0]='y';
	ans2[0]='n';
	cli_stream.recv_n(ans,100,0);
	perror("test recieve ");
	cout<<ans<<endl;
	while(1)
	{
		char buf[100];
		cli_stream.recv_n(buf,100,0);				//recieve a number from the number distributor
		perror("recieving ");
		int n=0;
		for(int i=0;i<strlen(buf);i++){
			n=n*10+(int)buf[i]-'0';
		}
		cout<<"*********"<<n<<"************"<<endl;
		for(int j=0;j<v.size();j++){
			if(v[j]==n){
				v[j]==-1;
				size--;
			}
		}
		if(size==0){							//all number got cancelled ,client won the show
			cli_stream.send_n(ans1,2,0);
			perror("0 sending");
			break;
		}
		else{
			cli_stream.send_n(ans2,2,0);
			perror("ans2 sending");
		}
	}
	cout<<"out of the while loop "<<endl;
	return 0;
}