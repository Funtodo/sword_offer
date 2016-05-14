#include "stdafx.h"
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

//问题描述：给定一个数组和滑动窗口的大小，找出【所有滑动窗口里数值的最大值】。
//        例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，
//             那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}； 
//             针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： 
//             {[2,3,4],2,6,2,5,1}，{2,[3,4,2],6,2,5,1}，{2,3,[4,2,6],2,5,1}，{2,3,4,[2,6,2],5,1}，{2,3,4,2,[6,2,5],1}，{2,3,4,2,6,[2,5,1]}。

vector<int> maxInWindows(const vector<int>& num, unsigned int size){
	vector<int> rMaxInWindows;		//存储所有滑动窗口里数值的最大值
	if(num.size()<size || size<=0 || num.size()==0) 	//不合理输入，返回空vector
		return rMaxInWindows;

	deque<int> index;				//辅助数组，存储可能成为滑动窗口最大值的index，队首为最大值
	//遍历num数组，找出【所有滑动窗口里数值的最大值】
	for(unsigned int i=0;i<size;++i){		//小于滑动窗口时
		while(!index.empty() && num[i]>=num[index.back()])
			index.pop_back();
		index.push_back(i);
	}
	for(unsigned int i=size;i<num.size();++i){
		rMaxInWindows.push_back(num[index.front()]);			//队首为此前滑动窗口(以下标i-1结束的窗口)的最大值
		//--存入下一个数字的下标--
		while( !index.empty() && num[i]>=num[index.back()])		//队列已有下标对应的数字小于当前数字，则队列中已有的数字不可能成为滑动窗口的最大值
			index.pop_back();
		if( !index.empty() && index.front()<=(int)(i-size))		//如果队头部的数字已经从窗口里滑出，则要从队头删除已滑出的数字
			index.pop_front();
		index.push_back(i);
	}
	rMaxInWindows.push_back(num[index.front()]);
	return rMaxInWindows;
}

// ==================== Test Code ====================
void Test(char* testName, const vector<int>& num, unsigned int size, const vector<int>& expected)
{
	if(testName != NULL)
		printf("%s begins: ", testName);

	vector<int> result = maxInWindows(num, size);

	vector<int>::const_iterator iterResult = result.begin();
	vector<int>::const_iterator iterExpected = expected.begin();
	while(iterResult < result.end() && iterExpected < expected.end())
	{
		if(*iterResult != *iterExpected)
			break;

		++iterResult;
		++iterExpected;
	}

	if(iterResult == result.end() && iterExpected == expected.end())
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

void Test1()
{
	int num[] = {2, 3, 4, 2, 6, 2, 5, 1};
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = {4, 4, 6, 6, 6, 5};
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 3;

	Test("Test1", vecNumbers, size, vecExpected);
}

void Test2()
{
	int num[] = {1, 3, -1, -3, 5, 3, 6, 7};
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = {3, 3, 5, 5, 6, 7};
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 3;

	Test("Test2", vecNumbers, size, vecExpected);
}

// increasingly sorted
void Test3()
{
	int num[] = {1, 3, 5, 7, 9, 11, 13, 15};
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = {7, 9, 11, 13, 15};
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 4;

	Test("Test3", vecNumbers, size, vecExpected);
}

// decreasingly sorted
void Test4()
{
	int num[] = {16, 14, 12, 10, 8, 6, 4};
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = {16, 14, 12};
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 5;

	Test("Test4", vecNumbers, size, vecExpected);
}

// size of sliding windows is 1
void Test5()
{
	int num[] = {10, 14, 12, 11};
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = {10, 14, 12, 11};
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 1;

	Test("Test5", vecNumbers, size, vecExpected);
}

// size of sliding windows is same as the array length
void Test6()
{
	int num[] = {10, 14, 12, 11};
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	int expected[] = {14};
	vector<int> vecExpected(expected, expected + sizeof(expected) / sizeof(int));

	unsigned int size = 4;

	Test("Test6", vecNumbers, size, vecExpected);
}

// size of sliding windows is 0
void Test7()
{
	int num[] = {10, 14, 12, 11};
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	vector<int> vecExpected;

	unsigned int size = 0;

	Test("Test7", vecNumbers, size, vecExpected);
}

// size of sliding windows is greater than the array length
void Test8()
{
	int num[] = {10, 14, 12, 11};
	vector<int> vecNumbers(num, num + sizeof(num) / sizeof(int));

	vector<int> vecExpected;

	unsigned int size = 5;

	Test("Test8", vecNumbers, size, vecExpected);
}

/*
int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	Test8();
	system("pause");
	return 0;
}
*/