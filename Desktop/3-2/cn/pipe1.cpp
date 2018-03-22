//  pipe

/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/

	#include <iostream>
	#include <sys/types.h>
	#include <stdio.h>
	#include <string>
	#include <unistd.h>
	#include <fcntl.h>
	#include <sys/stat.h>
	#include <bits/stdc++.h>

	using namespace std;

	int main(){
		int pfd[2];
		pipe(pfd);
		char arr1[80],arr2[80];
		int c=fork();
		if(c>0){	//parent process 
			while(1){
			close(pfd[0]);
			fgets(arr1,80,stdin);
			write(pfd[1],arr1,strlen(arr1)+1);
			}
		}

		else {	//child process 
			while(1){
			close(pfd[1]);
			read(pfd[0],arr2,80);
			cout<<"parent message : "<<arr2<<endl;
			}
		}
		return 0;
	}