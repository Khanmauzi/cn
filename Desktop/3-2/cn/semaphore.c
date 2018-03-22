/*
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/

	//#include <iostream>
	#include <string.h>	
	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/types.h>
	#include <pthread.h>
	#define  null NULL
	//using namespace std;
	int x=0;
	int y=0;
	int s1=0;					//semaphore associated with x;
	int s2=1;					//semaphore associated with y
	
	void wait1(int *x){
		while(*x<=0);
		*x=*x-1;
	}

	void signal1(int *x){
		*x=*x+1;
	}

	void * p1(void *argv){
		while(x<1000000&&y<1000000){
				
			wait1(&s2);
			int temp=y+1;
			x=x+temp;
			printf("in process p1\n");
			printf("the value of x is : %d\n",x );
			printf("the value of y is : %d\n",y );
			signal1(&s1);
			
		}
		//printf("ok bye\n");
		return null;
	}

	void *p2(void *argv){
		while(x<1000000&&y<1000000){
			wait1(&s1);
			int temp=x+1;
			y=y+temp;
			printf("in process p2\n");
			printf("the value of x is : %d\n",x );
			printf("the value of y is : %d\n",y );
			signal1(&s2);
		}
		//printf("ok \n");
		return null;
	}
	int main(){
		pthread_t t1,t2;
		pthread_create(&t1,null,p1,null);
		pthread_create(&t2,null,p2,null);
		pthread_join(t1,null);
		pthread_join(t2,null);
		return 0;
	}
