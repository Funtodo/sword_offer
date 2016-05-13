#include "stdafx.h"
#include <iostream>
using namespace std;

//问题描述：实现一个函数用来匹配包括'.'和'*'的正则表达式。
//        模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。
//假定 * 不能出现在最前面，且 不能出现 **
bool matchCore(char* str, char* pattern);
bool match(char* str, char* pattern){
	if( str==NULL || pattern==NULL )
		return false;
	return matchCore(str,pattern);		//递归核心
}
bool matchCore(char* str, char* pattern){
	if( *str=='\0' && *pattern=='\0')		//递归结束条件
		return true;
	//else if( *str=='\0' || *pattern=='\0')	return false;    //错误！例如 ""->.*
	else if( *pattern=='\0' && *str!='\0')
		return false;
	
	if( *(pattern+1)=='*'){
		if(str=='\0' && *pattern=='.')	// \0->.* 情况单独考虑
			return matchCore(str,pattern+2);
		if(*pattern=='.'){		//.*
			return matchCore(str,pattern+2)		//*前面一个字符出现0次
				|| ((*str!='\0') && matchCore(str+1,pattern+2))	//出现1次；
				|| ((*str!='\0') && matchCore(str+1,pattern));	//出现>1次；
		}else{		//ch*
			return matchCore(str,pattern+2)		//*前面一个字符出现0次
				|| ((*str==*pattern) && matchCore(str+1,pattern+2))   //出现1次；abc，abc*，如果直接用matchCore(str+1,pattern)会出现str结束了，但pattern没结束
				|| ((*str==*pattern) && matchCore(str+1,pattern));     //出现>1次
		}
	}else{				//下一位不是 * ，则只需要根据当前位给出匹配情况
		//if( *pattern=='.'|| *str==*pattern) //错误，pattern为.时，str要有字符匹配，即不能为'\0'
		if( (*pattern=='.' && *str!='\0') || *str==*pattern)
			return matchCore(str+1,pattern+1);
		return false;
	}
}

//matchCore的整理版
bool matchCore_2(char* str, char* pattern){
	if( *str=='\0' && *pattern=='\0')		//递归结束条件
		return true;
	else if( *pattern=='\0' && *str!='\0')
		return false;
	
	if( *(pattern+1)=='*'){
		if( (*pattern=='.'&& (*str!='\0')) ||  (*str==*pattern) )
			return matchCore(str,pattern+2)		//*前面一个字符出现0次
				|| matchCore(str+1,pattern+2)	//出现1次；
				|| matchCore(str+1,pattern);	//出现>1次；
		else
			return matchCore(str,pattern+2);
	}
	//下一位不是 * ，则只需要根据当前位给出匹配情况
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