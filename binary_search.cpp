#include "stdafx.h"
#include<iostream>
#include<vector>
using namespace std;

//----���ֲ���---
//--ע�⣺���ֲ��ҿ��Բ�Ҫ�õݹ飬ֱ��whileѭ�������򵥣�
typedef int array_type; //����ֱ���滻����������
//�������鳤��
template <class T>
int getArrayLen(T& array)
{
	return (sizeof(array) / sizeof(array[0]));
}

//���룺����ָ��(�������飬����)�����鳤�ȣ�Ҫ���ҵ�ֵ
//���������val�����±꣬-1��ʾ������
int binary_search(array_type *array_inorder, int length,array_type val)
{
	int start = 0;
	int end = length -1;
	int mid = 0;
	while( start <= end ){ // ����ʱ����Ҫ���Ƚ�
		mid = (start + end)/2;
		if( val < array_inorder[mid] )
			end = mid -1;
		else if( val > array_inorder[mid] )
			start = mid + 1;
		else
			return mid;
	}
	return -1;
}

//�ݹ�汾
int binary_search_recursive(array_type *array_inorder, int start,int end,array_type val){
	if( start > end) //�Ҳ����Ľ�������
		return -1;
	int mid = (start+end)/2;
	if( val < array_inorder[mid])
		return binary_search_recursive(array_inorder,start,mid-1,val);
	else if( val > array_inorder[mid])
		return binary_search_recursive(array_inorder,mid+1,end,val);
	else //�ҵ��ˣ������±�
		return mid;
}
//-----------------

/*
int main(){
	array_type test_array[] = {1,3,5,6,7,8,9,10,10,14,15,17,29,33,35};//����
	array_type find_val = 8;
	int length = getArrayLen(test_array);
	int find_index = binary_search(test_array,10,find_val);
	//int find_index = binary_search_recursive(test_array,0,10-1,find_val);
	if(find_index==-1)
		cout<<find_val<<" is not found"<<endl;
	else
		cout<<find_val<<" index is "<<find_index<<endl;
	
	system("pause");
	return 0;
}
*/