// hamming code for setting the reducatant code 

/* 
	NAME : MOJAMMIL
	CLSS :BTECH
	157238 CSE 2015-19
*/
	#include <iostream>
	#include <math.h>
	#include <stdlib.h>
	#include <string>

	using namespace std;

	int main(){
		string s;
		cout<<"enter the data(binary) : ";
		cin>>s;
		int m=s.length();					//number of message bit
		int i=0;
		int r;								//number of reductant bit
		while(1){
			int k=pow(2,i);
			int diff=k-(m+i+1);
			if(diff>=0){
				r=i;
				break;
			}
			i++;
		}
		int n=m+r;						//total length of data
		int data[n];
		int j=0;
		 i=0;
		 int temp=0;
		while(i<n){						//while not total 
			//cout<<"i : "<<i<<endl;
			int k=pow(2,temp++)-1;		//redundatn position
			data[i++]=0;				//setting redundant bit to 0;
			int l=pow(2,temp)-1;		//max lenght upto which we have to add the data
			while(i<l){
				char ch[1];
				ch[0]=s[j++];
				data[i++]=atoi(ch);		//adding bit data
			}
		}
		cout<<"after adding redundant bit : ";
		for(int i=0;i<n;i++){			//printing the data
			cout<<data[i];
		}
		cout<<endl;
		// now set the reductant bit;
		temp=0;
		i=0;
		while(1){
			int k=pow(2,temp++);			//finding redundant position
			if(k>=n){
				break;
			}
			int j=k-1;						//starting index to check for redundant bit
			int cnt=0;
			//cout<<"k :"<<k<<endl;
			int temp2=0;
			while(j<n){
				temp2=0;
				for(;temp2<k;j++,temp2++){	//every time loop runs exactly k times+++++
					//cout<<"j : "<<j+1<<endl;
					if(data[j]==1){
						cnt++;
					}
					
				}
				j=j+k;
			}
		//	cout<<endl;
			if(cnt%2==1){
				//cout<<" k setting "<<k-1<<endl;
				data[k-1]=1;
			}

		}
		cout<<"after settinng reductant data : ";
		for(int i=0;i<n;i++){
			cout<<data[i];
		}
		cout<<endl;   

		//error correction coding
		int bit_pos=0;
		cout<<"enter the positon of bit which u want to change : ";
		cin>>bit_pos;
		if(data[bit_pos]==0){
			data[bit_pos]=1;
		}
		else{
			data[bit_pos-1]=0;
		}
		cout<<"after changing the bit : ";
		for(int i=0;i<n;i++){
			cout<<data[i];
		}
		cout<<endl; 

		// now checking the position of error bit through programmng

		temp=0;
		i=0;
		int res=0;
		while(1){
			int k=pow(2,temp++);
			if(k>=n){
				break;
			}
			int j=k-1;
			int temp2=0;
			int cnt=0;

			while(j<n){
				temp2=0;
				for(;temp2<k;temp2++,j++){
					if(data[j]==1){
						cnt=cnt^1;
					}
				}
				j=j+k;
			}
			if(cnt==1){
				res=res+k;
			}
		}
		cout<<"error position is : "<<res<<endl;

		if(data[res-1]==0){
			data[res-1]=1;
		}
		else{
			data[res-1]=0;
		}
		cout<<"after correction of data :  ";
		for(int i=0;i<n;i++){
			cout<<data[i];
		}
		cout<<endl; 
		return 0;
	}