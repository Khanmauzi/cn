/*
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/


#include <iostream>
	#include <string.h>
	#include <unistd.h>
	#include <bits/stdc++.h>


	using namespace std;

	int main(){
		cout<<"this is main process  "<<endl;
		cout<<"process is calling fork process ."<<endl;
		char *arg[]={"./fork1",NULL};
		execvp(arg[0],arg);
		return 0;
	}