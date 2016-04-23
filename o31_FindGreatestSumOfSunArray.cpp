#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

//�����������������
//����һ���������飬������������Ҳ�и�����������������ĺ͵����ֵ��
//Ҫ��ʱ�临�Ӷ�Ϊo(n)

//˼·����һ������maxSum���浱ǰ���ͣ�����curSum�����ۼӺͣ�
//     ��curSumΪ��ʱ����curSum�����ۼӣ�Ϊ��ʱ��������ǰ����ۼӺͣ�curSum=��ǰԪ�أ�
//	   ����ʱ�ۼӺ�curSum��maxSum�������maxSum��

int FindGreatestSumOfSubArray(vector<int> array) {
	if(array.size()==0)
		return 0;
	int maxSum = array[0];	//����
	int curSum = array[0];	//��ǰ������
	for(vector<int>::const_iterator it=array.begin()+1; it!=array.end(); ++it){
		if(curSum<=0)
			curSum = *it;
		else
			curSum += *it;
		if(curSum > maxSum)
			maxSum = curSum;
	}
	return maxSum;
}

/*
int main(){
	vector<int> array;
	int temp,k;
	while(1){
		cin.clear();  cin.sync();
		array.clear();
		cout<<"������������(�����и���)��"<<endl;
		while(cin>>temp){
			array.push_back(temp);
		}
		cout<<"���������������Ϊ:"<<"\t";
		cout<<FindGreatestSumOfSubArray(array)<<endl;
	}
	system("pause");
}
*/