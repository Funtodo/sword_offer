#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

//111问题描述：翻转句子中单词的顺序，但单词内字符的顺序不变
//思路：先翻转句子中所有的字符，再翻转每个单词中字符的顺序
extern void swap(int &num1,int &num2);
void reverse(string &str,int start,int end);

string ReverseSentence(string str) {
	int len = str.length();
	if(len==0) return str;
	reverse(str,0,len-1);			//翻转句子中的所有字符
	int curWordStart = 0,i=0;
	for(;i<=len;++i){				//翻转每个单词
		if(i==len || str[i]==' '){			//遇到空格或句子结束，认为前面找到了一个单词
			reverse(str,curWordStart,i-1);
			curWordStart = i+1;				//下一个单词的起点
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

//222问题描述：实现对字符串进行循环左移操作，例如 abcde，左旋3位为 deabc
//思路：左旋n位，则先分别翻转前n位段和后半段，再整体翻转，例如abcde=>cbaed=>deabc
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
	cout<<"输入一个句子："<<endl;
	while(getline(cin,str)){
		cout<<"翻转单词顺序后的结果为："<<endl;
		cout<<ReverseSentence(str)<<endl;
		
		cout<<"输入左旋长度：";
		int n;
		cin>>n;
		cout<<"左旋后的结果为："<<endl;
		cout<<LeftRotateString(str,n)<<endl<<endl;

		cout<<"输入下一个句子："<<endl;
		cin.clear();  cin.sync();
	}
	system("pause");
}
*/