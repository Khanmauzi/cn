#include<bits/stdc++.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
using namespace std;

vector<int> sfds;
vector<int>tempfds;
int sfd; 
int port=8010;
int max_fd=0;

void *get_msgs(void *p)
{
  while(1)
  { 
    struct sockaddr_in add;
    socklen_t addlen;
    char buff[50]; 
    recvfrom(sfd,buff,50,0,(struct sockaddr *)&add,&addlen);
    int temp=socket(AF_INET,SOCK_STREAM,0);
   
    //struct sockaddr_in add;
    //int addlen=sizeof(add);
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = inet_addr("127.0.0.1");
    add.sin_port = htons(atoi(buff));  
    connect(temp,(struct sockaddr *)&add,addlen); 
    sfds.push_back(temp);
    int cid=socket(AF_INET,SOCK_STREAM,0);     
    add.sin_port = htons(port);  
    if(bind(cid,(struct sockaddr *)&add,sizeof(add))<0)
    cout<<"error in binding "<<endl;
    listen(cid,2);
    
    tempfds.push_back(cid);
    port++;
    max_fd=max(max_fd,cid);
  }
}

int main(int argc,char *argv[])
{
  int opt=1;
  cout<<"hello"<<endl;  
  sfd=socket(AF_INET,SOCK_DGRAM,0);
   
  struct sockaddr_in add;
  add.sin_family = AF_INET;
  add.sin_addr.s_addr = inet_addr("127.0.0.1");
  add.sin_port = htons(8005);  
  int addrlen=sizeof(add);
  if(bind(sfd,(struct sockaddr *)&add,sizeof(add))<0)
  cout<<"error in binding "<<endl;
  pthread_t t1;
  pthread_create(&t1,NULL,get_msgs,NULL);
  while(1)
  {
     fd_set readfds;
     struct timeval t;
     t.tv_sec=5;
     t.tv_usec=0;
     for(int i=0;i<tempfds.size();i++)
     FD_SET(tempfds[i],&readfds); 
     
     int no=select(max_fd+1,&readfds,NULL,NULL,&t);
     if(no>0)
     for(int i=0;i<tempfds.size();i++)
     {
        if(FD_ISSET(tempfds[i],&readfds))
        {
           int nsfd=accept(tempfds[i],(struct sockaddr *)&add,(socklen_t*)&addrlen);
           char b[]="serve";
           write(sfds[i],b,strlen(b)+1);      
           char buff[100];
           read(sfds[i],buff,100);
           write(nsfd,buff,strlen(buff)+1);
        } 
     }  

  }  
  
  return 0;

}
