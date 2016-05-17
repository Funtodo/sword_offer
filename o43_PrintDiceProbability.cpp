#include "stdafx.h"
#include <iostream>
#include <time.h>
using namespace std;


//��Ŀ��������n���������ڵ��ϣ��������ӳ���һ��ĵ�����Ϊs��
//		  ����n����ӡ��s�����п��ܵ�ֵ���ֵĸ��ʣ�

//˼·1���ݹ鷽ʽ������˼·�����ݹ�����n�����ӵĵ������ۼӣ�����
int g_maxValue = 6;		//���ӵ���
void CountSum(int number,int *pCountSum);
void CountSum(int originNum,int curNum,int curSum,int *pCountSum);
void PrintProbability(int number){
	if(number<1)
		return;
	int maxSum = number * g_maxValue;		//������
	int* pCountSum = new int[maxSum-number+1];		//�����ڴ浥Ԫ������ͳ�Ʋ�ͬsum���ֵĴ���(index 0��Ԫͳ�Ƶ��Ǻ�Ϊnumber���ֵĴ���)
	for(int i=number;i<=maxSum;++i)
		pCountSum[i-number] = 0;
	
	CountSum(number,pCountSum);
	
	int total = pow((double)g_maxValue,number);		//�����ܵ�������
	for(int i=number;i<=maxSum;++i){
		double ratio = (double)pCountSum[i-number] / total;
		printf("%d: %e\n",i,ratio);
	}

	delete[] pCountSum;
}
void CountSum(int number,int *pCountSum){
	for(int i=1;i<=g_maxValue;++i)
		CountSum(number,number-1,i,pCountSum);
}
//originNum--ԭ�����Ӹ�����curNum--��ǰ���õ����ӣ�curSum--��ǰ���е��ۼӺͣ�pCountSum-�ۼӺ�ͳ��
//����originNum����ͳ���ۼӺ�ʱ��Ҫ����ӳ��
void CountSum(int originNum,int curNum,int curSum,int *pCountSum){
	if(curNum==0){
		++pCountSum[curSum-originNum];
		return;
	}
	for(int i=1;i<=g_maxValue;++i)
		CountSum(originNum,curNum-1,curSum+i,pCountSum);
}

//˼·2������ѭ�������ӵ���
//����˼�룺�����һ�����ӣ���ʱ��Ϊn�����ӳ��ֵĴ���������һ��ѭ�������ӵ�����Ϊn-1��n-2��n-3��n-4��n-5��n-6�Ĵ������ܺ�
//�������������飬������Ϊ��һ��ѭ���ļ�������
void PrintProbability_2(int number){
	if(number==0)
		return;
	//���������������飬����ʼ��
	int* pCountSum[2];		
	pCountSum[0] = new int[number*g_maxValue+1];
	pCountSum[1] = new int[number*g_maxValue+1];
	for(int i=0;i<number*g_maxValue+1;++i){
		pCountSum[0][i] = 0;
		pCountSum[1][i] = 0;
	}
	int flagArr = 0;	//��ʾ��ǰѭ���м����õ�����
	for(int i=1;i<=g_maxValue;++i)
		pCountSum[flagArr][i] = 1;
	

	//������������
	for(int k=2;k<=number;++k){

		flagArr = 1-flagArr;	//�л�����

		for(int i=0;i<k;++i)	//��k�����ӣ������ӵ���������С��k
			pCountSum[flagArr][i] = 0;
		for(int i=k;i<=number*g_maxValue;++i){	//��k�����ӣ�������Χ k~number*g_maxValue
			pCountSum[flagArr][i] = 0;			//��0
			for( int j=1; j<=g_maxValue && j<=i; ++j )	//ǰһ�������n-1~n-6�ۼӣ���ע��j>=i��
				pCountSum[flagArr][i] += pCountSum[1-flagArr][i-j];
		}
	}
	//��ӡ���
	int total = pow((double)g_maxValue,number);		//�����ܵ�������
	for(int i=number;i<=number*g_maxValue;++i){
		double ratio = (double)pCountSum[flagArr][i] / total;
		printf("%d: %e\n",i,ratio);
	}
	delete[] pCountSum[0];
	delete[] pCountSum[1];
}

/*
int main(){
	int num = 11;
	clock_t time1=clock();
	PrintProbability(num);
	clock_t time2=clock();
	cout<<"run time: "<<time2-time1<<endl<<endl;
	PrintProbability_2(num);
	clock_t time3=clock();
	cout<<"run time: "<<time3-time2<<endl;
	system("pause");
	return 0;
}
*/