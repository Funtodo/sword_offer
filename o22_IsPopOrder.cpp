//���������������У���һ�����б�ʾջ��ѹ��˳��Ҫ���жϵڶ��������Ƿ�Ϊ��ջ�ĵ������У�

//˼·����һ��ָ������ڶ������У������ǰԪ�ز��ڸ���ջջ�����򽫵�һ������δѹջ��Ԫ��ѹջ��ֱ��ջ��Ԫ���뵱ǰԪ����ͬ��
//�����ǰԪ��Ϊ����ջջ������pop��ָ�����ƣ�
//ֱ���ڶ������б����꣬�����ʱ����ջΪ�գ���true�����ջ��ߵ�һ����������δѹջԪ�أ���Ϊfalse��

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

bool IsPopOrder(vector<int> pushV,vector<int> popV) {
	if(pushV.size()==0 || popV.size()==0 || pushV.size()!=popV.size())
		return false;

	typedef vector<int>::const_iterator pIndex;
	stack<int> aStack;		//����ջ
	pIndex pPushV = pushV.begin();
	pIndex pPopV = popV.begin();

	while(pPopV != popV.end()){
		while( (aStack.size()==0 || aStack.top()!=*pPopV) && pPushV!=pushV.end()){
			aStack.push(*(pPushV++));
		}
		if(aStack.top()!=*pPopV)		//˵��ǰ��while�Ѿ������е�pushVѹ��ջ��
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