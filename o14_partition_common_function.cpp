//������������������˳��ʹ����λ��ż��ǰ�棬�����е�����λ�������ǰ�벿�֣����е�ż��λ��λ������ĺ�벿��
//1����Ҫ��������������ż����ż��֮������λ�ò���
//2��  Ҫ��������������ż����ż��֮������λ�ò��䡣��
//==============�ܽᣬ���Ȿ���������򣬲��ȶ�������ȶ�����=====================

#include"stdafx.h"
#include<iostream>
#include<vector>
using namespace std;

//------------------------------------------------------------------------
//1����Ҫ��������������ż����ż��֮������λ�ò���-----------
//˼·�������ڿ��ŵĻ��ֺ�������������ָ��ɨ�裬���������ϵĽ�����ʱ�临�Ӷ�O��n��
//ע�⣺��ʹ�ú���ָ�룬�����ֵ������ú���ָ�봫�룬��ǿ����չ��--
//--------------------------------------------------------------------------
void reOrder(vector<int> &array, bool (*func)(int));
bool isEven(int num){
	return (num & 0x1) == 1;	//ע�⣺==�Ƚ������ > &��λ����� > &&�߼������
}
bool largeThen(int num){
	return num>5;
}
void reOrderArray(vector<int> &array) {
	if(array.empty())
		return;
	reOrder(array,isEven);
	//reOrder(array,largeThen);
}
void reOrder(vector<int> &array, bool (*func)(int)){	// ע�� & ��������ִ���꣬array����
	typedef vector<int>::iterator pIndex;
	pIndex pLeft = array.begin(),pRight = array.end()-1;
	while( pLeft < pRight ){
		while( pLeft < pRight && func(*pLeft) )	//����
			++pLeft;
		while( pLeft < pRight && !func(*pRight) )	//ż��
			--pRight;
		if( pLeft < pRight )
			swap(*pLeft, *pRight);
	}
}

//--���ú���ָ��
void reOrderArray_no_function_pointer(vector<int> &array) {
	typedef vector<int>::iterator pIndex;
	pIndex pLeft = array.begin(),pRight = array.end()-1;
	while( pLeft < pRight ){
		while( pLeft < pRight && (*pLeft & 0x1) == 1 )	//����
			++pLeft;
		//while( iLeft < iRight && array[iRight] & 0x1 == 0 )	//������������ԶΪfalse---��==�Ƚ������ > &��λ����� > &&�߼������
		while( pLeft < pRight && (*pRight & 0x1) == 0 )	//ż��
			--pRight;
		if( pLeft < pRight )
			swap(*pLeft, *pRight);
	}
}

//--------------------------------------------------------------------
//2��Ҫ��������������ż����ż��֮������λ�ò���-----------
//˼·1������ð������˼�룬����forѭ��ɨ�裬������������ߵĶԣ��򽻻�����ֱ��ĳ���в���������
//     ʱ�临�Ӷȣ�O(n^2)
//---------------------------------------------------------------------
void reOrderHoldRelative(vector<int> &array, bool (*func)(int));
void reOrderHoldRelative2(vector<int> &array, bool (*func)(int));
void reOrderArrayHoldRelative(vector<int> &array){
	if(array.empty())
		return;
	reOrderHoldRelative2(array,isEven);				//�ú���ָ����Ϊ�ָ�ָ��
}
void reOrderHoldRelative(vector<int> &array, bool (*func)(int)){
	typedef vector<int>::iterator pIndex;
	bool noSwap = true;
	for(pIndex i = array.begin(); (i < array.end()-1) && noSwap==true; ++i){		//n-1��
		noSwap = false;
		for(pIndex j = array.end()-1; j>i; --j){		//	����������һ�����������������������
			if( func(*j) && !func(*(j-1)) ){			//���������ż������
				swap(*j,*(j-1));
				noSwap = true;
			}
		}
	}
	/*//�����Ǳ������汾��ͬ��ͬ�����߼���ţ�����õ������ᷢ�����󣨶δ��󣬿���������Խ�磬��ջ��������磬�ݹ���ò���̫�ࣩ���������
	//�±�汾���ᡣ��
	for(int i = 0; i < array.size()-1 && noSwap==true; ++i){		//n-1��
		noSwap = false;
		for(int j = array.size()-1; j>i; --j){		//	����������һ�����������������������
			if( (array[j] & 0x1)==1 && ( array[j-1] & 0x1)!=1 ){			//���������ż������
				swap(array[j],array[j-1]);
				noSwap = true;
			}
		}
	}*/
}
//˼·2---�����ò�������˼�룬��������������뵽ǰ�桰���ź���
void reOrderHoldRelative2(vector<int> &array, bool (*func)(int)){
	typedef vector<int>::iterator pIndex;
	//pIndex curLastEven = 0;
	for(pIndex i = array.begin()+1; i < array.end(); ++i){
		int temp = *i;
		if(func(*i) && !func(*(i-1))){		//����ǰҪ���������������ǰ��"�ź���"����ż��ʱ������Ҫ����
			pIndex j = i;
			while( !func(*(j-1)) && j > array.begin() ){		//һ��Ҫע���ֹԽ��		
				*j = *(j-1);				//ż������Ų
				--j;
			}
			*j = temp;
		}
	}
}

//˼·3---���ù鲢����---�����-----------------------------
//-----------------------------------------------------------

//��ӡ���е����ݣ�������ʼ��ַ,endΪ���һ��Ҫ��ӡ��Ԫ�ص���һλ
template<typename T>
void PrintSequence(const T pBegin, const T pEnd){
	for(T it=pBegin; it!=pEnd; ++it)
		cout<<*it<<" ";
	cout<<endl;
}

/*
int main(){
	int test1[] = {1,2,3,4,5,6,7};//{3,2,9,1,2,5,4,10,12};
	vector<int> vtest1(test1, test1+sizeof(test1)/sizeof(test1[0]));
	reOrderArray(vtest1); 
	vector<int> vtest2(test1, test1+sizeof(test1)/sizeof(test1[0]));
	reOrderArrayHoldRelative(vtest2);
	PrintSequence(vtest1.begin(),vtest1.end());
	PrintSequence(vtest2.begin(),vtest2.end());
	system("pause");
	return 0;
}
*/