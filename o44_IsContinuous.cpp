#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//问题描述：随机抽取几张牌，判断是否能组成顺子，，2~10，A-1,J~K-11~13,大小王-0，可以看成任意数字
int compare(const void *a,const void *b){
	return *(int*)b-*(int*)a;   
}
bool IsContinuous( vector<int> numbers ) {
	if(numbers.size()==0)
		return false;
	//sort(numbers.begin(),numbers.end());
	qsort(&numbers[0],numbers.size(),sizeof(int),compare);	//qsort (void*, size_t, size_t,int (*)(const void*, const void*));
	int countZero = 0;		//统计0的个数，即大小王个数
	int countGap = 0;		//统计数组中间隔数目（不连续，需要大小王补充的个数）
	for(int i=0;i<numbers.size() && numbers[i]==0;++i)
		++countZero;
	for(int i=countZero+1;i<numbers.size();++i){
		if(numbers[i]==numbers[i-1])		//有相等的不能组成顺子
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