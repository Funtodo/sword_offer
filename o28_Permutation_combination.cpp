#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

//===============����================================
//��������������һ���ַ���,���ֵ����ӡ�����ַ������ַ����������С�
//		  �������ظ��ַ���
//˼·���ݹ鷽ʽ�������õ�һλ����һλ��Ϊstr��ÿһ�����ظ����ַ���ͨ������ʹ��һλΪ��ͬ�ַ�����Ȼ������strʣ�µ�Ԫ�أ�
//	   ֱ���������һλ����õ�һ�����У�
extern void swap(int &num1,int &num2);
void Permutation(string str,vector<string> &permuts,int curIndex);

vector<string> Permutation(string str) {
	vector<string> permuts;
	if(str.length()==0)
		return permuts;

	//--���ַ��������ַ��ֵ�������---
	sort(str.begin(),str.end());

	Permutation(str,permuts,0);
	return permuts;
}
void Permutation(string str,vector<string> &permuts,int curIndex){
	if( curIndex == str.length()-1 ){		//�̶������һ���ַ������õ�һ������
		permuts.push_back(str);
		return;
	}
	Permutation(str,permuts,curIndex+1);
	for(int i=curIndex+1;i<str.length();++i){
		if(str[curIndex]!=str[i]){				//��ȣ����ý������Ը�λ����
			swap(str[curIndex],str[i]);
			Permutation(str,permuts,curIndex+1);
			//swap(str[curIndex],str[i]);		//���Permutation��str�����ô��ݣ���˴���Ҫ�ٴν����ָ�ԭ���������������ܵõ��ֵ���
		}
	}
}

//================���==========================
//��������������һ���ַ���,���ֵ����ӡ�����ַ������ַ���������ϡ�
//		  �������ظ��ַ���
//        ���磺abc=��a,b,c,ab,ac,bc,abc
vector<string> combination(string str){
	vector<string> combins;
	if(str.length()==0)
		return combins;

	//--���ַ��������ַ��ֵ�������---
	sort(str.begin(),str.end());

	for(int curLen=1;curLen<=str.length();++curLen){	//��ͬ��ϳ���
		//for(int curIndex=0;curIndex<=str.length()-curLen;++curIndex)	//��Ͽ�ʼ���ַ��±�
		//	combination(str,combins,curLen,curIndex);
		combination(str,combins,curLen,0);
	}
}
//���룺ԭ�ַ���str����ǰ��ϵĳ���curLen����ǰ�����str�е���ʼλ��
//˼·���ݹ鷽ʽ����ѡ��һ�����������ں�����ִ���ѡ�������ַ�
void combination(string str,vector<string> &combins,int curLen,int curIndex){
	if(curIndex>=str.length())
		cout<<"�±����"<<endl;

	if(curLen==1){		//������һ�����
		string tmp(str.begin()+curIndex-curLen+1,str.begin()+curIndex+1);
		combins.push_back(tmp);
	}
	for(int i=curIndex;i<=str.length()-curLen;++i)
		combination(str,combins,curLen,i);				//�����Ե�iλ��Ϊ��ͷ���������

	for(int i=curIndex;i<=str.length()-curLen;++i){
		//swap(str[curIndex],str[i]);
		combination(str,combins,curLen,i);				//��iλ�����������
		combination(str,combins,curLen-1,i+1);			//��iλ���������
	}
}
void main(){
	string str;
	cout<<"����һ���ַ������������ظ��ַ�����"<<endl;
	while(cin>>str){
		cout<<"���н����"<<endl;
		vector<string> result = Permutation(str);
		for(vector<string>::const_iterator it=result.begin();it!=result.end();++it)
			cout<<(*it)<<"\t";
		cout<<endl;

		cout<<"������һ���ַ�����"<<endl;
		cin.clear();  cin.sync();
	}
	system("pause");
}