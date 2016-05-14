#include "stdafx.h"
#include <iostream>
using namespace std;

//������������ʵ��һ�����������ж��ַ����Ƿ��ʾ��ֵ������������С������
//        ���磬�ַ���"+100","5e2","-123","3.1416"��"-1E-16"����ʾ��ֵ�� 
//             ����"12e","1a3.14","1.2.3","+-5"��"12e+4.3"�����ǡ�
//˼·����ʾ��ֵ���ַ���ģʽ��[+/-]��������-digits[.[С������-digits]][e|E[+/-]ָ������-digits]
bool scanDigits(char* &str);
bool isExponential(char* &str);
bool isNumeric(char* str){		
	if(str==NULL)
		return false;
	if(*str=='+' || *str=='-')
		++str; 
	if (*str == '\0')
		return false;

	bool numeric = true;
	bool hasDigits = scanDigits(str);		//��������-digits �� С������ ������һ�����ڣ��� [+/-]e123����
	if (*str != '\0'){
		// ��С������ʱ
		if (*str == '.'){
			++str;
			if(!scanDigits(str) && !hasDigits)		//С�����û��������ok�ģ���123.,,����������С�����ֶ�û������
				return false;

			if (*str == 'e' || *str == 'E')
				numeric = isExponential(++str);
		}
		// û��С������ʱ
		else if ((*str == 'e' || *str == 'E') && hasDigits)		//+/-e123���󣬣���û��С������ʱ���������ֱ���������
			numeric = isExponential(++str);
		else					//û��С�����֣�Ҳû��ָ�����֣����ַ���ɨ��digitsû�е�'\0'��˵���зǷ��ַ�
			numeric = false;
	}

	return numeric && *str == '\0';
}
bool scanDigits(char* &str){
	char* pBefore = str;

	while (*str != '\0' && *str >= '0' && *str <= '9')
		++str;

	// �����digits���򷵻�true
	return str > pBefore;
}
bool isExponential(char* &str){
	if (*str == '+' || *str == '-')
		++str;
	if (*str == '\0')			//��ָ֤��������+/-��β
		return false;

	scanDigits(str);
	return (*str == '\0') ? true : false;	//��ȷ�������ָ���������ֽ�β����scanDigits��ɨ�赽�ַ������������ܣ�˵���з������ַ���
}

// ==================== Test Code ====================
//https://github.com/zhedahht/ChineseCodingInterviewAppendix/blob/master/NumericStrings/NumericString.cpp
void Test(char* testName, char* str, bool expected)
{
	if (testName != NULL)
		printf("%s begins: ", testName);

	if (isNumeric(str) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

/*
int main(int argc, char* argv[])
{
	Test("Test1", "100", true);
	Test("Test2", "123.45e+6", true);
	Test("Test3", "+500", true);
	Test("Test4", "5e2", true);
	Test("Test5", "3.1416", true);
	Test("Test6", "600.", true);
	Test("Test7", "-.123", true);
	Test("Test8", "-1E-16", true);
	Test("Test9", "1.79769313486232E+308", true);

	printf("\n\n");

	Test("Test10", "12e", false);
	Test("Test10", "12e+a", false);
	Test("Test11", "1a3.14", false);
	Test("Test12", "1+23", false);
	Test("Test13", "1.2.3", false);
	Test("Test14", "+-5", false);
	Test("Test15", "12e+5.4", false);
	Test("Test16", ".", false);
	Test("Test17", ".e1", false);
	Test("Test17", "-e123", false);
	Test("Test17", "e123", false);
	Test("Test18", "+.", false);
	system("pause");
	return 0;
}
*/