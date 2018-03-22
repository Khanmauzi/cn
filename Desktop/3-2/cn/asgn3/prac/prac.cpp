


#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
using namespace std;

int main(){
	int f;
	int fd=open("abc.txt",O_RDONLY);
	int cnt=1;
	while(f!=0){
		char buffer[100];
		int i=0;
		char ch[1];
		while(1){
			f=read(fd,ch,1);
			if(ch[0]=='\n')
				break;
			buffer[i++]=ch[0];
		}
		cout<<cnt<<" : "<<buffer<<endl;
		cnt++;
		memset(buffer,0,sizeof(buffer));
	}
	return 0;
}