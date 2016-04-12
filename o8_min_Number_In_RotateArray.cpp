#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

/*
��һ�������ʼ�����ɸ�Ԫ�ذᵽ�����ĩβ�����ǳ�֮Ϊ�������ת��
����һ���ǵݼ����е�һ����ת�������ת�������СԪ�ء�
��������{3,4,5,1,2}Ϊ{1,2,3,4,5}��һ����ת�����������СֵΪ1��
*/

int inOrderFind(vector<int>::const_iterator left, vector<int>::const_iterator right); //������������left��right��mid��ͬʱ��ֻ��˳�����
int minNumberInRotateArray(vector<int> rotateArray) {
	if(rotateArray.empty())
		throw exception("Invalid patameters");

	vector<int>::const_iterator left = rotateArray.begin(); //��һ��Ԫ��
	vector<int>::const_iterator right = rotateArray.end() - 1; //���һ��Ԫ��
	vector<int>::const_iterator mid = left;
	while( *left >= *right ){ //��� *left<*right ,˵������Ϊ���򣬵�һ��Ԫ�ؼ�Ϊ��СԪ��
		if( left +1 == right ){ //left����ָ��ǰ������е����һ��Ԫ�أ�right����ָ�����С���еĵ�һ��Ԫ��
			mid = right; 
			break;
		}
		//mid = (left + right)/2; //������������֮��ֻ�м�����û�мӷ�
		mid = (right - left)/2 + left;

		if( *left == *mid && *mid == *right ) //������������ȣ����޷��ж���С��Ԫ������һ�Σ�ֻ��˳����ң�����
			return inOrderFind(left,right);

		if( *mid >= *left ) //˵��midλ�����Σ���Сֵ��mid�ұ�
			left = mid;
		else if( *mid <= *right ) //˵��midλ���Ұ�Σ���Сֵ��mid���
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
	//int len = sizeof(testA)/sizeof(testA[0]);  ---���󣡣���testA��ָ�룬�Ѳ�������
	vector<int> testV(testA,testA+len);  //�������ʼ��vector�������������ַ��Χ
	print(testV);
	cout<<"==>"<<minNumberInRotateArray(testV)<<endl;
}
/*
int main(){
	//------���һ�β��Զ������������----------------

	//vector<int> testNull;
	//print(testNull); cout<<"==>"<<minNumberInRotateArray(testNull)<<endl;

	int test1[] = {5,6,7,8,0,1,2,3,4}; //���ܲ���
	int test2[] = {5,6,7,8,9,0,1,2}; //���ܲ���
	int test3[] = {5,6,0,1,2,3,4,5}; //���ܲ��ԣ����ظ�����
	int test4[] = {2,0,1,2,2,2,2}; //���ܲ��ԣ����ظ�����
	int test5[] = {2,2,2,2,0,1,2}; //���ܲ��ԣ����ظ�����

	int test6[] = {0,1,2,3,4,5,6}; //�߽���ԣ���������
	int test7[] = {0}; //�߽���ԣ�ֻ����һ�����ֵ�����
	int test8[] = {2,2,2,2,2,2,2,2}; //ȫ��һ��������

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