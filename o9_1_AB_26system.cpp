#include"stdafx.h"
#include<iostream>
#include<string>
using namespace std;

//A,B,C,D~Z,AA,AB,AC~Êä³ö×Ö·û´®¶ÔÓ¦µÄĞòºÅ£¬´Ó1¿ªÊ¼±àºÅ
//ÀıÈç A=>1,AB=>28
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
	cout<<"ÊäÈë×ÖÄ¸±àºÅ£¬ÈçA£¬AB¡­¡­"<<endl;
	while(cin>>letters){
		cout<<letters<<" => "<<ToNumber_26system(letters)<<endl;
	}
	system("pause");
}
*/