#include"stdafx.h"
#include<iostream>
#include <stdio.h>
#include<ctime>
using namespace std;

typedef int ElemTtype; 
void swap(ElemTtype &a, ElemTtype &b);

//=========简单排序算法实现========
//输入：待排表（int数组），数组长度
//输出：升序排列的数组

//直接插入排序，希尔排序；
//冒泡排序,快速排序；
//简单选择排序，堆排序；
//归并排序；
//基数排序；

//------------直接插入排序-----------------
void InsertSort(ElemTtype* A,int len){

	int i; //当前待排序元素位置
	int j; //找到的插入位置

	for( i=1; i<len; ++i ) //待排序的
		if( A[i] < A[i -1]){ //如果当前元素小于其前驱，才需将其插入有序表
			ElemTtype tmp = A[i]; //当前带插入元素

			//查找插入位置，（从后往前查找）查找的同时将元素往后挪
			for( j = i-1; j>=0 && tmp < A[j]; --j)
				A[j+1] = A[j];

			A[j+1] = tmp; //复制到插入位置
		}

}
//-----------折半插入排序-----------------
void BinaryInsertSort(ElemTtype* A,int len){
	int i, j, low, high, mid;
	for( i=1; i<len; ++i) //待排序的
		if( A[i] < A[i-1] ){ //带插入的小于其先驱，才需要往前插入排序
			ElemTtype tmp = A[i];

			//二分查找插入点
			low = 0; high = i-1;
			while(low <= high){
				mid = (low+high)/2;
				if( tmp == A[mid] )//有相同元素，则插入相同元素之后即可
					break;
				else if( tmp < A[mid])
					high = mid - 1;
				else //tmp>A[mid] )
					low = mid + 1;
			}
			//插入点：
			//没有相同元素时为： high + 1
			//有相同元素时为：mid+1
			int insertLoc =  (low > high)?(high+1):mid+1;

			//---将插入点之后的元素整体后移1位----
			for(j=i-1;j>=insertLoc; --j)
				A[j+1] = A[j];
			A[insertLoc] = tmp; //将第i个待排序元素复制到插入点
		}

}

//------------希尔排序（插入排序）---------
//注意，相隔步长为 dk 的元素为一组，而不是相邻dk个元素为一组
void ShellSort(ElemTtype* A,int len){

	int i; //当前待排元素位置
	int j; //找到的插入位置

	//与直接插入排序的差别是，增列是dk，不是1

	for( int dk = len/2; dk>=1; dk = dk/2)	//步长变化

		for( i = dk; i<len; ++i){			//前dk个元素（0~dk-1），正好是每组的第一个元素，不用找插入位置排序，，
											//后面每个元素按增量dk找组内元素插入排序（所以此处的1不用变为dk，后面出现的1全部变为dk即可）
			if( A[i] < A[i-dk]){			//带插入的小于其先驱(此时，前驱为i-dk)，才需要往前插入排序
				ElemTtype tmp = A[i];		//带插入的元素
				for(j=i-dk; j>=0 && tmp<A[j]; j = j-dk)
					A[j+dk] = A[j];
				A[j+dk] = tmp;
			}//end if
		}

}

//------------冒泡排序（交换排序）---------
void BubbleSort(ElemTtype* A,int len){
	for(int i=0; i<len-1; ++i ){				//n-1次冒泡
		bool flag = false;					//表示本趟是否发生交换的标志（某趟没有元素交换，说明已经有序）
		for(int j = len-1; j>i; --j ){		//从后往前冒泡，最后结果是将当前趟最小的元素放到位置 i
			if( A[j-1] > A[j]){
				swap(A[j-1],A[j]);
				flag = true;
			}
		}
		if(flag==false)
			return;
	}
}

//------------快速排序（交换排序）----------
void QuickSort_coreCur(ElemTtype* A,int low,int high); //递归快速排序
int Partition(ElemTtype* A,int low,int high); //划分，返回基准元素的正确位置
int RandomInRange(int low,int high);//在low 和 high中随机选择一个数

void QuickSort(ElemTtype* A,int len){
	QuickSort_coreCur(A,0,len-1); //快速排序递归程序
}
void QuickSort_coreCur(ElemTtype* A,int low,int high){
	if( low >= high )
		return;
	int kBase = Partition(A,low,high);//划分，并返回基准元素的位置
	QuickSort_coreCur(A,low,kBase-1); //依次对两个子表进行递归排序
	QuickSort_coreCur(A,kBase+1,high);
}
int Partition(ElemTtype* A,int low,int high){
	int index = RandomInRange(low,high);  //随机选择一个元素作基准元素
	swap( A[index], A[low] ); //交换，将选中的基准元素放在第一个位置

	ElemTtype base =  A[low]; //最开始A[low]是空出来的
	while(low<high){
		while( low<high && A[high]>=base) --high;
		A[low] = A[high]; //将比基准值小的元素移动到左端，此时A[high]是空出来的
		while( low<high && A[low]<=base) ++low;
		A[high] = A[low]; //将比基准值大的元素移动到右端，此时A[low]是空出来的
	}
	A[low] = base;
	return low;
}

int RandomInRange(int a,int b){
	srand((unsigned)time(NULL)); 
	return (rand() % (b-a+1))+ a;
	//要取得[a,b)的随机整数，使用(rand() % (b-a))+ a;
	//要取得[a,b]的随机整数，使用(rand() % (b-a+1))+ a;
	//要取得(a,b]的随机整数，使用(rand() % (b-a))+ a + 1;
}

//------------简单选择排序------------------
void SelectSort(ElemTtype* A,int len){
	for(int i=0;i<len-1;++i){		//一共进行 n-1 趟
		int iMin = i;				//找到第i趟最小的元素的位置
		for(int j = i+1;j<len; ++j)
			if( A[j] < A[iMin])
				iMin = j;			//更新最小元素位置
		if(iMin != i)
			swap(A[iMin], A[i]);	//把第i趟最小的元素放在i位置
	}
}
//------------堆排序------------------------
void HeapSort(ElemTtype* A,int len){

}

void printArray(ElemTtype* A,int len){
	for(int i=0;i<len;i++){
		cout<<A[i]<<" ";
	}
	cout<<endl;
}

void swap(ElemTtype &a, ElemTtype &b){
	ElemTtype tmp = a;
	a = b;
	b = tmp;
}
ElemTtype* copy(ElemTtype* myArray_origin,int len){
	ElemTtype *copys = new ElemTtype[len];
	for(int i=0;i<len;i++)
		copys[i] = myArray_origin[i];
	return copys;
}
/*
int main()
{
	ElemTtype myArray_origin[] = {3,18,2,6,17,9,10,1,5,2,12,23,18,6,14,25,6};
	int len = sizeof(myArray_origin)/sizeof(myArray_origin[0]);
	cout<<"原数组：        ";
	printArray(myArray_origin, len);

	ElemTtype *myArray = copy(myArray_origin,len); //因为传入数组，解析为指针，是直接修改原数组
	cout<<"简单插入排序：  ";
	InsertSort(myArray, len); printArray(myArray, len);

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"折半插入排序：  ";
	BinaryInsertSort(myArray, len); printArray(myArray, len);

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"希尔排序：      ";
	ShellSort(myArray, len); printArray(myArray, len);

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"冒泡排序：      ";
	BubbleSort(myArray, len); printArray(myArray, len);

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"快速排序：      ";
	QuickSort(myArray, len); printArray(myArray, len);

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"选择排序：      ";
	SelectSort(myArray, len); printArray(myArray, len);

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"堆排序：        ";
	HeapSort(myArray, len); printArray(myArray, len);

	system("pause");
	return 0;
}
*/