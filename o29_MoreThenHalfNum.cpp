#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

//问题描述：求数组中出现次数超过一半的元素

//---------思路1----------------------
//如果将数组排序，则n/2位置的元素一定是出现次数超过半数的数字，则问题可转化为 求第n/2大的元素
//--采用快排的partition思想，二分缩小范围，直到选中的基准元素最后位置在n/2位置为止
//=时间复杂度: O(n)
typedef vector<int>::iterator pIndex;
pIndex partition(vector<int> &numbers,pIndex pLeft,pIndex pRight);
bool checkMoreThenHalf(vector<int> numbers,int result);

int MoreThanHalfNum_Solution(vector<int> numbers) {
	int length = numbers.size();
	if(length==0)	return 0;	//无效输入

	pIndex pLeft = numbers.begin();
	pIndex pRight = numbers.end()-1;
	pIndex pMidBase = pLeft + length/2;		//n/2位置
	pIndex pMid = partition(numbers,pLeft,pRight);		//划分
	while( pMid != pMidBase ){
		if( pMid > pMidBase )
			pMid = partition(numbers,pLeft,pMid-1);		//n/2位置在左半段
		else
			pMid = partition(numbers,pMid+1,pRight);	//n/2位置在右半段
	}
	int result = *pMid;
	//检验结果是否正确---防止数组中根本没有出现次数超过一半的元素
	if(!checkMoreThenHalf(numbers,result))
		result = 0;
	return result;
}

pIndex partition(vector<int> &numbers,pIndex pLeft,pIndex pRight){
	//简单选取 最后一个元素 作为基准元素
	int baseElem = *pRight;
	while(pLeft<pRight){
		while(pLeft<pRight && *pLeft<=baseElem)
			++pLeft;
		*pRight = *pLeft;
		while(pLeft<pRight && *pRight>=baseElem)
			--pRight;
		*pLeft = *pRight;
	}
	*pLeft = baseElem;
	return pLeft;
}

bool checkMoreThenHalf(vector<int> numbers,int result){
	int countCheck = 0;		
	for(pIndex it=numbers.begin();it<numbers.end();++it)
		if(*it==result)
			++countCheck;
	if(countCheck>numbers.size()/2)
		return true;
	return false;
}

//------思路2-----------------------------------------
//利用数组特点：要求的元素比其他元素出现的次数总和还多
//方法：遍历数组时，保存两个值：元素q，次数；如果下一个元素相同，则次数加1；
//	   不相同，则次数减1，如果减到-1，则更改元素q为当前元素，并设置次数为1；
//	   由于要找的元素出现的次数比其他元素次数之和还要多，则要找的元素一定是最后把times设置为1的元素；
//---注意：此处同样要检查结果是否正确，因为规律是基于一定存在出现次数超过一半的元素的前提下的；
//--------不能通过times>=1判断是否存在，例如 1,2,1,2,3,3 最后times=2，result=3，但该数组并不存在要求的元素；

int MoreThanHalfNum_Solution2(vector<int> numbers) {
	if(numbers.size()==0)	return 0;
	int result = numbers[0];
	int times = 1;
	for(pIndex it = numbers.begin()+1;it!=numbers.end();++it){
		if( *it == result)
			++times;
		else
			--times;
		if(times==-1){
			result = *it;
			times = 1;
		}
	}
	if(!checkMoreThenHalf(numbers,result))
		result = 0;
	return result;
}


/*
int main(){
	cout<<"输入整数数组，要求某个数超过数组的一半："<<endl;
	vector<int> array;
	int temp;
	while(1){
		cin.clear();
		cin.sync();
		array.clear();
		while(cin>>temp){
			array.push_back(temp);
		}
		cout<<"超过一半的数字为(用0表示没有)："<<MoreThanHalfNum_Solution(array)<<endl;
		cout<<"超过一半的数字为(用0表示没有)："<<MoreThanHalfNum_Solution2(array)<<endl;
	}
	system("pause");
}
*/