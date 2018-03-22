//client for the chat


/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/	




	#include <iostream>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <fcntl.h>
	#include <string>
	#include <pthread.h>
	#include <unistd.h>
	#include <bits/stdc++.h>



	using namespace std;
	string s;
	void *p1(void *argv){
		int flag=0;
		char *path="/tmp/server";
		mkfifo(path,0666);
		int fd;
		char arr1[1024];
		string s2;
		string s3;
		while(1){
		//		cin>>s2;

			if(flag==0){
				s3="."+s+":  ";
				flag=1;
			}
			else{
				getline(cin,s2);
				s3=s+":  "+s2;
				
			}

			strcpy(arr1,s3.c_str());
			//cout<<"s3 : "<<arr1;
			fd=open(path,O_WRONLY);
			//fgets(arr1,1024,stdin);
			write(fd,arr1,strlen(arr1)+1);
		}
		return NULL;
	}

	void *p2(void *argv){
		string pathname="/tmp/"+s;
		char path[pathname.length()];
		strcpy(path,pathname.c_str());
		//cout<<path<<endl;
		mkfifo(path,0666);
		int fd;
		char arr2[1024];
		while(1){
			fd=open(path,O_RDONLY);
			read(fd,arr2,sizeof(arr2));
			cout<<arr2<<endl;
			close(fd);
		}
	}
	int main(){
		cout<<"enter the usernae : ";
		cin>>s;

		pthread_t t1,t2;
		pthread_create(&t1,NULL,p1,NULL);
		pthread_create(&t2,NULL,p2,NULL);
		pthread_join(t1,NULL);
		pthread_join(t2,NULL);
		return 0;
	}