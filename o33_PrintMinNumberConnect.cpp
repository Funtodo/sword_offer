#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//#include <stringstream>
#include <sstream>
using namespace std;

//�����������������ų���С����
//����һ�����������飬����������������ƴ�������ų�һ��������ӡ��ƴ�ӳ���������������С��һ����
//������ {3,32,321}==>321323

//˼·���Ƚ���������תΪ�ַ������飬Ȼ���������򣬽��ź��������Ԫ�ش��ӳ��ַ���������
//     �Ƚϱ�׼�����Ӻ�Ƚϣ�AB��BA���Ƚ��ַ�����С������ֱ�ӱȽ�(31,3=>313,but 38,3=>338)

bool compare_string(const string &str1,const string &str2){  //һ��Ҫ�� const��������ţ��Linux clang++�������±��벻ͨ��
	string strAB = str1+str2;								   //��������ж��壬��Ҫ�� static����̬������
	string strBA = str2+str1;
	return strAB<strBA;
}
string PrintMinNumber(vector<int> numbers) {
	string result;
	if(numbers.size()<=0)
		return result;

	//������������ת��Ϊ�ַ�������----
	vector<string> strNums;
	for(vector<int>::const_iterator it=numbers.begin();it!=numbers.end();++it){
		stringstream ss;
		ss<<*it;
		strNums.push_back(ss.str());
	}
	//����ֱ��ʹ�ÿ⺯��
	sort(strNums.begin(),strNums.end(),compare_string);

	for(vector<string>::const_iterator it=strNums.begin();it!=strNums.end();++it)
		result.append(*it);
	
	return result;
}

//----������ת��Ϊ�ַ���-----
//--1) c�ַ�����ʽ---
string num_to_str(int num){
	static const int maxNumLength = 10;
	char cStr[2*maxNumLength+1];	//c���ַ���
	sprintf(cStr, "%d", num);		//��������ƴ�ӳ��ַ���str1��sprintf(str1, "%d%d", num1, num2);
	return string(cStr);			//��c���ַ�����ʼ��һ������string�����ڷ��ؽ��
}
//--2) string��ʽ---
string num_to_str2(int num){
	stringstream ss;
	ss<<num;
	return ss.str();
}

/*
int main(){
	vector<int> numbers;
	int temp;

	cout<<"����һ��������������ת�ַ������ԣ�"<<endl;
	cin>>temp;
	cout<<num_to_str(temp)<<endl;
	cout<<num_to_str2(temp)<<endl;

	while(1){
		cin.clear();  cin.sync();
		numbers.clear();
		cout<<"�������������飺"<<endl;
		while(cin>>temp){
			numbers.push_back(temp);
		}
		cout<<"�����ųɵ���С����Ϊ:"<<"\t";
		cout<<PrintMinNumber(numbers)<<endl;
	}
	system("pause");
}
*/