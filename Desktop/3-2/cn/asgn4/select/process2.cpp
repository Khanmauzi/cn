#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


using namespace std;

int main(){
	char *messg="executing process 2 ";
	write(0,messg,strlen(messg)+1);
	exit(-1);
}