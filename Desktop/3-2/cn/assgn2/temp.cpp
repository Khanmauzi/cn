

#include <iostream>
#include <unistd.h>


using namespace std;
pid_t pd;
int main(){
	cout<<"hello world "<<endl;

	pd=fork();
	if(pd!=0){
	cout<<"process id is : "<<getpid()<<endl;
	cout<<"new craeted process, id is : "<<pd<<endl;}
	if(pd==0){
		char *arg[]={"./test1",NULL};
		execvp(arg[0],arg);
	}
	return 0;
}