#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#define address "unix"

using namespace std;

int main(){
	struct sockaddr_un server,client;
	unsigned int l=0;

	int usfd=socket(AF_UNIX,SOCK_STREAM,0);
	bzero(&server,sizeof(server));
	server.sun_family=AF_UNIX;
	strcpy(server.sun_path,address);
	unlink(address);
	l=sizeof(client);
	bind(usfd,(struct sockaddr*)&server,sizeof(server));
	listen(usfd, 10);
	while(1){
		int nsfd=accept(usfd,(struct sockaddr*)&client,(socklen_t*)&l);
		if(nsfd==-1){
			continue;
		}
		cout<<"connection established "<<endl;
		int t=fork();
		if(t==0){
			int cnt=3;
			close(usfd);
			while(cnt--){
				char buffer[100];
				read(nsfd,buffer,100);
				cout<<cnt<<" : "<<buffer<<endl;
			}
			close(nsfd);
		}
		else close(nsfd);
	}
}