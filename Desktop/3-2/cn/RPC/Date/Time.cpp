#include<bits/stdc++.h>
#include <stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/time.h>
#include<time.h>
using namespace std;
long bin_date(void);
char *str_date(long bintime); 

main(int argc, char **argv) {
	long lresult; /* return from bin_date */
	char *sresult; /* return from str_date */
if (argc != 1) {
	fprintf(stderr, "usage: %s\n", argv[0]);
	
}
/* call the procedure bin_date */
lresult = bin_date();
printf("time is %ld\n", lresult);
/* convert the result to a date string */
sresult =str_date(lresult);
printf("date is %s", sresult);

} 

/* bin_date returns the system time in binary format */
long bin_date(void) {
long timeval;
//long time();  /* Unix time function; returns time */
timeval = time((long *)0);
return timeval;
}
/* str_date converts a binary time into a date string */
char *str_date(long bintime) {
char *ptr;
//char *ctime();  /* Unix library function that does the work */
ptr = ctime(&bintime);
return ptr;
}