
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
using namespace std;

int main(){
	char *path="/tmp/p1";
	mkfifo(path,0666);
	char arr2[100];
	int fd;
	while(1){
		fd=open(path,O_WRONLY);
		char *arr1;
		string s;
		getline(cin,s);
		int l=s.length();
		arr1=new char[l];
		strcpy(arr1,s.c_str());
		write(fd,arr1,strlen(arr1)+1);
		close(fd);
		fd=open(path,O_RDONLY);
		read(fd,arr2,100);
		cout<<arr2<<endl;
	}
	return 0;
}