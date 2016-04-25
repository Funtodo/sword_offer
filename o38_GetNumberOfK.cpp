#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

//问题描述：统计数字在排序数组中出现的次数
//思路：二分查找思路，分别二分查找到找到第一个和最后一个出现的坐标，然后计算个数

//此处采用递归形式，输入：vector，要查找的数字，当前查找范围的起止下标
int GetFirstK(vector<int> &data,int k,int iLeft,int iRight){
	//if(left>right)		//-!!--注意：left和right是C++的保留关键字，用于格式化输出（左对齐，右对齐），，此处永远为true！
	if(iLeft>iRight)		//没有找到，返回 -1 
		return -1;
	

	int iFirstK = 0;
	int iMid = (iLeft+iRight)/2;

	if(k==data[iMid]){
		if(iMid>0 && data[iMid-1]!=k || iMid==0)		//找到了第一个k的两种条件
			iFirstK = iMid;
		else					//(iMid>0 && data[iMid-1]==k)
			iFirstK = GetFirstK(data,k,iLeft,iMid-1);
	}
	else if(k>data[iMid])
		iFirstK = GetFirstK(data,k,iMid+1,iRight);
	else			//(k<data[iMid])
		iFirstK = GetFirstK(data,k,iLeft,iMid-1);	

	return iFirstK;
}
int GetLastK(vector<int> &data,int k,int iLeft,int iRight){
	if(iLeft>iRight)		//没有找到，返回 -1 
		return -1;

	int iLastK = 0;
	int iMid = (iLeft+iRight)/2;

	if(k==data[iMid]){
		if(iMid<iRight && data[iMid+1]!=k || iMid==iRight)	//找到了最后一个k的两种条件
			iLastK = iMid;
		else					//(iMid<iRight && data[iMid+1]==k)
			iLastK = GetLastK(data,k,iMid+1,iRight);
	}
	else if(k>data[iMid])
		iLastK = GetLastK(data,k,iMid+1,iRight);
	else			//(k<data[iMid])
		iLastK = GetLastK(data,k,iLeft,iMid-1);	

	return iLastK;
}

int GetNumberOfK(vector<int> data ,int k) {
	if(data.size()==0)
		return 0;
	int firstIndex = GetFirstK(data,k,0,data.size()-1);		//查找k的第一个出现下标，递归二分查找，用下标形式
	int lastIndex = GetLastK(data,k,0,data.size()-1);		//查找k的最后一个出现的下标
	if(firstIndex>-1 && lastIndex>-1)						//不存在时，GetLastK，GetFirstK返回-1
		return lastIndex - firstIndex + 1;
	return 0;
}

/*
int main(){
	vector<int> numbers;
	int temp;

	while(1){
		cin.clear();  cin.sync();
		numbers.clear();
		cout<<"输入排好序的整数数组："<<endl;
		while(cin>>temp){
			numbers.push_back(temp);
		}
		cin.clear();  cin.sync();
		cout<<"输入查找的数字：";
		cin>>temp;
		cout<<temp;
		cout<<" 出现的次数为:  ";
		cout<<GetNumberOfK(numbers,temp)<<endl<<endl;
	}
	system("pause");
}
*/