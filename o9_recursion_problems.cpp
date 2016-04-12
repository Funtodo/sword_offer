#include"stdafx.h"
#include<iostream>
#include<ctime>
#include <limits>
using namespace std;

//===================菲波那切数列===========================
//f(0)=0;f(1)=1; f(n) = f(n-1)+f(n-2);

//---直接转换为递归，效率非常低；
//Fibonacci(n-1)+Fibonacci(n-2)重复计算了两遍Fibonacci(n-2);
long long Fibonacci(unsigned int n) { //所用数据类型尽可能精确(unsigned int不可能为负数)
	if(n==0)
		return 0;
	if(n==1)
		return 1;
	return Fibonacci(n-1)+Fibonacci(n-2);
}
//---从下往上计算，保存中间计算结果（前两项）----
//时间复杂度：O(n)
long long Fibonacci2(unsigned int n){
	long long fibNMinusTwo = 0; //f(n-2)
	long long fibNMinusOne = 1; //f(n-1)
	if(n<2)
		return n==0?0:1;

	long long fibN; //f(n)
	for(int i=2; i<=n; ++i){
		fibN = fibNMinusTwo + fibNMinusOne;

		fibNMinusTwo = fibNMinusOne;
		fibNMinusOne = fibN;
	}
	return fibN;
}

//========================跳台阶================================
//青蛙一次可以跳1级台阶或2级台阶，问n级台阶，青蛙有几种跳法

//思路: n级台阶，第一次跳了1级，则剩下有 f(n-1)种跳法；第一次跳了2级，则剩下有 f(n-2)种跳法；
//即：f(n) = f(n-1)+f(n-2); f(1) = 1; f(2) = 2;
long long jumpFloor(unsigned int  number) {
	if(number==0)
		return 0;
	if(number<3)
		return number==1?1:2; //f(1) =1,f(2) = 2

    long long jfNMinusTwo = 1; //f(n-2)
	long long jfNMinusOne = 2; //f(n-1)
	
	long long jfN; //f(n)
	for(int i=3; i<=number; ++i){
		jfN = jfNMinusTwo + jfNMinusOne;

		jfNMinusTwo = jfNMinusOne;
		jfNMinusOne = jfN;
	}
	return jfN;
}

//==========变态跳台阶==============
//青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。

//思路：因为青蛙的步伐0~n任意，则相当于n位二进制，某位取1，表示青蛙在此处落脚；取0表示越过了；
//则除了最后一个台阶必须取1，其他取0或1皆可；（例如只有第二个台阶取1，表示，青蛙一次跳了2级后直接跳到了n）
//则，f(n) = 2^(n-1)
int jumpFloorII(int number) {
	if(number<=0)
		return 0;
	return 1<<(number-1); //左移几位，乘以几个2，即2的几次方
	//return 2^(number-1); //^是亦或运算
}

//==========矩形覆盖================
//我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？
//思路：f(n) = f(n-1)+f(n-2); f(1) = 1; f(2) = 2;，规定f(0)=1

int rectCover(int number) {
	if(number==0)
		return 1;
	return jumpFloor(number); //同跳台阶问题
}

/*
int main(){
	
	//-----------测试，int，unsigned int 所占字符数与表示范围-------------------
	cout << "type: \t" << "************size**************"<< endl;  
    cout << "int: \t" << "所占字节数：" << sizeof(int);  //4
    cout << "\t最大值：" << (numeric_limits<int>::max)();  //2'147'483'647
    cout << "\t最小值：" << (numeric_limits<int>::min)() << endl;  //2'147'483'648
    cout << "unsigned int: \t" << "所占字节数：" << sizeof(unsigned int);  //4
    cout << "\t最大值：" << (numeric_limits<unsigned int>::max)();  //4'294'967'295
    cout << "\t最小值：" << (numeric_limits<unsigned int>::min)() << endl<<endl; //0
	clock_t start,finish;
	//unsigned int n = 0; //会将输入解释为无符号整数，如-1，解释为 4'294'967'295，不能判断输入是否为负数
	int n = 0;
	cout<<"斐波那契数列："<<endl;
	while(cin>>n){ //0,1,1,2,3,5,8,13,21，
		start = clock();
		if(n<0){
			cout<<"n 不能< 0"<<endl;
			continue;
		}
		cout<<"简单递归：f("<<n<<") = "<<Fibonacci(n)<<"\t";
		finish = clock();
		cout<<"计算时间："<<finish-start<<endl;

		cout<<"从下至上：f("<<n<<") = "<<Fibonacci2(n)<<"\t";
		start = finish; finish = clock();
		cout<<"计算时间："<<finish-start<<endl;
	}
	cout<<"青蛙跳台阶："<<endl;
	cin.clear(); //将错误状态清除，否则第二个while将不接收输入
	cin.sync(); //清除输入缓冲区（不然上一步的错误输入还在缓冲区，while的cin将无效）
	while(cin>>n){
		start = clock();
		if(n<0){
			cout<<"n 不能< 0"<<endl;
			continue;
		}
		cout<<"从下至上：f("<<n<<") = "<<jumpFloor(n)<<"\t";
		finish = clock();
		cout<<"计算时间："<<finish-start<<endl;
	}
	cout<<jumpFloorII(0)<<" "<<jumpFloorII(1)<<" "<<jumpFloorII(2)<<" "<<jumpFloorII(3)<<" "<<jumpFloorII(10)<<endl;
	system("pause");
	return 0;
}
*/