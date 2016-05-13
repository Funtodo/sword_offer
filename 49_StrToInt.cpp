#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

//�������������ַ���ת��Ϊ��������ʵ��c���Ժ������atoi
//���ؼ��㡿������ȫ�棺null��""���ַ��������š���Ч�ַ��������������

enum Status {kInvalid = 0,kValid};
Status g_nStatus = kValid;			//����ȫ�ֱ�������ʶ�����Ƿ�Ϸ�����ЧΪ1

int StrToIntCore(string &str,int indexStr,bool isMinus);
int StrToInt(string &str) {
	/*if(str==NULL){			//����Ҫ������char*ʱ����Ҫ
		g_nStatus = kInvalid;
		return 0;
	}*/
	if(str.length()==0){		//���ַ���
		g_nStatus = kInvalid;
		return 0;
	}
	bool isMinus = false;			//�Ƿ�Ϊ����
	int indexStr = 0;
	if(str[0]=='+'){
		++indexStr;
	}else if(str[0]=='-'){
		isMinus = true;
		++indexStr;
	}
	if(indexStr==str.length()){			//ֻ��һ������ʱ
		g_nStatus = kInvalid;
		return 0;
	}else
		return StrToIntCore(str,indexStr,isMinus);
}
int StrToIntCore(string &str,int indexStr,bool isMinus){
	long long num = 0;			//����long,long��ʽ���������ʱ�׳��쳣�������˳���Ҫ�Լ�����������
	int sign = isMinus?-1:1;
	//while(indexStr<str.length()){
	for(;indexStr<str.length();++indexStr){
		if(str[indexStr]>'9' || str[indexStr]<'0')			//���ڷ������ַ�
			break;

		num = num*10 + (str[indexStr]-'0')*sign;
		//if(num>0x7FFFFFFF || num<0x80000000)		//���󣬣�num<0x8000000Ϊture������Ϊ�޷������ˣ�
		if(num>0x7FFFFFFF || num<(signed int)0x80000000)	//�������0x7FFFFFFF-���������,0x8000000-��С������
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
	//int result = StrToInt(NULL);	//����NULL��Ϊ����---������õ�char*��c���Ը�ʽ�ַ���������Ҫ����null
	while(1){
		int result = StrToInt(str);		//���Կ��ַ���
		if(g_nStatus)
			//printf("%s==>%d\n",str.c_str(),result);	//printf("%s")ֻ�ܽ���c���ַ���
			cout<<str<<"==>"<<result<<endl;
		else
			printf("��Ч����\n");
		cin>>str;
	}
	return 0;
}
*/