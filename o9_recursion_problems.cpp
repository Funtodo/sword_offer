#include"stdafx.h"
#include<iostream>
#include<ctime>
#include <limits>
using namespace std;

//===================�Ʋ���������===========================
//f(0)=0;f(1)=1; f(n) = f(n-1)+f(n-2);

//---ֱ��ת��Ϊ�ݹ飬Ч�ʷǳ��ͣ�
//Fibonacci(n-1)+Fibonacci(n-2)�ظ�����������Fibonacci(n-2);
long long Fibonacci(unsigned int n) { //�����������;����ܾ�ȷ(unsigned int������Ϊ����)
	if(n==0)
		return 0;
	if(n==1)
		return 1;
	return Fibonacci(n-1)+Fibonacci(n-2);
}
//---�������ϼ��㣬�����м��������ǰ���----
//ʱ�临�Ӷȣ�O(n)
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

//========================��̨��================================
//����һ�ο�����1��̨�׻�2��̨�ף���n��̨�ף������м�������

//˼·: n��̨�ף���һ������1������ʣ���� f(n-1)����������һ������2������ʣ���� f(n-2)��������
//����f(n) = f(n-1)+f(n-2); f(1) = 1; f(2) = 2;
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

//==========��̬��̨��==============
//����һ�ο�������1��̨�ף�Ҳ��������2��������Ҳ��������n���������������һ��n����̨���ܹ��ж�����������

//˼·����Ϊ���ܵĲ���0~n���⣬���൱��nλ�����ƣ�ĳλȡ1����ʾ�����ڴ˴���ţ�ȡ0��ʾԽ���ˣ�
//��������һ��̨�ױ���ȡ1������ȡ0��1�Կɣ�������ֻ�еڶ���̨��ȡ1����ʾ������һ������2����ֱ��������n��
//��f(n) = 2^(n-1)
int jumpFloorII(int number) {
	if(number<=0)
		return 0;
	return 1<<(number-1); //���Ƽ�λ�����Լ���2����2�ļ��η�
	//return 2^(number-1); //^���������
}

//==========���θ���================
//���ǿ�����2*1��С���κ��Ż�������ȥ���Ǹ���ľ��Ρ�������n��2*1��С�������ص��ظ���һ��2*n�Ĵ���Σ��ܹ��ж����ַ�����
//˼·��f(n) = f(n-1)+f(n-2); f(1) = 1; f(2) = 2;���涨f(0)=1

int rectCover(int number) {
	if(number==0)
		return 1;
	return jumpFloor(number); //ͬ��̨������
}

/*
int main(){
	
	//-----------���ԣ�int��unsigned int ��ռ�ַ������ʾ��Χ-------------------
	cout << "type: \t" << "************size**************"<< endl;  
    cout << "int: \t" << "��ռ�ֽ�����" << sizeof(int);  //4
    cout << "\t���ֵ��" << (numeric_limits<int>::max)();  //2'147'483'647
    cout << "\t��Сֵ��" << (numeric_limits<int>::min)() << endl;  //2'147'483'648
    cout << "unsigned int: \t" << "��ռ�ֽ�����" << sizeof(unsigned int);  //4
    cout << "\t���ֵ��" << (numeric_limits<unsigned int>::max)();  //4'294'967'295
    cout << "\t��Сֵ��" << (numeric_limits<unsigned int>::min)() << endl<<endl; //0
	clock_t start,finish;
	//unsigned int n = 0; //�Ὣ�������Ϊ�޷�����������-1������Ϊ 4'294'967'295�������ж������Ƿ�Ϊ����
	int n = 0;
	cout<<"쳲��������У�"<<endl;
	while(cin>>n){ //0,1,1,2,3,5,8,13,21��
		start = clock();
		if(n<0){
			cout<<"n ����< 0"<<endl;
			continue;
		}
		cout<<"�򵥵ݹ飺f("<<n<<") = "<<Fibonacci(n)<<"\t";
		finish = clock();
		cout<<"����ʱ�䣺"<<finish-start<<endl;

		cout<<"�������ϣ�f("<<n<<") = "<<Fibonacci2(n)<<"\t";
		start = finish; finish = clock();
		cout<<"����ʱ�䣺"<<finish-start<<endl;
	}
	cout<<"������̨�ף�"<<endl;
	cin.clear(); //������״̬���������ڶ���while������������
	cin.sync(); //������뻺��������Ȼ��һ���Ĵ������뻹�ڻ�������while��cin����Ч��
	while(cin>>n){
		start = clock();
		if(n<0){
			cout<<"n ����< 0"<<endl;
			continue;
		}
		cout<<"�������ϣ�f("<<n<<") = "<<jumpFloor(n)<<"\t";
		finish = clock();
		cout<<"����ʱ�䣺"<<finish-start<<endl;
	}
	cout<<jumpFloorII(0)<<" "<<jumpFloorII(1)<<" "<<jumpFloorII(2)<<" "<<jumpFloorII(3)<<" "<<jumpFloorII(10)<<endl;
	system("pause");
	return 0;
}
*/