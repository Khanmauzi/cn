/*client code for the test.x*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<rpc/rpc.h>
#include "test.h"

int main(int argc, char **argv){
	int c;
extern char *optarg;
extern int optind;
//printf("client is running \n ");
char *server = "localhost";  /* default */
int err = 0;
while ((c = getopt(argc, argv, "h:")) != -1)
	switch (c) {
		case 'h':
			server = optarg;
			break;
		case '?':
			err = 1;
			break;
	}
/* exit if error or extra arguments */
	//printf("client is running \n ");
if (err || (optind < argc)) {
	fprintf(stderr, "usage:  %s [-h hostname]\n", argv[0]);
	exit(1);
}


CLIENT *cl;  /* rpc handle */
//printf("client is running \n ");
cl = clnt_create(server, TEST_PROG, TEST_VERS, "udp");
char **sresult; /* return from msg */
if (argc != 1) {
	fprintf(stderr, "usage: %s\n", argv[0]);
	
}
//printf("client is running \n ");
sresult=msg_1(NULL,cl);
printf("client is running1 \n ");

printf("date is %s", *sresult);
printf("exit \n ");
}