#include "stdafx.h"
#include <list>
#include <iostream>
#include <time.h>
using namespace std;

//�ⷨһ����ѭ������ʵ�֣�ѭ��������STL�е�Listģ�⣩
int LastRemaining_List(unsigned int n, unsigned int m){
	if(n<1||m<1)
		return -1;
	list<int> numbers;			//��ʼ��
	for(int i=0;i<n;++i)
		numbers.push_back(i);

	list<int>::iterator current = numbers.begin();		//��ʼ��currentָ���һ����
	while(numbers.size()>1){
		for(int i=2;i<=m;++i){		//�ҵ���m����
			++current;
			if( current == numbers.end() )		//ģ��ѭ���б�
				current = numbers.begin();
		}
		list<int>::iterator next = ++current;		//��m������ɾ����nextָ����һ��������һ��ѭ������㣩
		if( next == numbers.end() )				//ģ��ѭ���б�
			next = numbers.begin();
		current--;
		numbers.erase(current);
		current = next;
	}

	return *(numbers.begin());
}

//�ⷨ����ͨ���ҹ��ɣ��õ��ݹ鹫ʽ��f(n,m) = f'(n-1,m) = [f(n-1,m)+m]%n
int LastRemaining_Law(unsigned int n, unsigned int m){
	if(n<1||m<1)
		return -1;
	/*
	//�ݹ����----
	if(n==1)		//ֻ��һ����
		return 0;
	return (LastRemaining_Law(n-1,m)+m)%n;
	*/
	//ѭ�����룺
	int lastF = 0;
	for(int i=2;i<=n;++i)
		lastF = (lastF + m) % i ;		//ע��ȡ�� i 

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