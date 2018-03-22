//unix socket simple example(passing file descriptor)
/*
        NAME :MOJAMMIL
        ROLL :157238
        BATCH :2015-19 CSE
        NIT WARANGAL
*/

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;

static int * recv_fd(int socket, int n) {
        cout<<"Test1 "<<endl;
        int *fds = (int *)malloc (n * sizeof(int));
        struct msghdr msg = {0};
        struct cmsghdr *cmsg;
        cout<<"Test2 "<<endl;
        char buf[CMSG_SPACE(n * sizeof(int))], dup[256];
        memset(buf, '\0', sizeof(buf));
        struct iovec io = { .iov_base = &dup, .iov_len = sizeof(dup) };
        cout<<"Test3 "<<endl;
        msg.msg_iov = &io;
        msg.msg_iovlen = 1;
        msg.msg_control = buf;
        msg.msg_controllen = sizeof(buf);
        cout<<"Test4 "<<endl;
        recvmsg (socket, &msg, 0);

        cmsg = CMSG_FIRSTHDR(&msg);
        cout<<"Test5 "<<endl;
        memcpy (fds, (int *) CMSG_DATA(cmsg), n * sizeof(int));
        cout<<"Test6 "<<endl;
        return fds;
}

int main() {
        ssize_t nbytes;
        char buffer[256];
        int sfd, cfd, *fds;
        struct sockaddr_un addr,client;

        sfd = socket(AF_UNIX, SOCK_STREAM, 0);

        memset(&addr, 0, sizeof(struct sockaddr_un));
        addr.sun_family = AF_UNIX;
        strcpy(addr.sun_path,"./path");

        bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un));
        listen(sfd, 5);
        
         while(1){
         int l=sizeof(client);
        cfd = accept(sfd,(struct sockaddr*)&client,(socklen_t *)&l);
        cout<<"connected from client "<<endl;
        fds = recv_fd (cfd, 2);
        cout<<"recieving fds "<<endl;
        for (int i=0; i<2; ++i) {
                cout<<"reading from passed fd : "<<fds[i]<<endl;
                while(read(fds[i],buffer,256)){
                        cout<<buffer<<endl;
                }
        }

        if (close(cfd) == -1)
                exit(1);
        }
        return 0;
}