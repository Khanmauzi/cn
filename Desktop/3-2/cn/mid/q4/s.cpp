/************* UDP CLIENT CODE *************c******/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <bits/stdc++.h>
#include <unistd.h>
#include<arpa/inet.h>
using namespace std;
int main(){
  int clientSocket, portNum, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*Create UDP socket*/
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverAddr;

    printf("press enter to start server\n");
    fgets(buffer,1024,stdin);
    printf("server is registerd: %s",buffer);

    nBytes = strlen(buffer) + 1;
    
    /*Send message to server*/
    sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);

    /*Receive message from server*/
                nBytes = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);

    printf("Received from server: %s\n",buffer);
    sleep(1);
 int    clientSocket2 = socket(PF_INET, SOCK_STREAM, 0);
serverAddr.sin_port = htons(8000);
  connect(clientSocket2,(sockaddr*)&serverAddr,addr_size);
  cout<<"connected\n";
  char* msg="hello";
  send(clientSocket2,msg,strlen(msg),0);
  cout<<"send"<<endl;

  while(1)
  {
    char ms[100];
    recv(clientSocket2,ms,100,0);
    cout<<"ms="<<ms<<endl;
    char m[100]="Received";
    send(clientSocket2,m,strlen(m),0);
  }
  return 0;
}