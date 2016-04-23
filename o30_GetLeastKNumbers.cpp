#include "stdafx.h"
#include <iostream>
#include <vector>
#include <set>
#include<algorithm>
using namespace std;
//得到最小的k个数

//------------思路1----------------
//采用类似试题29的思路，用partition的思路，二分缩小范围，直到选中的基准元素最后位置在位置K-1为止
//则此时，小于位置K-1的元素都在其左边(无序的)，则数组0~k-1的元素即最小的k个数
//-适用性：当可以修改输入的数组时使用，且数组能全部装入内存
//-时间复杂度：O(n)

typedef vector<int>::iterator pIndex;
extern pIndex partition(vector<int> &numbers,pIndex pLeft,pIndex pRight); //在o29中已定义

vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
	vector<int> result;
	if(input.size()==0 || k>input.size() || k<1)		//非法输入,,,注意  k<1很重要，否则后面取k-1元素会内存错误
		return result;

	pIndex pLeft = input.begin();
	pIndex pRight = input.end()-1;
	pIndex pK = pLeft + k -1;
	if(pK!=pRight){				//即数组元素恰好k个,则不用划分
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

//------------思路2---------------
//o(nlogk)的算法，特别适合处理海量数据(不用整个数组载入内存，且不用改变原数组)
//--过程：创建一个大小为k的数据容器来存储最小的k个元素；遍历数组，当容器中元素少于k个时，直接放入；
//--     当容器已满，则拿当前元素与容器中最大的元素比较，如果比其小，则用该元素替换容器中最大的元素；
//--则该容器数据结构的常用操作有：在k个整数中找到最大数；删除容器中最大数；插入新的数字；
//  用最大堆最合适；
//--自己实现最大堆要时间，可以考虑红黑树，红黑树中查找、删除和插入操作都只需要O(logk)时间；
//  STL中的set，multiset 都是基于红黑树实现的

vector<int> GetLeastNumbers_Solution2(vector<int> input, int k) {
	vector<int> result;
	if(input.size()==0 || k>input.size() || k<1)		//非法输入
		return result;
	multiset<int> leastKNumber;
	vector<int>::iterator iter = input.begin();
	for(;iter!=input.end();++iter){
		if(leastKNumber.size()<k)
			leastKNumber.insert(*iter);
		else{
			multiset<int>::iterator  maxIndex = --leastKNumber.end();	//set中最大元素即最后一个元素
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

//----直接采用STL---排序取前k个------
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
		cout<<"输入整数数组："<<endl;
		while(cin>>temp){
			array.push_back(temp);
		}
		cout<<"输入k："<<endl;
		cin.clear();  cin.sync();
		cin>>k;
		cout<<"最小的k个数为："<<endl;
		printVector(GetLeastNumbers_Solution(array,k));
		printVector(GetLeastNumbers_Solution2(array,k));
		printVector(GetLeastNumbers_Solution3(array,k));
	}
	system("pause");
}
*/