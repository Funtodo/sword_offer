#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;

//����������һ�����������������������֮�⣬���������ֶ����������Ρ���д�����ҳ�������ֻ����һ�ε����֡�
//˼·�����һ����������ֻ����һ��ֻ����һ�ε�����(���඼��������)�������������������е�Ԫ�أ����õ��Ľ����ֻ����һ�ε����֣�
//     �����������������������Ԫ�أ����һ����Ϊ0�������������ĳһ����Ϊ0��λ�ɽ������Ϊ���飬ÿ��ǡ��ֻ����һ��ֻ����һ�ε����֣�
//     �������ÿ�飬�õ��ļ�Ϊ����ֻ����һ�ε����֣�

//���޵ķ�ʽ������ vector<int> &data,int &num1,int &num2
typedef vector<int>::const_iterator pIndex;
unsigned int FindFirstBitIs1(int num);
bool IsBit1(int num,unsigned int indexBit);
void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
	if(data.size()<2)
		return;

	int resultExclusiveOR = 0;
	for(pIndex it=data.begin();it!=data.end();++it)
		resultExclusiveOR ^= *it;

	unsigned int indexOf1 = FindFirstBitIs1(resultExclusiveOR);		//�ҵ�������е�һ����Ϊ1��λ
	//����ԭ���飬��Ԫ�ص�indexOf1λΪ1�������num1�� Ϊ0�������num2��
	//�൱����indexOf1λ��ԭ�����Ϊ���飬��ͬ��������Ϊһ�飬�����������÷ֱ�һ��ֻ����һ�ε���������ÿ��Ԫ���������õ��������Ǹó���һ�ε�����
	*num1 = *num2 = 0;
	for(pIndex it=data.begin();it!=data.end();++it){
		if(IsBit1(*it,indexOf1))			//�ж�indexOf1λ�Ƿ�Ϊ1
			*num1 ^= *it;
		else
			*num2 ^= *it;
	}
}

//������num�Ķ����Ʊ�ʾ���ҵ����ұ���1��λ
unsigned int FindFirstBitIs1(int num){
	unsigned int indexBit = 0;
	while( (num & 1) == 0 && ( indexBit<8*sizeof(int) ) ){		//8*sizeof(int)--int��Ӧ�Ķ�����λ��; 2)(num & 1) == 0һ��Ҫ�����ţ�== ������ &
		num = num>>1;		//����һλ
		++indexBit;
	}
	return indexBit;
}
//�ж�num�Ķ����Ʊ�ʾ�д��ұ������indexBitλ�ǲ���Ϊ1
bool IsBit1(int num,unsigned int indexBit){
	num = num>>indexBit;
	/*if( num & 1)	//ɵ����
		return true;
	return false;  */
	return num & 1;
}

/*
int main(){
	vector<int> numbers;
	int temp,num1,num2;

	while(1){
		cin.clear();  cin.sync();
		numbers.clear();
		cout<<"������������(������������֮�⣬���������ֶ�����������)��"<<endl;
		while(cin>>temp){
			numbers.push_back(temp);
		}
		cout<<"ֻ����һ�ε�������Ϊ:  ";
		FindNumsAppearOnce(numbers,&num1,&num2);	//���Ϊ���ã�FindNumsAppearOnce(numbers,num1,num2)
		cout<<num1<<"\t"<<num2<<endl<<endl;
	}
	system("pause");
}
*/
