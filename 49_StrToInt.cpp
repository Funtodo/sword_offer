#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

//问题描述：将字符串转换为整数，即实现c语言函数库的atoi
//【关键点】：考虑全面：null，""空字符，正负号、无效字符串、【溢出】，

enum Status {kInvalid = 0,kValid};
Status g_nStatus = kValid;			//设置全局变量，标识输入是否合法，有效为1

int StrToIntCore(string &str,int indexStr,bool isMinus);
int StrToInt(string &str) {
	/*if(str==NULL){			//不需要，，用char*时才需要
		g_nStatus = kInvalid;
		return 0;
	}*/
	if(str.length()==0){		//空字符串
		g_nStatus = kInvalid;
		return 0;
	}
	bool isMinus = false;			//是否为负数
	int indexStr = 0;
	if(str[0]=='+'){
		++indexStr;
	}else if(str[0]=='-'){
		isMinus = true;
		++indexStr;
	}
	if(indexStr==str.length()){			//只有一个符号时
		g_nStatus = kInvalid;
		return 0;
	}else
		return StrToIntCore(str,indexStr,isMinus);
}
int StrToIntCore(string &str,int indexStr,bool isMinus){
	long long num = 0;			//采用long,long形式，整形溢出时抛出异常，，即此程序要自己处理溢出情况
	int sign = isMinus?-1:1;
	//while(indexStr<str.length()){
	for(;indexStr<str.length();++indexStr){
		if(str[indexStr]>'9' || str[indexStr]<'0')			//存在非数字字符
			break;

		num = num*10 + (str[indexStr]-'0')*sign;
		//if(num>0x7FFFFFFF || num<0x80000000)		//错误，，num<0x8000000为ture（解释为无符号数了）
		if(num>0x7FFFFFFF || num<(signed int)0x80000000)	//溢出，，0x7FFFFFFF-最大正整数,0x8000000-最小负整数
			break;
	}
	if(indexStr<str.length()){
		g_nStatus = kInvalid;
		return 0;
	}
	g_nStatus = kValid;
	return int(num);
}
/*
int main(){
	string str;
	//int result = StrToInt(NULL);	//测试NULL作为输入---如果采用的char*，c语言格式字符串，才需要测试null
	while(1){
		int result = StrToInt(str);		//测试空字符串
		if(g_nStatus)
			//printf("%s==>%d\n",str.c_str(),result);	//printf("%s")只能接受c型字符串
			cout<<str<<"==>"<<result<<endl;
		else
			printf("无效输入\n");
		cin>>str;
	}
	return 0;
}
*/