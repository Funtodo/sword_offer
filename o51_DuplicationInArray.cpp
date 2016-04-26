#include "stdafx.h"
#include <iostream>
using namespace std;

//������������һ������Ϊn����������������ֶ��ڡ�0��n-1���ķ�Χ�ڡ� 
//        ������ĳЩ�������ظ��ġ����ҳ�����������һ���ظ������֡�
extern void swap(int &num1,int &num2);
bool duplicate(int numbers[], int length, int* duplication) {
	if(numbers==NULL || length<2)
		return false;
	for(int i=0;i<length;++i)				//����Ҫ�� 0~n-1��Χ��
		if(numbers[i]<0 || numbers[i]>length-1)	
			return false;
	
	for(int i=0;i<length;++i){
		while( numbers[i] != i){
			if(numbers[i]==numbers[numbers[i]]){			//�ҵ���һ���ظ�������
				*duplication = numbers[i];
				return true;
			}else{
				/* ������ڶ�����numers[i]�Ѿ��ı䣬���������numbers[numbers[i]]ӳ�䵽����Ԫ���ˣ�������ֵ������
				int temp = numbers[i];
				numbers[i] = numbers[numbers[i]];
				numbers[numbers[i]] = temp;
				*/
				int temp = numbers[i];
				numbers[i] = numbers[numbers[i]];
				numbers[temp] = temp;
				//swap(numbers[i],numbers[numbers[i]]);  //Ҳok
			}
				
		}
	}
	return false;
}


//================= Test Code =================
//====���ԣ�https://github.com/zhedahht/ChineseCodingInterviewAppendix/tree/master/DuplicationInArray
bool contains(int array[], int length, int number)
{
	for(int i = 0; i < length; ++i)
	{
		if(array[i] == number)
			return true;
	}

	return false;
}

void test(char* testName, int numbers[], int lengthNumbers, int expected[], int expectedExpected, bool validArgument)
{
	printf("%s begins: ", testName);

	int duplication;
	bool validInput = duplicate(numbers, lengthNumbers, &duplication);

	if(validArgument == validInput)
	{
		if(validArgument)
		{
			if(contains(expected, expectedExpected, duplication))
			{
				printf("Passed.\n");
			}
			else
			{
				printf("FAILED.\n");
			}
		}
		else
		{
			printf("Passed.\n");
		}
	}
	else
	{
		printf("FAILED.\n");
	}
}

// The duplicated number is the smallest number
static void test1()
{
	int numbers[] = {2, 1, 3, 1, 4};
	int duplications[] = {1};
	test("Test1", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}

// The duplicated number is the greatest number
static void test2()
{
	int numbers[] = {2, 4, 3, 1, 4};
	int duplications[] = {4};
	test("Test2", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}

// There are more than one duplicated number
static void test3()
{
	int numbers[] = {2, 4, 2, 1, 4};
	int duplications[] = {2, 4};
	test("Test3", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}

// no duplicated numbers
static void test4()
{
	int numbers[] = {2, 1, 3, 0, 4};
	int duplications[] = {-1}; // not in use in the test function
	test("Test4", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), false);
}

// no duplicated numbers
static void test5()
{
	int numbers[] = {2, 1, 3, 5, 4};
	int duplications[] = {-1}; // not in use in the test function
	test("Test5", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), false);
}

/*
void main() 
{
	test1();
	test2();
	test3();
	test4();
	test5();
	system("pause");
}
*/
