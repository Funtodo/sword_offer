#include "stdafx.h"
#include <iostream>
using namespace std;

//������������һ���ַ������ҵ�����һ����ֻ����һ�εġ��ַ���
//�ؼ��㣺��ϣ��˼�룬key-�ַ���value-�ַ����ֵĴ��������ù�ϣ���ܿ��ٻ��ĳ���ַ����ֵĴ���
//		char����ȡֵһ�����ö��������ʾ��ϣ����ch��ASCIIֵ��key�����±�ӳ��

char FirstNotRepeatingChar_ch(string str) {
	if(str.length()==0)
		return '\0';
	const int tableSize = 256;		//����Ϊ8��char�ܹ���256�ֿ���
	unsigned int hashTable[tableSize];
	for(int i=0;i<tableSize;++i)	//��ʼ��Ϊ0
		hashTable[i] = 0;
	
	for(string::size_type i=0;i<str.length();++i)	//ͳ�ƣ���char��ASCIIֵӳ��
		++hashTable[str[i]];

	for(string::size_type i=0;i<str.length();++i){	//�ٴα����ַ������鿴ÿ��char���ֵĴ������ҵ���һ��ֻ����һ�ε��ַ�
		if(hashTable[str[i]]==1) 
			return str[i];
	}
	return '\0';	//û��ֻ����һ�ε��ַ�
}


//������������һ���ַ���(1<=�ַ�������<=10000��ȫ������ĸ���)���ҵ���һ��ֻ����һ�εġ��ַ���λ�á���
//        ��Ϊ�մ�������-1��λ��������0��ʼ��ţ��-��ࣩ

int FirstNotRepeatingChar_index(string str) {
	if(str.length()==0)
		return -1;
	const int tableSize = 256;		//����Ϊ8��char�ܹ���256�ֿ���
	unsigned int hashTable[tableSize];
	for(int i=0;i<tableSize;++i)	//��ʼ��Ϊ0
		hashTable[i] = 0;

	for(string::size_type i=0;i<str.length();++i)	//ͳ�ƣ���char��ASCIIֵӳ��
		++hashTable[str[i]];

	for(string::size_type i=0;i<str.length();++i){	//�ٴα����ַ������鿴ÿ��char���ֵĴ������ҵ���һ��ֻ����һ�ε��ַ�
		if(hashTable[str[i]]==1) 
			return i;							    //�����±�
	}
	return -1;	//û��ֻ����һ�ε��ַ�
}