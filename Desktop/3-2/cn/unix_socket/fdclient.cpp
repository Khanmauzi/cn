//unix socket simple example(passing file descriptor)
/*
	NAME :MOJAMMIL
	ROLL :157238
	BATCH :2015-19 CSE
	NIT WARANGAL
*/


#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <iostream>

using namespace std;

static void send_fd(int socket, int *fds, int n)  // send fd by socket
{
        struct msghdr msg = {0};
        struct cmsghdr *cmsg;
        char buf[CMSG_SPACE(sizeof(fds))], dup[256];
        memset(buf, '\0', sizeof(buf));
        struct iovec io = { .iov_base = &dup, .iov_len = sizeof(dup) };

        msg.msg_iov = &io;
        msg.msg_iovlen = 1;
        msg.msg_control = buf;
        msg.msg_controllen = sizeof(buf);

        cmsg = CMSG_FIRSTHDR(&msg);
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;
        cmsg->cmsg_len = CMSG_LEN(n * sizeof(int));

        memcpy ((int *) CMSG_DATA(cmsg), fds, n * sizeof (int));
        sendmsg (socket, &msg, 0);

        /*if (sendmsg (socket, &msg, 0) < 0)
                handle_error (“Failed to send message”);*/
}

int main() {
        int sfd, fds[2];
        struct sockaddr_un addr;
      
        sfd = socket(AF_UNIX, SOCK_STREAM, 0);
        
       // memset(&addr, 0, sizeof(struct sockaddr_un));
        addr.sun_family = AF_UNIX;
        strcpy(addr.sun_path,"./path");

        fds[0] = open("abc1.txt",O_RDONLY);

        fds[1] = open("abc2.txt", O_RDONLY);
        cout<<"running client : "<<endl;

        connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un));

        send_fd (sfd, fds, 2);

}