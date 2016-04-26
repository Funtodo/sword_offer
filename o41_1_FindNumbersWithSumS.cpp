#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;

//问题描述：输入一个递增排序的数组和一个数字S，在数组中查找两个数，使得他们的和正好是S；
//       如果有多对数字的和等于S，输出两个数的乘积最小的，且两个数中，小的先输出


//思路：数组是递增排序的，因此只需要维持收尾两个指针，。。。
//    这样第一次找出的两个数，一定是和为s中乘积最小的；

bool FindNumbersWithSum(vector<int> &array,int sum,int &num1,int &num2) {
	int len = array.size();
	if(len<2 || sum<array[0])
		return false;

	int iLeft = 0;
	int iRight = len-1;
	while(iLeft<iRight){
		long long curSum = array[iLeft] + array[iRight];
		if( curSum == sum ){
			num1 = array[iLeft];
			num2 = array[iRight];
			return true;
		}
		else if( curSum > sum )
			--iRight;
		else //( curSum < sum)
			++iLeft;
	}
	return false;
}

//牛客-函数头要求，，结果以vector返回
vector<int>  FindNumbersWithSum2(vector<int> &array,int sum) {
	vector<int> result;
	int len = array.size();
	if(len<2 || sum<array[0])
		return result;

	int iLeft = 0;
	int iRight = len-1;
	while(iLeft<iRight){
		long long curSum = array[iLeft] + array[iRight];
		if( curSum == sum ){
			result.push_back(array[iLeft]);
			result.push_back(array[iRight]);
			break;
		}
		else if( curSum > sum )
			--iRight;
		else //( curSum < sum)
			++iLeft;
	}
	return result;
}

/*
int main(){
	vector<int> numbers;
	int temp,sum,num1,num2;

	while(1){
		cin.clear();  cin.sync();
		numbers.clear();
		cout<<"输入递增排序的数组:  "<<endl;
		while(cin>>temp){
			numbers.push_back(temp);
		}
		cout<<"输入一个数字S:  ";
		cin.clear();  cin.sync();
		cin>>sum;

		//结果通过 函数参数 传地址 得到，，另外函数返回bool，标志是否存在结果
		if(FindNumbersWithSum(numbers,sum,num1,num2))
			cout<<"和为 "<<sum<<" 的两个数为:  "<<num1<<"\t"<<num2<<endl<<endl;
		else
			cout<<"不存在和为 "<<sum<<" 的两个数"<<endl<<endl;

		//结果通过 返回vector 得到，，可通过结果vector的size判断是否存在结果
		vector<int> result = FindNumbersWithSum2(numbers,sum);
		if(result.size()==2)
			cout<<"和为 "<<sum<<" 的两个数为:  "<<result[0]<<"\t"<<result[1]<<endl<<endl;
		else
			cout<<"不存在和为 "<<sum<<" 的两个数"<<endl<<endl;
	}
	system("pause");
}
*/
