//问题描述：调整数组顺序使奇数位于偶数前面，即所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分
//1）不要求奇数和奇数，偶数和偶数之间的相对位置不变
//2）  要求奇数和奇数，偶数和偶数之间的相对位置不变。）
//==============总结，本题本质上是排序，不稳定排序和稳定排序=====================

#include"stdafx.h"
#include<iostream>
#include<vector>
using namespace std;

//------------------------------------------------------------------------
//1）不要求奇数和奇数，偶数和偶数之间的相对位置不变-----------
//思路：类似于快排的划分函数，左右两个指针扫描，遇到不符合的交换，时间复杂度O（n）
//注意：可使用函数指针，将划分的依据用函数指针传入，增强可扩展性--
//--------------------------------------------------------------------------
void reOrder(vector<int> &array, bool (*func)(int));
bool isEven(int num){
	return (num & 0x1) == 1;	//注意：==比较运算符 > &按位运算符 > &&逻辑运算符
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
void reOrder(vector<int> &array, bool (*func)(int)){	// 注意 & ，否则函数执行完，array不变
	typedef vector<int>::iterator pIndex;
	pIndex pLeft = array.begin(),pRight = array.end()-1;
	while( pLeft < pRight ){
		while( pLeft < pRight && func(*pLeft) )	//奇数
			++pLeft;
		while( pLeft < pRight && !func(*pRight) )	//偶数
			--pRight;
		if( pLeft < pRight )
			swap(*pLeft, *pRight);
	}
}

//--不用函数指针
void reOrderArray_no_function_pointer(vector<int> &array) {
	typedef vector<int>::iterator pIndex;
	pIndex pLeft = array.begin(),pRight = array.end()-1;
	while( pLeft < pRight ){
		while( pLeft < pRight && (*pLeft & 0x1) == 1 )	//奇数
			++pLeft;
		//while( iLeft < iRight && array[iRight] & 0x1 == 0 )	//！！！错误，永远为false---，==比较运算符 > &按位运算符 > &&逻辑运算符
		while( pLeft < pRight && (*pRight & 0x1) == 0 )	//偶数
			--pRight;
		if( pLeft < pRight )
			swap(*pLeft, *pRight);
	}
}

//--------------------------------------------------------------------
//2）要求奇数和奇数，偶数和偶数之间的相对位置不变-----------
//思路1：采用冒泡排序思想，两个for循环扫描，遇到奇数在左边的对，则交换，，直到某趟中不发生交换
//     时间复杂度：O(n^2)
//---------------------------------------------------------------------
void reOrderHoldRelative(vector<int> &array, bool (*func)(int));
void reOrderHoldRelative2(vector<int> &array, bool (*func)(int));
void reOrderArrayHoldRelative(vector<int> &array){
	if(array.empty())
		return;
	reOrderHoldRelative2(array,isEven);				//用函数指针作为分割指标
}
void reOrderHoldRelative(vector<int> &array, bool (*func)(int)){
	typedef vector<int>::iterator pIndex;
	bool noSwap = true;
	for(pIndex i = array.begin(); (i < array.end()-1) && noSwap==true; ++i){		//n-1趟
		noSwap = false;
		for(pIndex j = array.end()-1; j>i; --j){		//	从右往左，则一定有奇数交换到当趟最左边
			if( func(*j) && !func(*(j-1)) ){			//如果奇数在偶数后面
				swap(*j,*(j-1));
				noSwap = true;
			}
		}
	}
	/*//可能是编译器版本不同，同样的逻辑，牛课上用迭代器会发生错误（段错误，可能是数组越界，堆栈溢出（比如，递归调用层数太多）等情况引起）
	//下标版本不会。。
	for(int i = 0; i < array.size()-1 && noSwap==true; ++i){		//n-1趟
		noSwap = false;
		for(int j = array.size()-1; j>i; --j){		//	从右往左，则一定有奇数交换到当趟最左边
			if( (array[j] & 0x1)==1 && ( array[j-1] & 0x1)!=1 ){			//如果奇数在偶数后面
				swap(array[j],array[j-1]);
				noSwap = true;
			}
		}
	}*/
}
//思路2---，采用插入排序思想，如果是奇数，插入到前面“已排好序”
void reOrderHoldRelative2(vector<int> &array, bool (*func)(int)){
	typedef vector<int>::iterator pIndex;
	//pIndex curLastEven = 0;
	for(pIndex i = array.begin()+1; i < array.end(); ++i){
		int temp = *i;
		if(func(*i) && !func(*(i-1))){		//仅当前要插入的是奇数，而前面"排好序"的有偶数时，才需要插入
			pIndex j = i;
			while( !func(*(j-1)) && j > array.begin() ){		//一定要注意防止越界		
				*j = *(j-1);				//偶数往后挪
				--j;
			}
			*j = temp;
		}
	}
}

//思路3---采用归并排序---待完成-----------------------------
//-----------------------------------------------------------

//打印序列的内容，给定起始地址,end为最后一个要打印的元素的下一位
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