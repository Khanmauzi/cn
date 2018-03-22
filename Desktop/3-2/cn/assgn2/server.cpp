//server for the chat


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
	#include <iterator>
	#include <set>

	using namespace std;

	char arr1[1024];
	int flag=0;
	/*void * p1(void * argv){
		char *path="/tmp/server";
		int fd;
		mkfifo(path,0666);
		while(1){
			fd=open(path,O_RDONLY);
			read(fd,arr1,sizeof(arr1));
			cout<<arr1<<endl;
			flag=1;
		}
		return NULL;
	}

	void * p2(void* argv){
		vector<string>v;
		 char *path;
		while(1){
			int i=0;
			 char arr2[80];
			string temp="";
			if(flag==1){
				if(arr1[i]=='.'){
					i++;
				}
				while(arr1[i]!=':'){
					temp=temp+arr1[i++];
				}
				v.push_back(temp);
				flag=0;
				int k=0;
				while(arr1[i]){
					arr2[k++]=arr1[i]++;
				}
				//or(int j=0;j<v.size();j++){
					//path="/tmp/"+tochar(v[j]);
					char *path="/tmp/mauzi";
					mkfifo(path,0666);
					int fd=open(path,O_WRONLY);
					write(fd,arr1,strlen(arr1)+1);
				//}
			}
		}
		return NULL;
	}*/

	int main(){

		//pthread_t t1,t2;
		//pthread_create(&t1,NULL,p1,NULL);
		//pthread_create(&t2,NULL,p2,NULL);
		//'pthread_join(t1,NULL);
		//pthread_join(t2,NULL);
		char *path1="/tmp/server";
		int fd;
		set<string>s;
		string name;
		cout<<"starting chat server : "<<endl;
		while(1){
			mkfifo(path1,0666);
			fd=open(path1,O_RDONLY);						
			int i=0;
			read(fd,arr1,sizeof(arr1));						//reading message sent by client
			cout<<arr1<<endl;
			string path;
			if(arr1[i]=='.'){
				flag=1;
				name="***************";
				i++;
				close(fd);
				 path="/tmp/";
				while(arr1[i]!=':'){								//making path for fifo
					path=path+arr1[i];
					name=name+arr1[i];
					i++;
				}
			}
			else{
				name="";
				 path="/tmp/";
				while(arr1[i]!=':'){								//making path for fifo
					path=path+arr1[i];
					name=name+arr1[i];
					i++;
				}
			}
			name=name+" has joined the group ************";
			//cout<<"path: "<<path<<endl;
			s.insert(path);
			set<string>::iterator it;
			if(flag==1){
				for(it=s.begin();it!=s.end();it++){
					string s1=*it;
					int l=s1.length();
					char temp[l];
					strcpy(temp,s1.c_str());
					char arr2[1024];
					
					strcpy(arr2,name.c_str());
					mkfifo(temp,0666);
					int fd=open(temp,O_WRONLY);
					write(fd,arr2,strlen(arr2)+1);
					close(fd);

				}
			}
			else{
					for(it=s.begin();it!=s.end();it++){
					string s1=*it;
					int l=s1.length();
					char temp[l];
					strcpy(temp,s1.c_str());
					mkfifo(temp,0666);
					int fd=open(temp,O_WRONLY);
					write(fd,arr1,strlen(arr1)+1);
					close(fd);
				}

			}
			flag=0;
			
		}
		return 0;
	}