// message queue ipc mechanism

/*	NAME : MOJAMMIL
	ROLL : 157238
	BTECH: 2015-19 NIT W
*/


#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <error.h>
using namespace std;
struct msgdata{
	long mtype;							//messasge type to be specified (0,1,2 etc);
	char buff[200];						//message to be sent
};



int main(){
	int msgid;		// every message is accesed by an id by which we can access the msg
	key_t key;		//every queue needs a key which the sender and reciver will agree upon
	

	//now generate the key

	if((key=ftok("reciever.cpp",'b'))==-1){		//this key will be used by both sender and reciever to access the que
		perror("key ");
		exit(0);
	}

	//now get the msgid

	if((msgid=msgget(key,0644|IPC_CREAT))==-1){
		perror("message id : ");
		exit(0);
	} 			

	struct msgdata msg;
	msg.mtype=1;						//set the message type

	string s;
	while(1){						//send the message
		getline(cin,s);
		strcpy(msg.buff,s.c_str());
		if(msgsnd(msgid,&msg,sizeof(msg),0)==-1){
			perror("sending in messasge");
		}
	}
	msgctl(msgid,IPC_RMID,NULL);

	return 0;
}