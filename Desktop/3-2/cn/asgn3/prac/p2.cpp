#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

using namespace std;


int main(){
	char *path="/tmp/p1";
	int fd;
	char arr1[100];
	mkfifo(path,06666);
	while(1){
		char *arr2;
		fd=open(path,O_RDONLY);
		read(fd,arr1,100);
		cout<<arr1<<endl;
		close(fd);
		fd=open(path,O_WRONLY);
		string s;
		int l=s.length();
		arr2=new char[l];
		getline(cin,s);
		strcpy(arr2,s.c_str());-
		write(fd,arr2,strlen(arr2)+1);
		close(fd);
	}
	return 0;
}