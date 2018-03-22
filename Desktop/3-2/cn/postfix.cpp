//postfix evalution using stack
// example code
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int cal(int a,int b,char ch){
	switch(ch){
		case '+':return a+b;
		case '-':return b-a;
		case '*':return a*b;
		case '/':return b/a;
	}
}
int main(){
	stack<int>st;
	cout<<"enter a postfix expression : ";
	string s;
	cin>>s;
	for(int i=0;i<s.length();i++){
		if(s[i]>='0'&&s[i]<='9'){
			st.push(s[i]-'0');
		}
		else {
			int n1=st.top();
			st.pop();
			int n2=st.top();
			st.pop();
			char ch=s[i];
			int n3=cal(n1,n2,ch);
			st.push(n3);
		}
	}
	int ans=st.top();
	cout<<ans<<endl;
	return 0;
}