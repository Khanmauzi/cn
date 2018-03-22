#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

double i = 0.000;

int main(){
	while(1){
		fork();

		cout<<"forking is chutiyapa "<<endl;
		fork();
		while(1)
		{
			fork();
			i = i + 0.0001;
			cout << i << endl;
		}
	}
}