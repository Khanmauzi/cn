//dup system call


/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/


	#include <iostream>
	#include <fcntl.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <string>
	#include <bits/stdc++.h>
	#include <unistd.h>
	using namespace std;

	int main(){
		
		int filedisc=open("abc.txt",O_WRONLY | O_APPEND);
		if(filedisc<0){
			cout<<"fail to open the file "<<endl;
		}
		else{
			pid_t c=fork();
			int newdisc=dup(filedisc);
			if(c>0){		//this is parent process 
				cout<<"write through parent process (. to stop): "<<endl;
				while(1){
					string s;
					getline(cin,s);
					if(s==".")
					break;
					char a[s.length()+1];
					strcpy(a,s.c_str());
					a[s.length()]='\n';
					int k=s.length()+1;
					write(filedisc,a,k);				//writing through original file disc.
				}
			}
			else{				// this child process 
				cout<<"write through child process (. to stop): "<<endl;
				while(1){
					string s;
					getline(cin,s);
					if(s==".")
					break;
					char a[s.length()+1];
					strcpy(a,s.c_str());
					a[s.length()]='\n';
					int k=s.length()+1;
					write(newdisc,a,k);				//writing through copy file disc.
				}
			}
		}
		return 0;
	}