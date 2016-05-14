#include "stdafx.h"
#include <iostream>
using namespace std;

//问题描述：请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
//        例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 
//             但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。
//思路：表示数值的字符串模式：[+/-]整数部分-digits[.[小数部分-digits]][e|E[+/-]指数部分-digits]
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
	bool hasDigits = scanDigits(str);		//整数部分-digits 和 小数部分 必须有一个存在，即 [+/-]e123错误
	if (*str != '\0'){
		// 有小数部分时
		if (*str == '.'){
			++str;
			if(!scanDigits(str) && !hasDigits)		//小数点后没有数字是ok的，如123.,,但不能整数小数部分都没有数字
				return false;

			if (*str == 'e' || *str == 'E')
				numeric = isExponential(++str);
		}
		// 没有小数部分时
		else if ((*str == 'e' || *str == 'E') && hasDigits)		//+/-e123错误，，即没有小数部分时，整数部分必须有数字
			numeric = isExponential(++str);
		else					//没有小数部分，也没有指数部分，但字符串扫描digits没有到'\0'，说明有非法字符
			numeric = false;
	}

	return numeric && *str == '\0';
}
bool scanDigits(char* &str){
	char* pBefore = str;

	while (*str != '\0' && *str >= '0' && *str <= '9')
		++str;

	// 如果有digits，则返回true
	return str > pBefore;
}
bool isExponential(char* &str){
	if (*str == '+' || *str == '-')
		++str;
	if (*str == '\0')			//保证指数不是以+/-结尾
		return false;

	scanDigits(str);
	return (*str == '\0') ? true : false;	//正确情况：以指数部分数字结尾，即scanDigits能扫描到字符串结束（不能，说明有非数字字符）
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