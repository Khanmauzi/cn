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

 int    clientSocket2 = socket(PF_INET, SOCK_STREAM, 0);
serverAddr.sin_port = htons(8000);
  connect(clientSocket2,(sockaddr*)&serverAddr,addr_size);
  cout<<"connected\n";
  

  return 0;
}