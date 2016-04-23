#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

//求连续子数组的最大和
//输入一个整形数组，数组里有正数也有负数。求所有子数组的和的最大值；
//要求时间复杂度为o(n)

//思路：用一个变量maxSum保存当前最大和，变量curSum保存累加和；
//     当curSum为正时，则curSum继续累加；为负时，则抛弃前面的累加和，curSum=当前元素；
//	   若此时累加和curSum比maxSum大，则更新maxSum；

int FindGreatestSumOfSubArray(vector<int> array) {
	if(array.size()==0)
		return 0;
	int maxSum = array[0];	//最大和
	int curSum = array[0];	//当前连续和
	for(vector<int>::const_iterator it=array.begin()+1; it!=array.end(); ++it){
		if(curSum<=0)
			curSum = *it;
		else
			curSum += *it;
		if(curSum > maxSum)
			maxSum = curSum;
	}
	return maxSum;
}

/*
int main(){
	vector<int> array;
	int temp,k;
	while(1){
		cin.clear();  cin.sync();
		array.clear();
		cout<<"输入整数数组(有正有负数)："<<endl;
		while(cin>>temp){
			array.push_back(temp);
		}
		cout<<"连续子数组的最大和为:"<<"\t";
		cout<<FindGreatestSumOfSubArray(array)<<endl;
	}
	system("pause");
}
*/