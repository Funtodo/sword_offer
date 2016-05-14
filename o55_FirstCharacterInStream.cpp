#include "stdafx.h"
#include <vector>
#include <limits>

using namespace std;

//问题描述：实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。
//        当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。 
//		  如果当前字符流没有存在出现一次的字符，返回#字符
class CharStatistics
{
public:
	CharStatistics() : index (0){
		for(int i = 0; i < 256; ++i)
			occurrence[i] = -1;
	}

	void Insert(char ch){
		if(occurrence[ch] == -1)
			occurrence[ch] = index;
		else if(occurrence[ch] >= 0)
			occurrence[ch] = -2;
		index++;  
	}

	char FirstAppearingOnce(){
		char ch = '#';
		int minIndex = numeric_limits<int>::max();		//初始化为最大值
		for(int i = 0; i < 256; ++i)
			if(occurrence[i] >= 0 && occurrence[i] < minIndex){
				ch = (char)i;
				minIndex = occurrence[i];
			}
		return ch;
	}

private:
	// occurrence[i]:      ASCII码为i的字符出现的情况
	// occurrence[i] = -1: 该字符还未出现过
	// occurrence[i] = -2: 该字符已经出现不止一次
	// occurrence[i] >= 0: 该字符目前只出现了一次，且occurrence[i]为其出现的位置
	int occurrence[256];
	int index;
};

// ==================== Test Code ====================
void Test(char* testName, CharStatistics chars, char expected)
{
	if(testName != NULL)
		printf("%s begins: ", testName);

	if(chars.FirstAppearingOnce() == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

/*
int main(int argc, char* argv[])
{
	CharStatistics chars;

	Test("Test1", chars, '#');

	chars.Insert('g');
	Test("Test2", chars, 'g');

	chars.Insert('o');
	Test("Test3", chars, 'g');

	chars.Insert('o');
	Test("Test4", chars, 'g');

	chars.Insert('g');
	Test("Test5", chars, '#');

	chars.Insert('l');
	Test("Test6", chars, 'l');

	chars.Insert('e');
	Test("Test7", chars, 'l');

	system("pause");
	return 0;
}
*/