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
  vector<int> fd(4,-1);
  int opt=1;
  int sfd=socket(AF_INET,SOCK_STREAM,0);
  
  setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)); 
  
  struct sockaddr_in add;
  add.sin_family = AF_INET;
  add.sin_addr.s_addr = inet_addr("127.0.0.1");
  add.sin_port = htons(8010);  
  
  int addrlen=sizeof(add);
  
  if(bind(sfd,(struct sockaddr *)&add,sizeof(add))<0)
  cout<<"error in binding "<<endl;
  
  if(listen(sfd,10)<0)
  cout<<"error in listening"<<endl;
  int nsfd[100];
  int j=0;
  while(1)
  {
     nsfd[j]=accept(sfd,(struct sockaddr *)&add,(socklen_t*)&addrlen);  
     char buff[20];         
     recv(nsfd[j],buff,20,0);
     int i=atoi(buff);
     char b[100];
        
     if(fd[i-1]!=-1)
     {
       read(fd[i-1],b,40);
       write(nsfd[j++],b,strlen(b)+1);
           
     } 
     else
     {
       switch(i)
       {
         case 1:fd[i-1]=fileno(popen("./d1","r"));   
                 break;
                 
         case 2:fd[i-1]=fileno(popen("./d2","r"));   
                 break;
                 
         case 3:fd[i-1]=fileno(popen("./d3","r"));   
                 break;
                 
         case 4:fd[i-1]=fileno(popen("./d4","r"));   
                 break;
                       
       }
       cout<<"hello"<<endl;
       int temp;
 //      dup2(nsfd[j++],fd[i-1]); 
       read(fd[i-1],b,40);
       write(nsfd[j++],b,strlen(b)+1);
     }
     cout<<"done"<<endl;
  }
  return 0;
}
