#include"stdafx.h"
#include<iostream>
#include<string>
using namespace std;

//A,B,C,D~Z,AA,AB,AC~����ַ�����Ӧ����ţ���1��ʼ���
//���� A=>1,AB=>28
int ToNumber_26system(string letters){
	if(letters.empty())
		return 0;
	int number = 0;
	for(string::const_iterator it = letters.begin(); it != letters.end(); ++it)
	{
		number = number * 26 + (*it - 'A' + 1);
	}
	return number;
}

/*
int main(){
	string letters;
	cout<<"������ĸ��ţ���A��AB����"<<endl;
	while(cin>>letters){
		cout<<letters<<" => "<<ToNumber_26system(letters)<<endl;
	}
	system("pause");
}
*/