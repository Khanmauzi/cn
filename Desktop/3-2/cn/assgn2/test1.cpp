

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
int main(){
	pid_t p1,p2;
	cout<<"hello world "<<endl;
	cout<<"process id is "<<getpid()<<endl;
	cout<<"parent process id is "<<getppid()<<endl;
	
	return 0;
}