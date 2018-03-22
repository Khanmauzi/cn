#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/un.h>
using namespace std;
int arr[100],c=0;
int main()
{
	int i,j,k,usfd,len;
	usfd=socket(AF_UNIX,SOCK_STREAM,0);

	sockaddr_un sadd,cadd;
	sadd.sun_family=AF_UNIX;
	strcpy(sadd.sun_path,"./red");
	
	connect(usfd,(sockaddr *)&sadd,sizeof(sadd));
	char in[100],out[100]="iam client";
	write(usfd,out,100);
	read(usfd,in,100);
	cout<<in<<endl;

	return 0;
}