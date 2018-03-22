//  pipe 2 way communiction using pipe

/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/

// pipe1 send message to child and pipe 2 send message to parent
	#include <iostream>
	#include <bits/stdc++.h>
	#include <sys/types.h>
	#include <string>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/stat.h>

	using namespace std;

	int main(){
		int pfd1[2],pfd2[2];
		
		pipe(pfd1);
		pipe(pfd2);

		int c=fork();
		if(c>0){				//parent process
			while(1){
			char arr1[80],arr2[80];
			close(pfd1[0]);
			fgets(arr1,80,stdin);
			write(pfd1[1],arr1,strlen(arr1));
			close(pfd2[1]);
			read(pfd2[0],arr2,80);
			cout<<"child message : "<<arr2<<endl;}
		}
		else{							//child process
			while(1){
			char arr1[80],arr2[80];
			close(pfd1[1]);
			read(pfd1[0],arr2,80);
			cout<<"Parent message : "<<arr2<<endl;
			close(pfd2[0]);
			fgets(arr1,80,stdin);
			write(pfd2[1],arr1,strlen(arr1));}
		}
		return 0;
	}