#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

//111������������ת�����е��ʵ�˳�򣬵��������ַ���˳�򲻱�
//˼·���ȷ�ת���������е��ַ����ٷ�תÿ���������ַ���˳��
extern void swap(int &num1,int &num2);
void reverse(string &str,int start,int end);

string ReverseSentence(string str) {
	int len = str.length();
	if(len==0) return str;
	reverse(str,0,len-1);			//��ת�����е������ַ�
	int curWordStart = 0,i=0;
	for(;i<=len;++i){				//��תÿ������
		if(i==len || str[i]==' '){			//�����ո����ӽ�������Ϊǰ���ҵ���һ������
			reverse(str,curWordStart,i-1);
			curWordStart = i+1;				//��һ�����ʵ����
		}
	}
	return str;
}
void reverse(string &str,int start,int end){
	while(start<end){
		swap(str[start],str[end]);
		++start,--end;
	}
}
/*void swap(int &num1,int &num2){
	int temp = num1;
	num1 = num2;
	num2 = temp;
}*/

//222����������ʵ�ֶ��ַ�������ѭ�����Ʋ��������� abcde������3λΪ deabc
//˼·������nλ�����ȷֱ�תǰnλ�κͺ��Σ������巭ת������abcde=>cbaed=>deabc
bool flagIsValid = true;
string LeftRotateString(string str, int n) {
	int len = str.length();
	if(len==0 || len<n || n<0){
		flagIsValid = false;
		return str;
	}
	reverse(str,0,n-1);
	reverse(str,n,len-1);
	reverse(str,0,len-1);
	return str;
}

/*
int main(){
	string str;
	cout<<"����һ�����ӣ�"<<endl;
	while(getline(cin,str)){
		cout<<"��ת����˳���Ľ��Ϊ��"<<endl;
		cout<<ReverseSentence(str)<<endl;
		
		cout<<"�����������ȣ�";
		int n;
		cin>>n;
		cout<<"������Ľ��Ϊ��"<<endl;
		cout<<LeftRotateString(str,n)<<endl<<endl;

		cout<<"������һ�����ӣ�"<<endl;
		cin.clear();  cin.sync();
	}
	system("pause");
}
*/