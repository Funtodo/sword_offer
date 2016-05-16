#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//���������������ȡ�����ƣ��ж��Ƿ������˳�ӣ���2~10��A-1,J~K-11~13,��С��-0�����Կ�����������
int compare(const void *a,const void *b){
	return *(int*)b-*(int*)a;   
}
bool IsContinuous( vector<int> numbers ) {
	if(numbers.size()==0)
		return false;
	//sort(numbers.begin(),numbers.end());
	qsort(&numbers[0],numbers.size(),sizeof(int),compare);	//qsort (void*, size_t, size_t,int (*)(const void*, const void*));
	int countZero = 0;		//ͳ��0�ĸ���������С������
	int countGap = 0;		//ͳ�������м����Ŀ������������Ҫ��С������ĸ�����
	for(int i=0;i<numbers.size() && numbers[i]==0;++i)
		++countZero;
	for(int i=countZero+1;i<numbers.size();++i){
		if(numbers[i]==numbers[i-1])		//����ȵĲ������˳��
			return false;
		countGap += numbers[i]-numbers[i-1]-1;
	}
	/*if(countGap<=countZero)
		return true;
	return false;*/
	return (countGap<=countZero)?true:false;
}

/*
int main(){
	vector<int> numbers;
	numbers.push_back(0);
	numbers.push_back(1);
	numbers.push_back(3);
	numbers.push_back(6);
	numbers.push_back(4);
	numbers.push_back(5);
	cout<<IsContinuous(numbers)<<endl;
	system("pause");
}
*/