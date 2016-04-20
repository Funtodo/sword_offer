#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

//�����������������г��ִ�������һ���Ԫ��

//---------˼·1----------------------
//���������������n/2λ�õ�Ԫ��һ���ǳ��ִ����������������֣��������ת��Ϊ ���n/2���Ԫ��
//--���ÿ��ŵ�partition˼�룬������С��Χ��ֱ��ѡ�еĻ�׼Ԫ�����λ����n/2λ��Ϊֹ
//=ʱ�临�Ӷ�: O(n)
typedef vector<int>::iterator pIndex;
pIndex partition(vector<int> &numbers,pIndex pLeft,pIndex pRight);
bool checkMoreThenHalf(vector<int> numbers,int result);

int MoreThanHalfNum_Solution(vector<int> numbers) {
	int length = numbers.size();
	if(length==0)	return 0;	//��Ч����

	pIndex pLeft = numbers.begin();
	pIndex pRight = numbers.end()-1;
	pIndex pMidBase = pLeft + length/2;		//n/2λ��
	pIndex pMid = partition(numbers,pLeft,pRight);		//����
	while( pMid != pMidBase ){
		if( pMid > pMidBase )
			pMid = partition(numbers,pLeft,pMid-1);		//n/2λ��������
		else
			pMid = partition(numbers,pMid+1,pRight);	//n/2λ�����Ұ��
	}
	int result = *pMid;
	//�������Ƿ���ȷ---��ֹ�����и���û�г��ִ�������һ���Ԫ��
	if(!checkMoreThenHalf(numbers,result))
		result = 0;
	return result;
}

pIndex partition(vector<int> &numbers,pIndex pLeft,pIndex pRight){
	//��ѡȡ ���һ��Ԫ�� ��Ϊ��׼Ԫ��
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

//------˼·2-----------------------------------------
//���������ص㣺Ҫ���Ԫ�ر�����Ԫ�س��ֵĴ����ܺͻ���
//��������������ʱ����������ֵ��Ԫ��q�������������һ��Ԫ����ͬ���������1��
//	   ����ͬ���������1���������-1�������Ԫ��qΪ��ǰԪ�أ������ô���Ϊ1��
//	   ����Ҫ�ҵ�Ԫ�س��ֵĴ���������Ԫ�ش���֮�ͻ�Ҫ�࣬��Ҫ�ҵ�Ԫ��һ��������times����Ϊ1��Ԫ�أ�
//---ע�⣺�˴�ͬ��Ҫ������Ƿ���ȷ����Ϊ�����ǻ���һ�����ڳ��ִ�������һ���Ԫ�ص�ǰ���µģ�
//--------����ͨ��times>=1�ж��Ƿ���ڣ����� 1,2,1,2,3,3 ���times=2��result=3���������鲢������Ҫ���Ԫ�أ�

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
	cout<<"�����������飬Ҫ��ĳ�������������һ�룺"<<endl;
	vector<int> array;
	int temp;
	while(1){
		cin.clear();
		cin.sync();
		array.clear();
		while(cin>>temp){
			array.push_back(temp);
		}
		cout<<"����һ�������Ϊ(��0��ʾû��)��"<<MoreThanHalfNum_Solution(array)<<endl;
		cout<<"����һ�������Ϊ(��0��ʾû��)��"<<MoreThanHalfNum_Solution2(array)<<endl;
	}
	system("pause");
}
*/