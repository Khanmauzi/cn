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

using namespace std;

int main()
{
	int fd;
	char myfifo[] = "/tmp/myfifo2";
	char buffer[100];

	fd = open(myfifo, O_WRONLY);
	while(1)
	{
		cin.getline(buffer, 100);
		write(fd, buffer, strlen(buffer) + 1);
	}
	return 0;
}