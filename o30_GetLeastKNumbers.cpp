#include "stdafx.h"
#include <iostream>
#include <vector>
#include <set>
#include<algorithm>
using namespace std;
//�õ���С��k����

//------------˼·1----------------
//������������29��˼·����partition��˼·��������С��Χ��ֱ��ѡ�еĻ�׼Ԫ�����λ����λ��K-1Ϊֹ
//���ʱ��С��λ��K-1��Ԫ�ض��������(�����)��������0~k-1��Ԫ�ؼ���С��k����
//-�����ԣ��������޸����������ʱʹ�ã���������ȫ��װ���ڴ�
//-ʱ�临�Ӷȣ�O(n)

typedef vector<int>::iterator pIndex;
extern pIndex partition(vector<int> &numbers,pIndex pLeft,pIndex pRight); //��o29���Ѷ���

vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
	vector<int> result;
	if(input.size()==0 || k>input.size() || k<1)		//�Ƿ�����,,,ע��  k<1����Ҫ���������ȡk-1Ԫ�ػ��ڴ����
		return result;

	pIndex pLeft = input.begin();
	pIndex pRight = input.end()-1;
	pIndex pK = pLeft + k -1;
	if(pK!=pRight){				//������Ԫ��ǡ��k��,���û���
		pIndex pCurBase = partition(input,pLeft,pRight);
		while(pCurBase!=pK){
			if(pCurBase<pK)
				pCurBase = partition(input,pCurBase+1,pRight);
			if(pCurBase>pK)
				pCurBase = partition(input,pLeft,pCurBase-1);
		}
	}
	for(;pLeft<=pK;++pLeft)
		result.push_back(*pLeft);
	return result;
}

//------------˼·2---------------
//o(nlogk)���㷨���ر��ʺϴ���������(�����������������ڴ棬�Ҳ��øı�ԭ����)
//--���̣�����һ����СΪk�������������洢��С��k��Ԫ�أ��������飬��������Ԫ������k��ʱ��ֱ�ӷ��룻
//--     ���������������õ�ǰԪ��������������Ԫ�رȽϣ��������С�����ø�Ԫ���滻����������Ԫ�أ�
//--����������ݽṹ�ĳ��ò����У���k���������ҵ��������ɾ��������������������µ����֣�
//  ����������ʣ�
//--�Լ�ʵ������Ҫʱ�䣬���Կ��Ǻ������������в��ҡ�ɾ���Ͳ��������ֻ��ҪO(logk)ʱ�䣻
//  STL�е�set��multiset ���ǻ��ں����ʵ�ֵ�

vector<int> GetLeastNumbers_Solution2(vector<int> input, int k) {
	vector<int> result;
	if(input.size()==0 || k>input.size() || k<1)		//�Ƿ�����
		return result;
	multiset<int> leastKNumber;
	vector<int>::iterator iter = input.begin();
	for(;iter!=input.end();++iter){
		if(leastKNumber.size()<k)
			leastKNumber.insert(*iter);
		else{
			multiset<int>::iterator  maxIndex = --leastKNumber.end();	//set�����Ԫ�ؼ����һ��Ԫ��
			if(*iter < *maxIndex){
				leastKNumber.erase(maxIndex);
				leastKNumber.insert(*iter);
			}
		}
	}
	for(multiset<int>::const_iterator it=leastKNumber.begin();it!=leastKNumber.end();++it)
		result.push_back(*it);
	return result;
}

//----ֱ�Ӳ���STL---����ȡǰk��------
vector<int> GetLeastNumbers_Solution3(vector<int> input, int k) {
	vector<int>vec;
	if(k<1||input.empty()||input.size()<k)
		return vec;
	sort(input.begin(),input.end());
	for(int i=0;i<k;i++)
		vec.push_back(input[i]);
	return vec;
}

template<typename T> void printVector(const vector<T> &input){
	for(vector<T>::const_iterator it=input.begin();it!=input.end();++it)
		cout<<*it<<"\t";
	cout<<endl;
}

/*
int main(){
	vector<int> array;
	int temp,k;
	while(1){
		cin.clear();  cin.sync();
		array.clear();
		cout<<"�����������飺"<<endl;
		while(cin>>temp){
			array.push_back(temp);
		}
		cout<<"����k��"<<endl;
		cin.clear();  cin.sync();
		cin>>k;
		cout<<"��С��k����Ϊ��"<<endl;
		printVector(GetLeastNumbers_Solution(array,k));
		printVector(GetLeastNumbers_Solution2(array,k));
		printVector(GetLeastNumbers_Solution3(array,k));
	}
	system("pause");
}
*/