#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

void multiply(const vector<double>& array1, vector<double>& array2){
	if(array1.size()<=1 || array1.size()!=array2.size())
		return;
	array2[0] = 1.0;
	for(int i=1;i<array1.size();++i){
		array2[i] = array2[i-1] * array1[i-1];
	}
	double tmp = 1.0;
	for(int j=array1.size()-2;j>=0;--j){
		tmp *= array1[j+1];
		array2[j] *= tmp;
	}
}

//================= Test Code =================
//来自 https://github.com/zhedahht/ChineseCodingInterviewAppendix/tree/master/ArrayConstruction
static bool equalArrays(const vector<double>& array1, const vector<double>& array2)
{
	int length1= array1.size();
	int length2 = array2.size();

	if(length1 != length2)
		return false;

	for(int i = 0; i < length1; ++i)
	{
		if(abs(array1[i] - array2[i]) > 0.0000001)	//浮点数判断是否相等
			return false;
	}

	return true;
}

static void test(char* testName, const vector<double>& array1, vector<double>& array2, const vector<double>& expected){
	printf("%s Begins: ", testName);

	multiply(array1, array2);
	if(equalArrays(array2, expected))
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

static void test1()
{
	double array1[] = {1, 2, 3, 4, 5};
	double array2[] = {0, 0, 0, 0, 0};
	double expected[] = {120, 60, 40, 30, 24};

	test("Test1", vector<double>(array1, array1 + sizeof(array1) / sizeof(double)), 
		vector<double>(array2, array2 + sizeof(array2) / sizeof(double)), 
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test2()
{
	double array1[] = {1, 2, 0, 4, 5};
	double array2[] = {0, 0, 0, 0, 0};
	double expected[] = {0, 0, 40, 0, 0};

	test("Test2", vector<double>(array1, array1 + sizeof(array1) / sizeof(double)), 
		vector<double>(array2, array2 + sizeof(array2) / sizeof(double)), 
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test3()
{
	double array1[] = {1, 2, 0, 4, 0};
	double array2[] = {0, 0, 0, 0, 0};
	double expected[] = {0, 0, 0, 0, 0};

	test("Test3", vector<double>(array1, array1 + sizeof(array1) / sizeof(double)), 
		vector<double>(array2, array2 + sizeof(array2) / sizeof(double)), 
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test4()
{
	double array1[] = {1, -2, 3, -4, 5};
	double array2[] = {0, 0, 0, 0, 0};
	double expected[] = {120, -60, 40, -30, 24};

	test("Test4", vector<double>(array1, array1 + sizeof(array1) / sizeof(double)), 
		vector<double>(array2, array2 + sizeof(array2) / sizeof(double)), 
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

static void test5()
{
	double array1[] = {1, -2};
	double array2[] = {0, 0};
	double expected[] = {-2, 1};

	test("Test5", vector<double>(array1, array1 + sizeof(array1) / sizeof(double)), 
		vector<double>(array2, array2 + sizeof(array2) / sizeof(double)), 
		vector<double>(expected, expected + sizeof(expected) / sizeof(double)));
}

/*
void main()
{
	test1();
	test2();
	test3();
	test4();
	test5();
	vector<int> test(10);
	test[0] = 1;
	test[9] = 1;
	cout<<test[0]<<" "<<test[1]<<" "<<test[9];
	system("pause");
}
*/