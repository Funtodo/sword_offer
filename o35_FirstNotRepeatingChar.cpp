#include "stdafx.h"
#include <iostream>
using namespace std;

//问题描述：在一个字符串中找到【第一个】只出现一次的【字符】
//关键点：哈希表思想，key-字符，value-字符出现的次数，，用哈希表能快速获得某个字符出现的次数
//		char可能取值一定，用定长数组表示哈希表，用ch的ASCII值作key进行下标映射

char FirstNotRepeatingChar_ch(string str) {
	if(str.length()==0)
		return '\0';
	const int tableSize = 256;		//长度为8的char总共有256种可能
	unsigned int hashTable[tableSize];
	for(int i=0;i<tableSize;++i)	//初始化为0
		hashTable[i] = 0;
	
	for(string::size_type i=0;i<str.length();++i)	//统计，按char的ASCII值映射
		++hashTable[str[i]];

	for(string::size_type i=0;i<str.length();++i){	//再次遍历字符串，查看每个char出现的次数，找到第一个只出现一次的字符
		if(hashTable[str[i]]==1) 
			return str[i];
	}
	return '\0';	//没有只出现一次的字符
}


//问题描述：在一个字符串(1<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的【字符的位置】。
//        若为空串，返回-1。位置索引从0开始（牛客-差不多）

int FirstNotRepeatingChar_index(string str) {
	if(str.length()==0)
		return -1;
	const int tableSize = 256;		//长度为8的char总共有256种可能
	unsigned int hashTable[tableSize];
	for(int i=0;i<tableSize;++i)	//初始化为0
		hashTable[i] = 0;

	for(string::size_type i=0;i<str.length();++i)	//统计，按char的ASCII值映射
		++hashTable[str[i]];

	for(string::size_type i=0;i<str.length();++i){	//再次遍历字符串，查看每个char出现的次数，找到第一个只出现一次的字符
		if(hashTable[str[i]]==1) 
			return i;							    //返回下标
	}
	return -1;	//没有只出现一次的字符
}