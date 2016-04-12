//=========��ֵ�����η�==============
//--˼·��0��<=0�η�û�����壻�����η���ֱ�Ӽ��㣻�����η�Ϊ�����η�����ĵ�����
//--------���������η����õݹ鷽ʽ��
//			  nΪż����base^n = (base^(n/2))^2��nΪ������base^n =( base^(n/2))^2 * base;

#include"stdafx.h"
#include<iostream>
using namespace std;

bool g_InvalidInput = false; //ȫ�ֱ�����������ʶ�����Ƿ����
//�Ƚ�����double�Ƿ����
bool equal(double a,double b);
//��ָ��Ϊ unsigned int ��һ��Ϊ������ʱ����������
double PowerWithUnsignedExponent(double base, unsigned int exponent);

double Power(double base, int exponent) {
	g_InvalidInput = false;

	if( equal(base,0.0) && exponent < 0 ){ // 0�ĸ����η���û�����壬��0��0�η�Ϊ1
		g_InvalidInput = true;      //ò��ֱ�� base == 0 �ж�Ҳ����ȷ�ģ���
		return 0.0;
	}
	unsigned int absExponent = (unsigned int) exponent; //ʡ��(unsigned int)Ҳ�ɣ���ʽת��
	if(exponent < 0)
		absExponent = (unsigned int)-exponent;
	double result = PowerWithUnsignedExponent(base,absExponent);
	if(exponent < 0)		//ָ��Ϊ���������Ϊ�����ֵ�η��ĵ���
		result = 1.0/result;
	return result;
}

//��ָ��Ϊ unsigned int ��һ��Ϊ������ʱ����������
double PowerWithUnsignedExponent(double base, unsigned int exponent) {
	if(exponent==0) //�ݹ��������
		return 1;

	double result = 0.0;
	result = Power(base,exponent>>1); //����λ�����������Ҫע�� exponent Ϊ��������ȷ
	result *= result;
	if( exponent & 0x1 == 1 ) //��������λ���㡰�롰������������
		result *= base;
    return result;
}

//�Ƚ�����double�Ƿ����
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
	cout<<"��������double base��int exponent����3.5 8"<<endl<<endl;
	cout<<"a^b = \t"<<"pow\t"<<"myPower"<<endl;
	while(cin>>base>>exponent){
		cout<<base<<"^"<<exponent
			<<" = \t"<<pow(base,exponent)<<"\t"<<Power(base,exponent)<<endl;
	}
	return 0;
}
*/