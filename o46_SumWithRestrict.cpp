#include "stdafx.h"
#include <iostream>
using namespace std;

//������������1+2+3+...+n��Ҫ����ʹ�ó˳�����for��while��if��else��switch��case�ȹؼ��ּ������ж���䣨A?B:C����
//Ҫ��n>0

//����﷨û�����ƣ�1+2+3+����+n = n(n+1)/2
int Sum_Solution_0(int n) {
	if(n<0) return -1;
	return n*(n+1)/2;
}
//���ߵݹ�
int Sum_Solution_0r(int n) {
	if(n<0) return -1;
	if(n==0)	return 0;
	return Sum_Solution_0r(n-1) + n;
}

//˼·1��ʵ�ֳ˷�������sizeof��ά����
/*int Sum_Solution_1(int n) {
	bool a[n][n+1];				//vs2010����������ͨ�����������Ϊ����ֵ��
	return sizeof(a)>>1;		//sizeof(a)=n(n+1)
}
*/

//˼·2�������߼���Ķ�·����ʵ�ֵݹ���ֹ��
//����·���ԡ����������ж����Ĺؼ��֣��Ϳ���ʹ�á��߼����Ķ�·���ԡ���
//			 ��� || ǰ��һ��Ϊ�棬�����Ĳ����ټ���
//			 ��� && ǰ��һ��Ϊ�٣������Ĳ����ټ���
int Sum_Solution_2(int n) {
	int ans = n;
	ans && (ans += Sum_Solution_2(n-1)) ;
	return ans;
}

//˼·3���ú���ָ��ʵ�ֵݹ���ֹ
typedef unsigned int (*fun_ptr)(int n);
unsigned int sum_terminate(int n){
	return 0;
}
unsigned int Sum_Solution_3(int n){
	fun_ptr f[2]={sum_terminate, Sum_Solution_3};
	return n+f[!!n](n-1);			//!!n--��n==0ʱ��Ϊ0����n>0ʱ��Ϊ1
}

//˼·4��ʹ����ľ�̬���Ժ͹��캯��
class tmp{
public:
	tmp(){++n;sum+=n;}
	static void Reset(){n=0;sum=0;}
	static unsigned int GetSum(){return sum;}
private:
	static unsigned int n;
	static unsigned int sum;
};
unsigned int tmp::n=0;			//��ľ�̬����Ҫ��ʼ��
unsigned int tmp::sum=0;

int Sum_Solution_4(int n) {
		tmp::Reset();
		tmp *a = new tmp[n];		//���ù��캯��n�Σ�ʵ���ۼ�
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