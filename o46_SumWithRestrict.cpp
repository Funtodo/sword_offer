#include "stdafx.h"
#include <iostream>
using namespace std;

//问题描述：求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。
//要求n>0

//如果语法没有限制：1+2+3+……+n = n(n+1)/2
int Sum_Solution_0(int n) {
	if(n<0) return -1;
	return n*(n+1)/2;
}
//或者递归
int Sum_Solution_0r(int n) {
	if(n<0) return -1;
	if(n==0)	return 0;
	return Sum_Solution_0r(n-1) + n;
}

//思路1：实现乘法可以用sizeof多维数组
/*int Sum_Solution_1(int n) {
	bool a[n][n+1];				//vs2010编译器不能通过（数组必须为常量值）
	return sizeof(a)>>1;		//sizeof(a)=n(n+1)
}
*/

//思路2：【用逻辑与的短路特性实现递归终止】
//【短路特性】：不能用判断语句的关键字，就考虑使用【逻辑与或的短路特性】：
//			 如果 || 前面一个为真，则后面的不会再计算
//			 如果 && 前面一个为假，则后面的不会再计算
int Sum_Solution_2(int n) {
	int ans = n;
	ans && (ans += Sum_Solution_2(n-1)) ;
	return ans;
}

//思路3：用函数指针实现递归终止
typedef unsigned int (*fun_ptr)(int n);
unsigned int sum_terminate(int n){
	return 0;
}
unsigned int Sum_Solution_3(int n){
	fun_ptr f[2]={sum_terminate, Sum_Solution_3};
	return n+f[!!n](n-1);			//!!n--当n==0时，为0，当n>0时，为1
}

//思路4：使用类的静态属性和构造函数
class tmp{
public:
	tmp(){++n;sum+=n;}
	static void Reset(){n=0;sum=0;}
	static unsigned int GetSum(){return sum;}
private:
	static unsigned int n;
	static unsigned int sum;
};
unsigned int tmp::n=0;			//类的静态变量要初始化
unsigned int tmp::sum=0;

int Sum_Solution_4(int n) {
		tmp::Reset();
		tmp *a = new tmp[n];		//调用构造函数n次，实现累加
		delete []a;
		a=NULL;
		return tmp::GetSum();
}

/*
int main(){
	cout<<Sum_Solution_4(19)<<endl;
	return 0;
}
*/