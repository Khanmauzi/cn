#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/if_ether.h>
#include <netdb.h>
#include<bits/stdc++.h>
using namespace std;
#define MAX 100

/*
__u8 	tos
__u16 	tot_len
__u16 	id
__u16 	frag_off
__u8 	ttl
__u8 	protocol
__u16 	check
__u32 	saddr
__u32 	daddr

*/
int msgcount =0;
int main(int argc ,char *argv[])
{
	struct sockaddr_in addr,client;
	int rsfd = socket(AF_INET, SOCK_RAW, 161);
    if(rsfd < 0) {
        perror("socket() ");
        exit(1);
    }
   
   
    memset((char *)&addr, 0, sizeof addr);
  //  addr.sin_family = AF_INET;
    //addr.sin_port = 8001;
    //addr.sin_addr.s_addr = inet_addr("127.0.0.1");
   // if(bind(rsfd, (struct sockaddr*)&addr, sizeof addr) < 0) {
   //     perror("bind() ");
   //     exit(1);
  //  }
    char buffer[MAX];
    char buf[MAX];
    struct iphdr * iph; 
    unsigned int header_length;
    printf("waitng for packets\n");
    char reply[]="message by server ";
    while(1) {
        int len = sizeof(addr);
        if(recvfrom(rsfd, buffer, MAX, 0, (struct sockaddr *)&client, (socklen_t*)&len) < 0) {
            perror("recvfrom() ");
        }
   // cout<<"client ip : "<<inet_ntoa(client.sin_addr)<<endl;
	printf("Packet Count is now %d \n\n", ++msgcount);
    iph = (struct iphdr *) buffer;
    struct sockaddr_in s_addr, d_addr;
	memset((char *)&s_addr, 0, sizeof s_addr);
	memset((char *)&d_addr, 0, sizeof d_addr);
	header_length = iph->ihl*4;
	s_addr.sin_addr.s_addr = iph->saddr;
	d_addr.sin_addr.s_addr = iph->daddr;
	printf("------------- IP Header ------------\n");
	printf("|%4d|%4d|%8d|%16d|\n", (unsigned int)iph->version, (unsigned int)iph->ihl, (unsigned int)iph->tos, ntohs(iph->tot_len));
	printf("------------------------------------\n");
	printf("|%16d|R|D|M|%13d|\n", ntohs(iph->id), (unsigned int)iph->frag_off);
	printf("------------------------------------\n");
	printf("|%8d|%8d|%16d|\n", (unsigned int)iph->ttl, (unsigned int)iph->protocol, ntohs(iph->check));
	printf("------------------------------------\n");
	printf("%s\n", inet_ntoa(s_addr.sin_addr));
	printf("------------------------------------\n");
	printf("%s\n", inet_ntoa(d_addr.sin_addr));
	printf("------------------------------------\n");
	strcpy(buf, buffer+header_length);
	printf("Message : %s\n", buf);


    //cout<<"client ip : "<<inet_ntoa(client.sin_addr)<<endl;
    sendto(rsfd,reply,sizeof(reply),0,(struct sockaddr*)&client,sizeof client);
    perror("sending");
    //cout<<"client ip : "<<inet_ntoa(client.sin_addr)<<endl;
    sleep(1);
    }
    return 0;



}