//给定两个整数序列，第一个序列表示栈的压入顺序，要求判断第二个序列是否为该栈的弹出序列；

//思路，用一个指针遍历第二个序列，如果当前元素不在辅助栈栈顶，则将第一个序列未压栈的元素压栈，直到栈顶元素与当前元素相同；
//如果当前元素为辅助栈栈顶，则pop，指针下移；
//直到第二个序列遍历完，如果此时辅助栈为空，则true，不空或者第一个序列有尚未压栈元素，则为false；

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

bool IsPopOrder(vector<int> pushV,vector<int> popV) {
	if(pushV.size()==0 || popV.size()==0 || pushV.size()!=popV.size())
		return false;

	typedef vector<int>::const_iterator pIndex;
	stack<int> aStack;		//辅助栈
	pIndex pPushV = pushV.begin();
	pIndex pPopV = popV.begin();

	while(pPopV != popV.end()){
		while( (aStack.size()==0 || aStack.top()!=*pPopV) && pPushV!=pushV.end()){
			aStack.push(*(pPushV++));
		}
		if(aStack.top()!=*pPopV)		//说明前面while已经将所有的pushV压入栈中
			break;
		else{
			aStack.pop();
			++pPopV;
		}
	}
	if(pPopV != popV.end())
		return false;
	return true;
}

/*
int main(){
	int pushA[] = {1,2,3,4,5};
	int popA[] = {4,5,3,2,1};
	vector<int> pushV(pushA,pushA+5);
	vector<int> popV(popA,popA+5);
	cout<<IsPopOrder(pushV,popV)<<" (expect 1)"<<endl;

	int pushA2[] = {1,2,3,4,5};
	int popA2[] = {4,3,5,1,2};
	vector<int> pushV2(pushA2,pushA2+5);
	vector<int> popV2(popA2,popA2+5);
	cout<<IsPopOrder(pushV2,popV2)<<" (expect 0)"<<endl;

	int pushA3[] = {1};
	int popA3[] = {1};
	vector<int> pushV3(pushA3,pushA3+1);
	vector<int> popV3(popA3,popA3+1);
	cout<<IsPopOrder(pushV3,popV3)<<" (expect 1)"<<endl;

	int pushA4[] = {1,2,3,4,5,6};
	int popA4[] = {4,5,3,2,1};
	vector<int> pushV4(pushA4,pushA4+6);
	vector<int> popV4(popA4,popA4+5);
	cout<<IsPopOrder(pushV4,popV4)<<" (expect 0)"<<endl;

	system("pause");
}
*/