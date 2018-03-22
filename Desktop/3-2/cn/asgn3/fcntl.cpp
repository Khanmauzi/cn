/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/


#include <unistd.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

int main()
{
	
	int fd = fcntl(1, F_DUPFD, 0);

	write(fd, "this is awesome\n", 16);
	// cout<<"yo"<<endl;
	return 0;
}