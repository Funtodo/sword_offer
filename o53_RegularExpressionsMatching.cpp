#include "stdafx.h"
#include <iostream>
using namespace std;

//����������ʵ��һ����������ƥ�����'.'��'*'��������ʽ��
//        ģʽ�е��ַ�'.'��ʾ����һ���ַ�����'*'��ʾ��ǰ����ַ����Գ�������Σ�����0�Σ���
//�ٶ� * ���ܳ�������ǰ�棬�� ���ܳ��� **
bool matchCore(char* str, char* pattern);
bool match(char* str, char* pattern){
	if( str==NULL || pattern==NULL )
		return false;
	return matchCore(str,pattern);		//�ݹ����
}
bool matchCore(char* str, char* pattern){
	if( *str=='\0' && *pattern=='\0')		//�ݹ��������
		return true;
	//else if( *str=='\0' || *pattern=='\0')	return false;    //�������� ""->.*
	else if( *pattern=='\0' && *str!='\0')
		return false;
	
	if( *(pattern+1)=='*'){
		if(str=='\0' && *pattern=='.')	// \0->.* �����������
			return matchCore(str,pattern+2);
		if(*pattern=='.'){		//.*
			return matchCore(str,pattern+2)		//*ǰ��һ���ַ�����0��
				|| ((*str!='\0') && matchCore(str+1,pattern+2))	//����1�Σ�
				|| ((*str!='\0') && matchCore(str+1,pattern));	//����>1�Σ�
		}else{		//ch*
			return matchCore(str,pattern+2)		//*ǰ��һ���ַ�����0��
				|| ((*str==*pattern) && matchCore(str+1,pattern+2))   //����1�Σ�abc��abc*�����ֱ����matchCore(str+1,pattern)�����str�����ˣ���patternû����
				|| ((*str==*pattern) && matchCore(str+1,pattern));     //����>1��
		}
	}else{				//��һλ���� * ����ֻ��Ҫ���ݵ�ǰλ����ƥ�����
		//if( *pattern=='.'|| *str==*pattern) //����patternΪ.ʱ��strҪ���ַ�ƥ�䣬������Ϊ'\0'
		if( (*pattern=='.' && *str!='\0') || *str==*pattern)
			return matchCore(str+1,pattern+1);
		return false;
	}
}

//matchCore�������
bool matchCore_2(char* str, char* pattern){
	if( *str=='\0' && *pattern=='\0')		//�ݹ��������
		return true;
	else if( *pattern=='\0' && *str!='\0')
		return false;
	
	if( *(pattern+1)=='*'){
		if( (*pattern=='.'&& (*str!='\0')) ||  (*str==*pattern) )
			return matchCore(str,pattern+2)		//*ǰ��һ���ַ�����0��
				|| matchCore(str+1,pattern+2)	//����1�Σ�
				|| matchCore(str+1,pattern);	//����>1�Σ�
		else
			return matchCore(str,pattern+2);
	}
	//��һλ���� * ����ֻ��Ҫ���ݵ�ǰλ����ƥ�����
	if( (*pattern=='.' && *str!='\0') || *str==*pattern)
		return matchCore(str+1,pattern+1);
	return false;
}

//https://github.com/zhedahht/ChineseCodingInterviewAppendix/blob/master/RegularExpressionsMatching/RegularExpressions.cpp
// ==================== Test Code ====================

void Test(char* testName, char* string, char* pattern, bool expected)
{
	if(testName != NULL)
		printf("%s begins: ", testName);

	if(match(string, pattern) == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

/*
int main(int argc, char* argv[])
{
	Test("Test01", "", "", true);
	Test("Test02", "", ".*", true);
	Test("Test03", "", ".", false);
	Test("Test04", "", "c*", true);
	Test("Test05", "a", ".*", true);
	Test("Test06", "a", "a.", false);
	Test("Test07", "a", "", false);
	Test("Test08", "a", ".", true);
	Test("Test09", "a", "ab*", true);
	Test("Test10", "a", "ab*a", false);
	Test("Test11", "aa", "aa", true);
	Test("Test12", "aa", "a*", true);
	Test("Test13", "aa", ".*", true);
	Test("Test14", "aa", ".", false);
	Test("Test15", "ab", ".*", true);
	Test("Test16", "ab", ".*", true);
	Test("Test17", "aaa", "aa*", true);
	Test("Test18", "aaa", "aa.a", false);
	Test("Test19", "aaa", "a.a", true);
	Test("Test20", "aaa", ".a", false);
	Test("Test21", "aaa", "a*a", true);
	Test("Test22", "aaa", "ab*a", false);
	Test("Test23", "aaa", "ab*ac*a", true);
	Test("Test24", "aaa", "ab*a*c*a", true);
	Test("Test25", "aaa", ".*", true);
	Test("Test26", "aab", "c*a*b", true);
	Test("Test27", "aaca", "ab*a*c*a", true);
	Test("Test28", "aaba", "ab*a*c*a", false);
	Test("Test29", "bbbba", ".*a*a", true);
	Test("Test30", "bcbbabab", ".*a*a", false);
	system("pause");
	return 0;
}
*/