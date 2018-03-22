#include <iostream>
#include <unistd.h>
using namespace std;


void f(){
	int t=fork();
	if(t==0){
		cout<<getppid()<<" : " <<getpid()<<endl;
	}
}
int main(){
	cout<<"hii"<<getpid()<<endl;
	f();
}