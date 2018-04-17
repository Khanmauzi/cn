#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std;
int main()
{
  int opt=1;
  int sfd=socket(AF_INET,SOCK_STREAM,0);
  
  setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)); 
  
  struct sockaddr_in add;
  add.sin_family = AF_INET;
  add.sin_addr.s_addr = inet_addr("127.0.0.1");
  add.sin_port = htons(8010);  
  int addrlen=sizeof(add);
  
   if(connect(sfd,(struct sockaddr *)&add,sizeof(add)))
   cout<<"failed in connection "<<endl;
   int no;
   cout<<"which request "<<endl;
   cin>>no;
   string s=to_string(no);
   send(sfd,s.c_str(),s.length()+1,0); 
   char buff[40]; 
   read(sfd,buff,40); 
   
   cout<<buff<<endl;
  return 0; 
}
