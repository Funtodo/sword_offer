//=========数值整数次方==============
//--思路：0的<=0次方没有意义；正数次方可直接计算；负数次方为正数次方结果的倒数；
//--------其中正数次方可用递归方式求，
//			  n为偶数：base^n = (base^(n/2))^2，n为奇数：base^n =( base^(n/2))^2 * base;

#include"stdafx.h"
#include<iostream>
using namespace std;

bool g_InvalidInput = false; //全局变量，用来标识输入是否出错
//比较两个double是否相等
bool equal(double a,double b);
//当指数为 unsigned int （一定为正数）时的求余运算
double PowerWithUnsignedExponent(double base, unsigned int exponent);

double Power(double base, int exponent) {
	g_InvalidInput = false;

	if( equal(base,0.0) && exponent < 0 ){ // 0的负数次方都没有意义，，0的0次方为1
		g_InvalidInput = true;      //貌似直接 base == 0 判断也是正确的？？
		return 0.0;
	}
	unsigned int absExponent = (unsigned int) exponent; //省略(unsigned int)也可，隐式转换
	if(exponent < 0)
		absExponent = (unsigned int)-exponent;
	double result = PowerWithUnsignedExponent(base,absExponent);
	if(exponent < 0)		//指数为负数，结果为其绝对值次方的倒数
		result = 1.0/result;
	return result;
}

//当指数为 unsigned int （一定为正数）时的求余运算
double PowerWithUnsignedExponent(double base, unsigned int exponent) {
	if(exponent==0) //递归结束条件
		return 1;

	double result = 0.0;
	result = Power(base,exponent>>1); //用移位代替除法，但要注意 exponent 为正数才正确
	result *= result;
	if( exponent & 0x1 == 1 ) //奇数，用位运算“与“代替求余运算
		result *= base;
    return result;
}

//比较两个double是否相等
bool equal(double a,double b){
	if( a-b > -0.0000001 && a-b < 0.0000001 )
		return true;
	else
		return false;
}

/*
int main(){
	double base;
	int exponent;
	cout<<"依次输入double base，int exponent，如3.5 8"<<endl<<endl;
	cout<<"a^b = \t"<<"pow\t"<<"myPower"<<endl;
	while(cin>>base>>exponent){
		cout<<base<<"^"<<exponent
			<<" = \t"<<pow(base,exponent)<<"\t"<<Power(base,exponent)<<endl;
	}
	return 0;
}
*/