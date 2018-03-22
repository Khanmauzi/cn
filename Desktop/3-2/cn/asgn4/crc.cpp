// cyclic redundency check

/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/


#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace std;


string key="1101";
string data;

string module(string data, string key){
	int n=data.length();
	int k=key.length();
	int divisor[k];
	int divident[k];
	string qou="";
	string rem1="";
	for(int i=0;i<k;i++){
		char ch[1];
	    ch[0]=key[i];
		divisor[i]=atoi(ch);
	}
	int i=0;
	for(int j=0;j<k;j++){
		char ch[1];
	    ch[0]=data[i++];
		divident[j]=atoi(ch);
	}
	while(1){
		//cout<<"i : "<<i<<endl;
		for(int j=0;j<k;j++){
			divident[j]=divident[j]^divisor[j];
		}
		qou=qou+"1";
		if(divident[1]==0){
			for(int m=0;m<k-2;m++){
				divident[m]=divident[m+2];
			}
			char ch[1];
			ch[0]=data[i++];
			divident[k-2]=atoi(ch);
			ch[0]=data[i++];
			divident[k-1]=atoi(ch);
			qou=qou+"0";
		}
		else {
			for(int m=0;m<k-1;m++){
				divident[m]=divident[m+1];
			}
			char ch[1];
			ch[0]=data[i++];
			divident[k-1]=atoi(ch);
		}
		if(i==n){
			break;
		}
	}
		for(int j=0;j<k;j++){
			divident[j]=divident[j]^divisor[j];
		}
		qou=qou+"1";
		for(int i=1;i<k;i++){
			char ch=(char)divident[i]+'0';
			rem1=rem1+ch;
		}

	cout<<"qoutient : "<<qou<<endl;
	return rem1;
}

int main(){
	cout<<"key is "<<key<<endl;
	cout<<"enter the data to be sent (binary form) : ";
	cin>>data;
	string data1=data;
	int k=key.length();
	for(int i=0;i<k-1;i++){
		data1=data1+"0";
	}
	string rem=module(data1,key);
	cout<<"remainder is : "<<rem<<endl;
	data=data+rem;
	
	cout<<"data sent is : "<<data<<endl;
	cout<<"performing checking if data is correct ....."<<endl;
	rem=module(data,key);
	cout<<"remainder : "<<rem<<endl;
	for(int i=0;i<k-1;i++){
		if(rem[i]=='1'){
			cout<<"not correct ";
			return 0;
		}
	}
	cout<<"correct ";
	return 0;
}