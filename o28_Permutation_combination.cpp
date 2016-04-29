#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

//===============排列================================
//问题描述：输入一个字符串,按字典序打印出该字符串中字符的所有排列。
//		  可能有重复字符；
//思路：递归方式，先设置第一位（第一位可为str里每一个不重复的字符，通过交换使第一位为不同字符），然后设置str剩下的元素，
//	   直到设置最后一位，则得到一个排列；
extern void swap(int &num1,int &num2);
void Permutation(string str,vector<string> &permuts,int curIndex);

vector<string> Permutation(string str) {
	vector<string> permuts;
	if(str.length()==0)
		return permuts;

	//--对字符串按照字符字典序排序---
	sort(str.begin(),str.end());

	Permutation(str,permuts,0);
	return permuts;
}
void Permutation(string str,vector<string> &permuts,int curIndex){
	if( curIndex == str.length()-1 ){		//固定到最后一个字符，即得到一个排列
		permuts.push_back(str);
		return;
	}
	Permutation(str,permuts,curIndex+1);
	for(int i=curIndex+1;i<str.length();++i){
		if(str[curIndex]!=str[i]){				//相等，则不用交换并以该位排列
			swap(str[curIndex],str[i]);
			Permutation(str,permuts,curIndex+1);
			//swap(str[curIndex],str[i]);		//如果Permutation的str是引用传递，则此处需要再次交换恢复原样（但这样并不能得到字典序）
		}
	}
}

//================组合==========================
//问题描述：输入一个字符串,按字典序打印出该字符串中字符的所有组合。
//		  可能有重复字符；
//        例如：abc=》a,b,c,ab,ac,bc,abc
vector<string> combination(string str){
	vector<string> combins;
	if(str.length()==0)
		return combins;

	//--对字符串按照字符字典序排序---
	sort(str.begin(),str.end());

	for(int curLen=1;curLen<=str.length();++curLen){	//不同组合长度
		//for(int curIndex=0;curIndex<=str.length()-curLen;++curIndex)	//组合开始的字符下标
		//	combination(str,combins,curLen,curIndex);
		combination(str,combins,curLen,0);
	}
}
//输入：原字符串str，当前组合的长度curLen，当前组合在str中的起始位置
//思路：递归方式，先选第一个，再依次在后面的字串中选择其他字符
void combination(string str,vector<string> &combins,int curLen,int curIndex){
	if(curIndex>=str.length())
		cout<<"下标出错"<<endl;

	if(curLen==1){		//设置完一个组合
		string tmp(str.begin()+curIndex-curLen+1,str.begin()+curIndex+1);
		combins.push_back(tmp);
	}
	for(int i=curIndex;i<=str.length()-curLen;++i)
		combination(str,combins,curLen,i);				//依次以第i位作为开头，设置组合

	for(int i=curIndex;i<=str.length()-curLen;++i){
		//swap(str[curIndex],str[i]);
		combination(str,combins,curLen,i);				//第i位不放入组合中
		combination(str,combins,curLen-1,i+1);			//第i位放入组合中
	}
}
void main(){
	string str;
	cout<<"输入一个字符串（允许有重复字符）："<<endl;
	while(cin>>str){
		cout<<"排列结果："<<endl;
		vector<string> result = Permutation(str);
		for(vector<string>::const_iterator it=result.begin();it!=result.end();++it)
			cout<<(*it)<<"\t";
		cout<<endl;

		cout<<"输入下一个字符串："<<endl;
		cin.clear();  cin.sync();
	}
	system("pause");
}