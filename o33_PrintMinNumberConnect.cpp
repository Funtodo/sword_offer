#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//#include <stringstream>
#include <sstream>
using namespace std;

//问题描述：把数组排成最小的数
//输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个；
//如输入 {3,32,321}==>321323

//思路：先将整数数组转为字符串数组，然后将数组排序，将排好序的数组元素串接成字符串即所求；
//     比较标准：串接后比较，AB，BA，比较字符串大小，不能直接比较(31,3=>313,but 38,3=>338)

bool compare_string(const string &str1,const string &str2){  //一定要加 const？不加在牛客Linux clang++编译器下编译不通过
	string strAB = str1+str2;								   //如果在类中定义，还要加 static（静态函数）
	string strBA = str2+str1;
	return strAB<strBA;
}
string PrintMinNumber(vector<int> numbers) {
	string result;
	if(numbers.size()<=0)
		return result;

	//将正整数数组转换为字符串数组----
	vector<string> strNums;
	for(vector<int>::const_iterator it=numbers.begin();it!=numbers.end();++it){
		stringstream ss;
		ss<<*it;
		strNums.push_back(ss.str());
	}
	//排序，直接使用库函数
	sort(strNums.begin(),strNums.end(),compare_string);

	for(vector<string>::const_iterator it=strNums.begin();it!=strNums.end();++it)
		result.append(*it);
	
	return result;
}

//----将整数转换为字符串-----
//--1) c字符串方式---
string num_to_str(int num){
	static const int maxNumLength = 10;
	char cStr[2*maxNumLength+1];	//c型字符串
	sprintf(cStr, "%d", num);		//两个数字拼接成字符串str1：sprintf(str1, "%d%d", num1, num2);
	return string(cStr);			//用c型字符串初始化一个匿名string，用于返回结果
}
//--2) string方式---
string num_to_str2(int num){
	stringstream ss;
	ss<<num;
	return ss.str();
}

/*
int main(){
	vector<int> numbers;
	int temp;

	cout<<"输入一个正整数（整数转字符串测试）"<<endl;
	cin>>temp;
	cout<<num_to_str(temp)<<endl;
	cout<<num_to_str2(temp)<<endl;

	while(1){
		cin.clear();  cin.sync();
		numbers.clear();
		cout<<"输入正整数数组："<<endl;
		while(cin>>temp){
			numbers.push_back(temp);
		}
		cout<<"数组排成的最小的数为:"<<"\t";
		cout<<PrintMinNumber(numbers)<<endl;
	}
	system("pause");
}
*/