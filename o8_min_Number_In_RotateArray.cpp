#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

/*
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个非递减序列的一个旋转，输出旋转数组的最小元素。
例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
*/

int inOrderFind(vector<int>::const_iterator left, vector<int>::const_iterator right); //辅助函数，当left，right，mid相同时，只能顺序查找
int minNumberInRotateArray(vector<int> rotateArray) {
	if(rotateArray.empty())
		throw exception("Invalid patameters");

	vector<int>::const_iterator left = rotateArray.begin(); //第一个元素
	vector<int>::const_iterator right = rotateArray.end() - 1; //最后一个元素
	vector<int>::const_iterator mid = left;
	while( *left >= *right ){ //如果 *left<*right ,说明本身为升序，第一个元素即为最小元素
		if( left +1 == right ){ //left最终指向前面大序列的最后一个元素，right最终指向后面小序列的第一个元素
			mid = right; 
			break;
		}
		//mid = (left + right)/2; //！！！迭代器之间只有减法，没有加法
		mid = (right - left)/2 + left;

		if( *left == *mid && *mid == *right ) //！！！三者相等，则无法判断最小的元素在哪一段，只能顺序查找！！！
			return inOrderFind(left,right);

		if( *mid >= *left ) //说明mid位于左半段，最小值在mid右边
			left = mid;
		else if( *mid <= *right ) //说明mid位于右半段，最小值在mid左边
			right = mid;
	}
	return *mid;
}
int inOrderFind(vector<int>::const_iterator left, vector<int>::const_iterator right){
	int min = *left;
	for(++left; left<=right; ++left)
		if( *left < min )
			min = *left;
	return min;
}

void print(vector<int> &testV){
	if(testV.empty()){
		cout<<"Null";return;
	}
	for(vector<int>::const_iterator it=testV.begin(); it!=testV.end(); ++it)
		cout<<*it<<" ";
}
void testExample(int *testA, int len){
	//int len = sizeof(testA)/sizeof(testA[0]);  ---错误！！！testA是指针，已不是数组
	vector<int> testV(testA,testA+len);  //用数组初始化vector，传入迭代器地址范围
	print(testV);
	cout<<"==>"<<minNumberInRotateArray(testV)<<endl;
}
/*
int main(){
	//------如何一次测试多个样例？？？----------------

	//vector<int> testNull;
	//print(testNull); cout<<"==>"<<minNumberInRotateArray(testNull)<<endl;

	int test1[] = {5,6,7,8,0,1,2,3,4}; //功能测试
	int test2[] = {5,6,7,8,9,0,1,2}; //功能测试
	int test3[] = {5,6,0,1,2,3,4,5}; //功能测试，有重复数字
	int test4[] = {2,0,1,2,2,2,2}; //功能测试，有重复数字
	int test5[] = {2,2,2,2,0,1,2}; //功能测试，有重复数字

	int test6[] = {0,1,2,3,4,5,6}; //边界测试，升序数组
	int test7[] = {0}; //边界测试，只包含一个数字的数组
	int test8[] = {2,2,2,2,2,2,2,2}; //全部一样的数字

	testExample(test1,sizeof(test1)/sizeof(test1[0]));
	testExample(test2,sizeof(test2)/sizeof(test2[0]));
	testExample(test3,sizeof(test3)/sizeof(test3[0]));
	testExample(test4,sizeof(test4)/sizeof(test4[0]));
	testExample(test5,sizeof(test5)/sizeof(test5[0]));
	testExample(test6,sizeof(test6)/sizeof(test6[0]));
	testExample(test7,sizeof(test7)/sizeof(test7[0]));
	testExample(test8,sizeof(test8)/sizeof(test8[0]));

	system("pause");
	return 0;
}
*/