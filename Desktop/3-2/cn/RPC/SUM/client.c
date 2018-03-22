
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<rpc/rpc.h>
#include "sum.h"


int main(int argc, char **argv){

printf("In clinet");
int c;
extern char *optarg;
extern int optind;
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
if (err || (optind < argc)) {
	fprintf(stderr, "usage:  %s [-h hostname]\n", argv[0]);
	exit(1);
}


CLIENT *cl;  /* rpc handle */
cl = clnt_create(server, SUM_PROG, SUM_VERS, "udp");

int i=0;
struct arrs A;
for( i=0;i<10;i++){
	A.arr1[i]=i;A.arr2[i]=i;
}
	
	//long *lresult; /* return from bin_date */
	//char **sresult; /* return from str_date */
if (argc != 1) {
	fprintf(stderr, "usage: %s\n", argv[0]);
	
}
/* call the procedure bin_date */
//lresult = bin_date_1(NULL,cl);
//printf("time on %s is %ld\n",server, *lresult);
/* convert the result to a date string */
//sresult =str_date_1(lresult,cl);
//printf("date is %s", *sresult);
struct arr *B;
B = add_1(&A,cl);
for(i=0;i<10;i++){
 printf("%ld",B->arr[i]);
}


}