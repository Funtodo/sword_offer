#include"stdafx.h"
#include<iostream>
#include <stdio.h>
#include<ctime>
using namespace std;

typedef int ElemTtype; 
void swap(ElemTtype &a, ElemTtype &b);
void printArray(ElemTtype* A,int len);
//=========�������㷨ʵ��========
//���룺���ű�int���飩�����鳤��
//������������е�����

//ֱ�Ӳ�������ϣ������
//ð������,��������
//��ѡ�����򣬶�����
//�鲢����
//��������

//------------ֱ�Ӳ�������-----------------
void InsertSort(ElemTtype* A,int len){

	int i; //��ǰ������Ԫ��λ��
	int j; //�ҵ��Ĳ���λ��

	for( i=1; i<len; ++i ) //�������
		if( A[i] < A[i -1]){ //�����ǰԪ��С����ǰ�������轫����������
			ElemTtype tmp = A[i]; //��ǰ������Ԫ��

			//���Ҳ���λ�ã����Ӻ���ǰ���ң����ҵ�ͬʱ��Ԫ������Ų
			for( j = i-1; j>=0 && tmp < A[j]; --j)
				A[j+1] = A[j];

			A[j+1] = tmp; //���Ƶ�����λ��
		}

}
//-----------�۰��������-----------------
void BinaryInsertSort(ElemTtype* A,int len){
	int i, j, low, high, mid;
	for( i=1; i<len; ++i) //�������
		if( A[i] < A[i-1] ){ //�������С��������������Ҫ��ǰ��������
			ElemTtype tmp = A[i];

			//���ֲ��Ҳ����
			low = 0; high = i-1;
			while(low <= high){
				mid = (low+high)/2;
				if( tmp == A[mid] )//����ͬԪ�أ��������ͬԪ��֮�󼴿�
					break;
				else if( tmp < A[mid])
					high = mid - 1;
				else //tmp>A[mid] )
					low = mid + 1;
			}
			//����㣺
			//û����ͬԪ��ʱΪ�� high + 1
			//����ͬԪ��ʱΪ��mid+1
			int insertLoc =  (low > high)?(high+1):mid+1;

			//---�������֮���Ԫ���������1λ----
			for(j=i-1;j>=insertLoc; --j)
				A[j+1] = A[j];
			A[insertLoc] = tmp; //����i��������Ԫ�ظ��Ƶ������
		}

}

//------------ϣ�����򣨲�������---------
//ע�⣬�������Ϊ dk ��Ԫ��Ϊһ�飬����������dk��Ԫ��Ϊһ��
void ShellSort(ElemTtype* A,int len){

	int i; //��ǰ����Ԫ��λ��
	int j; //�ҵ��Ĳ���λ��

	//��ֱ�Ӳ�������Ĳ���ǣ�������dk������1

	for( int dk = len/2; dk>=1; dk = dk/2)	//�����仯

		for( i = dk; i<len; ++i){			//ǰdk��Ԫ�أ�0~dk-1����������ÿ��ĵ�һ��Ԫ�أ������Ҳ���λ�����򣬣�
											//����ÿ��Ԫ�ذ�����dk������Ԫ�ز����������Դ˴���1���ñ�Ϊdk��������ֵ�1ȫ����Ϊdk���ɣ�
			if( A[i] < A[i-dk]){			//�������С��������(��ʱ��ǰ��Ϊi-dk)������Ҫ��ǰ��������
				ElemTtype tmp = A[i];		//�������Ԫ��
				for(j=i-dk; j>=0 && tmp<A[j]; j = j-dk)
					A[j+dk] = A[j];
				A[j+dk] = tmp;
			}//end if
		}

}

//------------ð�����򣨽�������---------
void BubbleSort(ElemTtype* A,int len){
	for(int i=0; i<len-1; ++i ){				//n-1��ð��
		bool flag = false;					//��ʾ�����Ƿ��������ı�־��ĳ��û��Ԫ�ؽ�����˵���Ѿ�����
		for(int j = len-1; j>i; --j ){		//�Ӻ���ǰð�ݣ�������ǽ���ǰ����С��Ԫ�طŵ�λ�� i
			if( A[j-1] > A[j]){
				swap(A[j-1],A[j]);
				flag = true;
			}
		}
		if(flag==false)
			return;
	}
}

//------------�������򣨽�������----------
void QuickSort_coreCur(ElemTtype* A,int low,int high); //�ݹ��������
int Partition(ElemTtype* A,int low,int high); //���֣����ػ�׼Ԫ�ص���ȷλ��
int RandomInRange(int low,int high);//��low �� high�����ѡ��һ����

void QuickSort(ElemTtype* A,int len){
	QuickSort_coreCur(A,0,len-1); //��������ݹ����
}
void QuickSort_coreCur(ElemTtype* A,int low,int high){
	if( low >= high )
		return;
	int kBase = Partition(A,low,high);//���֣������ػ�׼Ԫ�ص�λ��
	QuickSort_coreCur(A,low,kBase-1); //���ζ������ӱ���еݹ�����
	QuickSort_coreCur(A,kBase+1,high);
}
int Partition(ElemTtype* A,int low,int high){
	int index = RandomInRange(low,high);  //���ѡ��һ��Ԫ������׼Ԫ��
	swap( A[index], A[low] ); //��������ѡ�еĻ�׼Ԫ�ط��ڵ�һ��λ��

	ElemTtype base =  A[low]; //�ʼA[low]�ǿճ�����
	while(low<high){
		while( low<high && A[high]>=base) --high;
		A[low] = A[high]; //���Ȼ�׼ֵС��Ԫ���ƶ�����ˣ���ʱA[high]�ǿճ�����
		while( low<high && A[low]<=base) ++low;
		A[high] = A[low]; //���Ȼ�׼ֵ���Ԫ���ƶ����Ҷˣ���ʱA[low]�ǿճ�����
	}
	A[low] = base;
	return low;
}

int RandomInRange(int a,int b){
	srand((unsigned)time(NULL)); 
	return (rand() % (b-a+1))+ a;
	//Ҫȡ��[a,b)�����������ʹ��(rand() % (b-a))+ a;
	//Ҫȡ��[a,b]�����������ʹ��(rand() % (b-a+1))+ a;
	//Ҫȡ��(a,b]�����������ʹ��(rand() % (b-a))+ a + 1;
}

//------------��ѡ������------------------
void SelectSort(ElemTtype* A,int len){
	for(int i=0;i<len-1;++i){		//һ������ n-1 ��
		int iMin = i;				//�ҵ���i����С��Ԫ�ص�λ��
		for(int j = i+1;j<len; ++j)
			if( A[j] < A[iMin])
				iMin = j;			//������СԪ��λ��
		if(iMin != i)
			swap(A[iMin], A[i]);	//�ѵ�i����С��Ԫ�ط���iλ��
	}
}

//------------������------------------------
//������ѣ��õ����Ǵ�С����
inline void BuildMaxHeap(ElemTtype* A,int len);		//������ʼ�����
void AdjustDown(ElemTtype* A,int k, int len);		//����ĳ���ڵ����µ���
void HeapSort(ElemTtype* A,int len){
	if(A==NULL || len<=0)	return;
	BuildMaxHeap(A,len);			//������ʼ�����
	for(int i=len-1; i>0; --i){		//>0��Ϊ���ֻ��һ��Ԫ��ʱ���õ���
		swap(A[0], A[i]);			//���ѵĸ��ڵ㣨���Ԫ�أ��ŵ�����棨�����һ��Ԫ�ؽ�����
		AdjustDown(A,0,i);			//�Ӹ��ڵ㿪ʼ�����ѣ�ͬʱ�ѵĳ��ȼ�1
	}
}
void BuildMaxHeap(ElemTtype* A,int len){
	for(int i=(len-1)/2; i>=0; --i)		//�����һ����Ҷ�ڵ㵽���ڵ㣬���������ѣ��ڵ��0~len-1��ţ�
		AdjustDown(A,i,len);
}
void AdjustDown(ElemTtype* A,int k, int len){
	if( k > (len-1)/2 || len==1)	//!!!!-Ҷ�ӽڵ�(!����ֻ��һ���ڵ� )�����õ�����ֱ�ӷ���---�ݹ����������Ҳ�Ƿ�ֹA[2*k+1]Խ�������
		return;
	//�ҵ���ǰ��Ҷ�ڵ�����ĺ��ӽڵ�
	//int iMaxSon = A[2*k+1]>A[2*k+2] ? (2*k+1):(2*k+2);//�����п���ֻ��һ�����ӽڵ�	//�ҵ�����ӽڵ�	//��1��ʼ��ţ����ӽڵ�������2k������0��ʼ������2k+1
	int iMaxSon = 2*k+1;
	if(2*k+2<len)										//�����Һ��ӽڵ㣬�Ƚ��������ӽڵ�
		iMaxSon = A[2*k+1]>A[2*k+2] ? (2*k+1):(2*k+2);		

	if(A[k]>=A[iMaxSon])									//���õ���
		return;
	swap(A[k],A[iMaxSon]);									//�ӽڵ���ڸ��ڵ㣬�򽻻�
	AdjustDown(A,iMaxSon,len);								//�����е������ӽڵ�������µ���
}

//------------�鲢����----------------------
void MergeSortCore(ElemTtype* A,int low,int high);	//�ݹ�鲢����
void merge(ElemTtype *A,int low,int mid,int high);	//�����������кϲ�
void MergeSort(ElemTtype* A,int len){
	if(A==NULL || len<=0)
		return;
	MergeSortCore(A,0,len-1);	//�ݹ�
}
//��·�鲢����
void MergeSortCore(ElemTtype* A,int low,int high){
	if(low<high){
		int mid = (low+high)/2;			//���м仮��Ϊ����������
		MergeSortCore(A, low,mid);		//�����߹鲢����
		MergeSortCore(A,mid+1,high);	//���Ұ�߹鲢����
		merge(A,low,mid,high);			//�鲢
	}
}
//���ø����������
void merge(ElemTtype *A,int low,int mid,int high){
	//������A1:low-mid;A2:mid+1,high;
	ElemTtype *lowB = new ElemTtype[mid-low+1];		//ע��ǰ������鳤�ȵļ���
	ElemTtype *highB = new ElemTtype[high-mid];
	for(int i =low; i<=mid; ++i)		//��Ҫ�ϲ������θ��Ƹ�lowB����
		lowB[i-low] = A[i];
	for(int i =mid+1; i<=high; ++i)		//��Ҫ�ϲ����Ұ�θ��Ƹ�highB����
		highB[i-(mid+1)] = A[i];

	int i=0,j=0,k=low;					//i--lowB��ָ�룬j--highB��ָ�룬k--A��ָ��
	while( i< mid-low+1 && j< high-mid && k<= high){	//�Ƚ�lowB��highB��ÿ�ΰ�С���ȸ��ƻ�A��
		if( lowB[i] <= highB[j] )
			A[k++] = lowB[i++];
		else
			A[k++] = highB[j++];
	}
	while( i< mid-low+1)
		A[k++] = lowB[i++];		//����һ����δ�����
	while( j< high-mid )
		A[k++] = highB[j++];		//���ڶ�����δ�����

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
	cout<<"ԭ���飺        ";
	printArray(myArray_origin, len);

	ElemTtype *myArray = copy(myArray_origin,len); //��Ϊ�������飬����Ϊָ�룬��ֱ���޸�ԭ����
	cout<<"�򵥲�������  ";
	InsertSort(myArray, len); printArray(myArray, len);

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"�۰��������  ";
	BinaryInsertSort(myArray, len); printArray(myArray, len);

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"ϣ������      ";
	ShellSort(myArray, len); printArray(myArray, len);

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"ð������      ";
	BubbleSort(myArray, len); printArray(myArray, len);

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"��������      ";
	QuickSort(myArray, len); printArray(myArray, len);

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"ѡ������      ";
	SelectSort(myArray, len); printArray(myArray, len);

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"������        ";
	HeapSort(myArray, len); printArray(myArray, len);

	delete myArray; myArray = copy(myArray_origin,len);
	cout<<"�鲢����      ";
	MergeSort(myArray, len); printArray(myArray, len);
	
	system("pause");
	return 0;
}
