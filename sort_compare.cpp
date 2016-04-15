#include"stdafx.h"
#include<iostream>
#include <stdio.h>
#include<ctime>
using namespace std;

typedef int ElemTtype; 
void swap(ElemTtype &a, ElemTtype &b);
void printArray(ElemTtype* A,int len);
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
//（大根堆，得到的是从小到大）
inline void BuildMaxHeap(ElemTtype* A,int len);		//建立初始大根堆
void AdjustDown(ElemTtype* A,int k, int len);		//沿着某个节点往下调整
void HeapSort(ElemTtype* A,int len){
	if(A==NULL || len<=0)	return;
	BuildMaxHeap(A,len);			//建立初始大根堆
	for(int i=len-1; i>0; --i){		//>0因为最后只有一个元素时不用调整
		swap(A[0], A[i]);			//将堆的根节点（最大元素）放到最后面（与最后一个元素交换）
		AdjustDown(A,0,i);			//从根节点开始调整堆，同时堆的长度减1
	}
}
void BuildMaxHeap(ElemTtype* A,int len){
	for(int i=(len-1)/2; i>=0; --i)		//从最后一个非叶节点到根节点，反复调整堆（节点从0~len-1编号）
		AdjustDown(A,i,len);
}
void AdjustDown(ElemTtype* A,int k, int len){
	if( k > (len-1)/2 || len==1)	//!!!!-叶子节点(!或者只有一个节点 )，不用调整，直接返回---递归结束条件，也是防止A[2*k+1]越界的条件
		return;
	//找到当前非叶节点的最大的孩子节点
	//int iMaxSon = A[2*k+1]>A[2*k+2] ? (2*k+1):(2*k+2);//错误，有可能只有一个左子节点	//找到大的子节点	//从1开始编号，左子节点正好是2k，但是0开始，则是2k+1
	int iMaxSon = 2*k+1;
	if(2*k+2<len)										//存在右孩子节点，比较两个孩子节点
		iMaxSon = A[2*k+1]>A[2*k+2] ? (2*k+1):(2*k+2);		

	if(A[k]>=A[iMaxSon])									//不用调整
		return;
	swap(A[k],A[iMaxSon]);									//子节点大于父节点，则交换
	AdjustDown(A,iMaxSon,len);								//沿着有调整的子节点继续往下调整
}

//------------归并排序----------------------
void MergeSortCore(ElemTtype* A,int low,int high);	//递归归并排序
void merge(ElemTtype *A,int low,int mid,int high);	//将两个子序列合并
void MergeSort(ElemTtype* A,int len){
	if(A==NULL || len<=0)
		return;
	MergeSortCore(A,0,len-1);	//递归
}
//二路归并排序
void MergeSortCore(ElemTtype* A,int low,int high){
	if(low<high){
		int mid = (low+high)/2;			//从中间划分为两个子序列
		MergeSortCore(A, low,mid);		//对左半边归并排序
		MergeSortCore(A,mid+1,high);	//对右半边归并排序
		merge(A,low,mid,high);			//归并
	}
}
//采用辅助数组进行
void merge(ElemTtype *A,int low,int mid,int high){
	//子序列A1:low-mid;A2:mid+1,high;
	ElemTtype *lowB = new ElemTtype[mid-low+1];		//注意前后段数组长度的计算
	ElemTtype *highB = new ElemTtype[high-mid];
	for(int i =low; i<=mid; ++i)		//将要合并的左半段复制给lowB数组
		lowB[i-low] = A[i];
	for(int i =mid+1; i<=high; ++i)		//将要合并的右半段复制给highB数组
		highB[i-(mid+1)] = A[i];

	int i=0,j=0,k=low;					//i--lowB的指针，j--highB的指针，k--A的指针
	while( i< mid-low+1 && j< high-mid && k<= high){	//比较lowB，highB，每次把小的先复制回A中
		if( lowB[i] <= highB[j] )
			A[k++] = lowB[i++];
		else
			A[k++] = highB[j++];
	}
	while( i< mid-low+1)
		A[k++] = lowB[i++];		//若第一个表未检测完
	while( j< high-mid )
		A[k++] = highB[j++];		//若第二个表未检测完

	delete []lowB;
	delete []highB;
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
void printArray(ElemTtype* A,int len){
	for(int i=0;i<len;i++){
		cout<<A[i]<<" ";
	}
	cout<<endl;
}

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

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"归并排序：      ";
	MergeSort(myArray, len); printArray(myArray, len);
	
	system("pause");
	return 0;
}
