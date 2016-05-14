#include "stdafx.h"
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

//��������������һ������ͻ������ڵĴ�С���ҳ������л�����������ֵ�����ֵ����
//        ���磬�����������{2,3,4,2,6,2,5,1}���������ڵĴ�С3��
//             ��ôһ������6���������ڣ����ǵ����ֵ�ֱ�Ϊ{4,4,6,6,6,5}�� 
//             �������{2,3,4,2,6,2,5,1}�Ļ�������������6���� 
//             {[2,3,4],2,6,2,5,1}��{2,[3,4,2],6,2,5,1}��{2,3,[4,2,6],2,5,1}��{2,3,4,[2,6,2],5,1}��{2,3,4,2,[6,2,5],1}��{2,3,4,2,6,[2,5,1]}��

vector<int> maxInWindows(const vector<int>& num, unsigned int size){
	vector<int> rMaxInWindows;		//�洢���л�����������ֵ�����ֵ
	if(num.size()<size || size<=0 || num.size()==0) 	//���������룬���ؿ�vector
		return rMaxInWindows;

	deque<int> index;				//�������飬�洢���ܳ�Ϊ�����������ֵ��index������Ϊ���ֵ
	//����num���飬�ҳ������л�����������ֵ�����ֵ��
	for(unsigned int i=0;i<size;++i){		//С�ڻ�������ʱ
		while(!index.empty() && num[i]>=num[index.back()])
			index.pop_back();
		index.push_back(i);
	}
	for(unsigned int i=size;i<num.size();++i){
		rMaxInWindows.push_back(num[index.front()]);			//����Ϊ��ǰ��������(���±�i-1�����Ĵ���)�����ֵ
		//--������һ�����ֵ��±�--
		while( !index.empty() && num[i]>=num[index.back()])		//���������±��Ӧ������С�ڵ�ǰ���֣�����������е����ֲ����ܳ�Ϊ�������ڵ����ֵ
			index.pop_back();
		if( !index.empty() && index.front()<=(int)(i-size))		//�����ͷ���������Ѿ��Ӵ����ﻬ������Ҫ�Ӷ�ͷɾ���ѻ���������
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