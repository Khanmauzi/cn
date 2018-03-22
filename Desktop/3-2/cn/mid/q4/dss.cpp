

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include<arpa/inet.h>
using namespace std;
int main(){
  int udpSocket, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  map<string,int> clientfds;
  int i;
  /*Create UDP socket*/
  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
 int sfdport=9000;
  /*Configure settis in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*Bind socket with address struct*/
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverStorage;
  cout<<"SERVER RUNNING...\n";

       nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
       cout<<"UDP SELECT\n";
       cout<<"received="<<buffer<<endl;
       for(i=0;i<nBytes-1;i++)
      buffer[i] = toupper(buffer[i]);
       sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);


       //tcp connection
       vector<int> tsfd,sfd;
       char buf[100];
       serverAddr.sin_port = htons(8000);
       int tcpSocket = socket(PF_INET, SOCK_STREAM, 0);
       bind(tcpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
       listen(tcpSocket,10);
       int nfd=accept(tcpSocket,NULL,NULL);
       cout<<"accepted tcp"<<endl;
       tsfd.push_back(nfd);
       int size=recv(nfd,buf,100,0);
       cout<<"size="<<size<<endl;
       cout<<"CONNECT receive="<<buf<<endl;

        serverAddr.sin_port = htons(8088);sfdport++;  //PREPARING SFDi         
       int sfdi;
       sfdi = socket(PF_INET, SOCK_STREAM, 0);
       bind(sfdi, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
       listen(sfdi,10);
       sfd.push_back(sfdi);
      nfd=accept(tcpSocket,NULL,NULL);
      cout<<"accepted client="<<nfd<<endl;
          clientfds["c1"]=nfd;
         char m[100]="c1";
            send(tsfd[0],m,strlen(m)+1,0);
  while(1){
    /* Try to receive any incoming UDP datagram. Address and port of 
      requesting client will be stored on serverStorage variable */
    fd_set readfds;
    FD_ZERO(&readfds);
    for(int i=0;i<sfd.size();i++)
    FD_SET(sfd[i],&readfds);
  for(int i=0;i<tsfd.size();i++)
    FD_SET(tsfd[i],&readfds);
    int k=select(1024,&readfds,NULL,NULL,NULL);
    for(int i=0;i<sfd.size();i++)
    {
      if(FD_ISSET(sfd[i],&readfds))
      {
        cout<<"IN ACCEPT"<<endl;
          int nfd=accept(sfd[i],NULL,NULL);
          clientfds["c1"]=nfd;
         char m[100]="c1";
            send(sfd[i],m,strlen(m)+1,0);
      }
    }
    for(int i=0;i<tsfd.size();i++)
    {
      if(FD_ISSET(tsfd[i],&readfds))
      {
         cout<<"IN MSG TRANSFER\n";
         char ms[100];
         recv(tsfd[i],ms,100,0);
         cout<<"msg from server to client="<<ms<<endl;
         send(clientfds["c1"],ms,strlen(ms)+1,0);
      }
    }
    
  }

  return 0;
}