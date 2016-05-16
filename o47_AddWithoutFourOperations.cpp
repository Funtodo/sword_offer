#include "stdafx.h"
#include <iostream>
using namespace std;

//�������������üӼ��˳����ӷ�������������֮�ͣ�Ҫ���ں������ڲ���ʹ��+��-��*��/����������š���

//˼·���������������㣬����λ���㣻��������
//	   1�������ǽ�λ��ÿһλ��ӣ�����Ӧλ����Ϊ ���
//     2)�����λ���֣�ֻ�� 1+1=10���н�λ������Ӧλ����Ϊ ���������һλ��
//     3)��������ӣ���ӵĹ�����Ȼ���ظ�1��2������

//--�ݹ�--
int Add_r(int num1, int num2){
	int sum = num1 ^ num2;				//1)
	int carry = (num1 & num2) << 1;		//2)	
	
	return carry==0?sum:Add_r(sum,carry);
}
//--�ǵݹ�--
int Add(int num1, int num2){
	int sum,carry;
	do{
		sum = num1 ^ num2;				//1)
		carry = (num1 & num2) << 1;		//2)
		num1 = sum;						//sum+carry����sum^carry(��û�н�λ��carryΪ0ʱ;�н�λ�����������Ͻ�λ)
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