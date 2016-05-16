#include "stdafx.h"
#include <iostream>
using namespace std;

//问题描述：不用加减乘除做加法（求两个整数之和，要求在函数体内不得使用+、-、*、/四则运算符号。）

//思路：不能用四则运算，考虑位运算；分三步：
//	   1）不考虑进位，每一位相加，，对应位运算为 异或；
//     2)计算进位部分，只有 1+1=10，有进位，，对应位运算为 相与后左移一位；
//     3)两部分相加，相加的过程依然是重复1）2）步；

//--递归--
int Add_r(int num1, int num2){
	int sum = num1 ^ num2;				//1)
	int carry = (num1 & num2) << 1;		//2)	
	
	return carry==0?sum:Add_r(sum,carry);
}
//--非递归--
int Add(int num1, int num2){
	int sum,carry;
	do{
		sum = num1 ^ num2;				//1)
		carry = (num1 & num2) << 1;		//2)
		num1 = sum;						//sum+carry，即sum^carry(当没有进位，carry为0时;有进位，则继续异或上进位)
		num2 = carry;
	}while(carry!=0);

	return sum;
}

/*
int main(){
	int num1 = 1534,num2=18423;
	cout<<num1<<"+"<<num2<<" = "<<Add(num1,num2)<<endl;
	num1 = -3877,num2=34370;
	cout<<num1<<"+"<<num2<<" = "<<Add(num1,num2)<<endl;
	num1 = 0,num2=0;
	cout<<num1<<"+"<<num2<<" = "<<Add(num1,num2)<<endl;
	num1 = 0,num2=1567;
	cout<<num1<<"+"<<num2<<" = "<<Add(num1,num2)<<endl;
	num1 = 0,num2=-1567;
	cout<<num1<<"+"<<num2<<" = "<<Add(num1,num2)<<endl;
	system("pause");
}
*/