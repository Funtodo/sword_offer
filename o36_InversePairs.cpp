#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;

int InversePairsCore(vector<int> &data,vector<int> &copy,int pLeft,int pRight);
int InversePairs(vector<int> data) {
	if(data.size()==0)
		return 0;
	vector<int> copy;
	for(vector<int>::const_iterator it=data.begin();it!=data.end();++it)	//一次“申请”空间，比在merge里每次申请空间高效
		copy.push_back(*it);
	return InversePairsCore(data,copy,0,data.size()-1);			//采用下标更方便，因迭代器不能以第一个元素前一个为哨兵，而程序中是倒序遍历，会使程序变复杂
	//return InversePairsCore(data.begin(),data.end()-1,copy.begin(),copy.end()-1);			//逆序对递归计算，用迭代器，可直接传入vector的迭代器范围
}

int InversePairsCore(vector<int> &data,vector<int> &copy,int iLeft,int iRight){
	if(iLeft==iRight){
		copy[iLeft] = data[iLeft];
		return 0;
	}
	int halfLen = (iRight-iLeft)/2;				//半长长度
	int countLeft = InversePairsCore(copy,data,iLeft,iLeft+halfLen);				//copy 和 data 互为辅助空间
	int countRight = InversePairsCore(copy,data,iLeft+halfLen+1,iRight);
	//Merge 部分，merge同时计算逆序对(合并到copy，即结束后copy该段是排序好的)
	int countMerge=0;
	int iData1 = iLeft+halfLen;			//前半段最后一个元素的下标
	int iData2 = iRight;				//后半段最后一个元素的下标
	int iCopy = iRight;				    //copy段最后一个位置的下标
	while(iData1>=iLeft && iData2>=iLeft+halfLen+1){
		if(data[iData1]>data[iData2]){					//构成逆序
			countMerge += iData2-(iLeft+halfLen);		//后半段剩下的元素都比*pData1小，则逆序对为pData2-dataMid
			copy[iCopy--] = data[iData1--];
		}else
			copy[iCopy--] = data[iData2--];
	}
	while(iData1>=iLeft)					//前半段没排完
		copy[iCopy--] = data[iData1--];
	while(iData2>=iLeft+halfLen+1)			//后半段没排完(两个while只可能一个成立)
		copy[iCopy--] = data[iData2--];
	//不必再从copy复制回data，因为最终目的只是计算逆序对，不需要对原数组排序，可以让copy和data互为辅助空间
	return countLeft+countRight+countMerge;
}

int main(){
	vector<int> numbers;
	int temp;

	while(1){
		cin.clear();  cin.sync();
		numbers.clear();
		cout<<"输入整数数组："<<endl;
		while(cin>>temp){
			numbers.push_back(temp);
		}
		cout<<"逆序对个数:"<<"\t";
		cout<<InversePairs(numbers)<<endl;
	}
	system("pause");
}