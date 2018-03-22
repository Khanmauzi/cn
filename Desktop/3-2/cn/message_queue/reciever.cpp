// message queue ipc mechanism

/*	NAME : MOJAMMIL
	ROLL : 157238
	BTECH: 2015-19 NIT W
*/
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <error.h>

using namespace std;

struct msgdata{
	long mtype;
	char buff[200];
};

int main(){
	int msgid;
	key_t key;
	struct msgdata msg;			//create the instance of the msgdata
	if((key=ftok("reciever.cpp",'b'))==-1){
		perror("key");
		exit(1);
	}
	if((msgid=msgget(key,0644))==-1){
		perror("msgid");
		exit(1);
	}
	while(1){
		msgrcv(msgid,&msg,sizeof(msg),1,0);
		cout<<msg.buff<<endl;
	}
	return 0;


}

