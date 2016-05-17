#include "stdafx.h"
#include <iostream>
#include <time.h>
using namespace std;


//题目描述：把n个骰子仍在地上，所有骰子朝上一面的点数和为s。
//		  输入n，打印出s的所有可能的值出现的概率；

//思路1：递归方式，排列思路，，递归设置n个骰子的点数，累加，计数
int g_maxValue = 6;		//骰子点数
void CountSum(int number,int *pCountSum);
void CountSum(int originNum,int curNum,int curSum,int *pCountSum);
void PrintProbability(int number){
	if(number<1)
		return;
	int maxSum = number * g_maxValue;		//最大点数
	int* pCountSum = new int[maxSum-number+1];		//分配内存单元，用于统计不同sum出现的次数(index 0单元统计的是和为number出现的次数)
	for(int i=number;i<=maxSum;++i)
		pCountSum[i-number] = 0;
	
	CountSum(number,pCountSum);
	
	int total = pow((double)g_maxValue,number);		//骰子总的排列数
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
//originNum--原本骰子个数；curNum--当前设置的骰子；curSum--当前排列的累加和，pCountSum-累加和统计
//传入originNum，因统计累加和时需要坐标映射
void CountSum(int originNum,int curNum,int curSum,int *pCountSum){
	if(curNum==0){
		++pCountSum[curSum-originNum];
		return;
	}
	for(int i=1;i<=g_maxValue;++i)
		CountSum(originNum,curNum-1,curSum+i,pCountSum);
}

//思路2：基于循环求骰子点数
//核心思想：新添加一个骰子，此时和为n的骰子出现的次数等于上一次循环中骰子点数和为n-1，n-2，n-3，n-4，n-5，n-6的次数的总和
//用两个辅助数组，轮流作为下一次循环的计算数组
void PrintProbability_2(int number){
	if(number==0)
		return;
	//定义两个辅助数组，并初始化
	int* pCountSum[2];		
	pCountSum[0] = new int[number*g_maxValue+1];
	pCountSum[1] = new int[number*g_maxValue+1];
	for(int i=0;i<number*g_maxValue+1;++i){
		pCountSum[0][i] = 0;
		pCountSum[1][i] = 0;
	}
	int flagArr = 0;	//表示当前循环中计算用的数组
	for(int i=1;i<=g_maxValue;++i)
		pCountSum[flagArr][i] = 1;
	

	//依次增加骰子
	for(int k=2;k<=number;++k){

		flagArr = 1-flagArr;	//切换数组

		for(int i=0;i<k;++i)	//有k个骰子，则骰子点数不可能小于k
			pCountSum[flagArr][i] = 0;
		for(int i=k;i<=number*g_maxValue;++i){	//有k个骰子，点数范围 k~number*g_maxValue
			pCountSum[flagArr][i] = 0;			//清0
			for( int j=1; j<=g_maxValue && j<=i; ++j )	//前一个数组的n-1~n-6累加，，注意j>=i，
				pCountSum[flagArr][i] += pCountSum[1-flagArr][i-j];
		}
	}
	//打印结果
	int total = pow((double)g_maxValue,number);		//骰子总的排列数
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