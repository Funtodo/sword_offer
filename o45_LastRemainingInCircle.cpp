#include "stdafx.h"
#include <list>
#include <iostream>
#include <time.h>
using namespace std;

//解法一：用循环链表实现（循环链表用STL中的List模拟）
int LastRemaining_List(unsigned int n, unsigned int m){
	if(n<1||m<1)
		return -1;
	list<int> numbers;			//初始化
	for(int i=0;i<n;++i)
		numbers.push_back(i);

	list<int>::iterator current = numbers.begin();		//初始化current指向第一个数
	while(numbers.size()>1){
		for(int i=2;i<=m;++i){		//找到第m个数
			++current;
			if( current == numbers.end() )		//模拟循环列表
				current = numbers.begin();
		}
		list<int>::iterator next = ++current;		//第m个数待删除，next指向下一个数（下一次循环的起点）
		if( next == numbers.end() )				//模拟循环列表
			next = numbers.begin();
		current--;
		numbers.erase(current);
		current = next;
	}

	return *(numbers.begin());
}

//解法二：通过找规律，得到递归公式：f(n,m) = f'(n-1,m) = [f(n-1,m)+m]%n
int LastRemaining_Law(unsigned int n, unsigned int m){
	if(n<1||m<1)
		return -1;
	/*
	//递归代码----
	if(n==1)		//只有一个数
		return 0;
	return (LastRemaining_Law(n-1,m)+m)%n;
	*/
	//循环代码：
	int lastF = 0;
	for(int i=2;i<=n;++i)
		lastF = (lastF + m) % i ;		//注意取余 i 

	return lastF;
}

/*
int main(){
	int n=4000;
	int m=997;
	cout<<"n="<<n<<" m="<<m<<endl;

	clock_t time1=clock();
	cout<<"Remain number:"<<LastRemaining_List(n,m);
	clock_t time2=clock();
	cout<<" Run time:"<<time2-time1<<endl;

	cout<<"Remain number:"<<LastRemaining_Law(n,m);
	clock_t time3=clock();
	cout<<" Run time:"<<time3-time2<<endl;

	system("pause");
	return 0;
}
*/