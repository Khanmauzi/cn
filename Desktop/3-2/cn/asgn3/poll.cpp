/* 
    NAME : MOJAMMIL
    CLSS :BTECH
    157238 CSE 2015-19
*/


#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <iostream>
#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stropts.h>
#include <poll.h>

using namespace std;

struct pollfd fds[2];
int timeout_msecs = 5000, ret;

int main()
{
	cout<<"started"<<endl;
	int fd;
	char myfifo1[] = "/tmp/myfifo1";
	char myfifo2[] = "/tmp/myfifo2";
	mkfifo(myfifo1, 0666);
	mkfifo(myfifo2, 0666);

	char buffer[100];

	fds[0].fd = open(myfifo1, O_RDWR);
	fds[1].fd = open(myfifo2, O_RDWR);
	fds[0].events = POLLIN;
    fds[1].events = POLLIN;

    while(1)
    {
    	ret = poll(fds, 2, timeout_msecs);
    	if(ret > 0)
    	{
    		// cout<<"In ret"<<endl;
    		for(int i = 0; i < 2; i++)
    		{
    			if (fds[i].revents & POLLIN)
    			{
    				read(fds[i].fd, buffer, sizeof(buffer));
					cout<<buffer<<endl;
    			}

    			if (fds[i].revents & POLLOUT)
    			{
    				read(fds[i].fd, buffer, sizeof(buffer));
					cout<<buffer<<endl;
    			}
    			if (fds[i].revents & POLLWRBAND)
    			{
    				read(fds[i].fd, buffer, sizeof(buffer));
					cout<<buffer<<endl;
    			}
    			if (fds[i].revents & POLLHUP)
    			{

    				read(fds[i].fd, buffer, sizeof(buffer));
					cout<<buffer<<endl;
    			}
    		}
    	}
    	/*else
		{
			cout<<"timeout"<<endl;
		}*/

	}
	
	

	return 0;
}