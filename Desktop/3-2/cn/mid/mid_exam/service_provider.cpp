#include<bits/stdc++.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
using namespace std;
int nsfd;
void *run(void *param)
{
   char buff[]="Service s1 done";
   write(nsfd,buff,strlen(buff)+1);
  
}

int main()
{
 int sfd=socket(AF_INET,SOCK_DGRAM,0);
  
  struct sockaddr_in add;
  add.sin_family = AF_INET;
  add.sin_addr.s_addr = inet_addr("127.0.0.1");
  add.sin_port = htons(8005);  
  socklen_t addrlen=sizeof(add);
  char buff[]="8006";
  sendto(sfd,buff,strlen(buff)+1,0,(struct sockaddr *)&add,addrlen);
    int temp=socket(AF_INET,SOCK_STREAM,0);
   
    //struct sockaddr_in add;
   // int addlen=sizeof(add);
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = inet_addr("127.0.0.1");
    int port=8006;
    add.sin_port = htons(port);  
    
    if(bind(temp,(struct sockaddr *)&add,sizeof(add))<0)
    cout<<"error in binding "<<endl;
    listen(temp,2);
    
     nsfd=accept(temp,(struct sockaddr *)&add,&addrlen);
    while(1)
    {
       char buff[20];
       read(nsfd,buff,20);
       pthread_t t;
       pthread_create(&t,NULL,&run,NULL);
      sleep(5);
    }
 return 0;
}
