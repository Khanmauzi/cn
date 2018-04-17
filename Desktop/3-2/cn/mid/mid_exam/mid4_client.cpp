#include<bits/stdc++.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
using namespace std;
int port=8009;
int main()
{
  
  int opt=1;
  int sfd=socket(AF_INET,SOCK_STREAM,0);
  setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)); 
  
  struct sockaddr_in add;
  add.sin_family = AF_INET;
  add.sin_addr.s_addr = inet_addr("127.0.0.1");
  int val;
  cout<<"which service "<<endl;
  cin>>val;
  val+=port;
  add.sin_port = htons(val);  
  
  if(connect(sfd,(struct sockaddr *)&add,sizeof(add)))
  cout<<"failed in connection "<<endl;
   
  char b[100]; 
  read(sfd,b,100); 
  
  cout<<b<<endl;

  return 0;
}
