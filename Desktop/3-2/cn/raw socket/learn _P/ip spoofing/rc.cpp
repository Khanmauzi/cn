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
#include <assert.h>

#define MAX 100

int main(int argc, char const *argv[]) {
    struct sockaddr_in addr; int rsfd, n=1, len; char buffer[MAX];
    rsfd = socket(AF_INET, SOCK_RAW, 149);
    if(rsfd < 0) 
    {
        perror("socket() ");
        exit(1);
    }
    int val = 1;
    if(setsockopt(rsfd, IPPROTO_IP, IP_HDRINCL, &val, sizeof(val)) < 0) {
        perror("setsockopt() ");
    }
    memset((char *)&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
   // addr.sin_port = 9001;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    char buf[MAX];
    while(1) {
        memset(buf, 0, MAX);
        strcpy(buf,"mauzi\n");
        memset(buffer, 0 , MAX);
       struct iphdr * iph; unsigned short iphdrlen;
        iph = (struct iphdr *)buffer;
        iph->version = 4; /* IPv4 */
        iph->ihl = 5; /* default 5 */
        iph->tos = 0;
        iph->frag_off = 0;
        iph->ttl = 8;
        iph->protocol = 161;
        iph->saddr = inet_addr("192.0.3.1");
        iph->daddr = inet_addr("192.0.1.1");
        strcpy(buffer+sizeof(struct iphdr), buf);
        iph->tot_len = htons(sizeof(struct iphdr)+strlen(buf));
       
        if(sendto(rsfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, sizeof addr) < 0) {
            perror("sendto() ");
        }
        
    }
    return 0;
}