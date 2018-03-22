#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
using namespace std;
int arr[100],c=0;
int main()
{
	int i,j,k,usfd,len;
	usfd=socket(AF_UNIX,SOCK_STREAM,0);

	sockaddr_un sadd,cadd;
	sadd.sun_family=AF_UNIX;
	strcpy(sadd.sun_path,"./red");
	bind(usfd,(sockaddr *)&sadd,sizeof(sadd));
	listen(usfd,10);

	while(1)
	{
		len=sizeof(cadd);//removing this causes error
		int nsfd=accept(usfd,(sockaddr *)&cadd,(socklen_t *)&len);
		cout<<"hello "<<endl;
		
		char in[100],out[100]="iam server";
		read(nsfd,in,100);
		write(nsfd,out,strlen(out)+1);
		cout<<in<<endl;
	}
	return 0;
}
