//

#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

int main(){
	pid_t t=fork();
	if(t==0){
		char *path[]={"./t2",NULL};
		execvp(path[0],path);
	}
	if(t>0){
		while(1){
			cout<<"reading first file : "<<endl;
			sleep(2);
		}
	}
	
}