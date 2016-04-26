#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;

//��������������һ����������������һ������S���������в�����������ʹ�����ǵĺ�������S��
//       ����ж�����ֵĺ͵���S������������ĳ˻���С�ģ����������У�С�������


//˼·�������ǵ�������ģ����ֻ��Ҫά����β����ָ�룬������
//    ������һ���ҳ�����������һ���Ǻ�Ϊs�г˻���С�ģ�

bool FindNumbersWithSum(vector<int> &array,int sum,int &num1,int &num2) {
	int len = array.size();
	if(len<2 || sum<array[0])
		return false;

	int iLeft = 0;
	int iRight = len-1;
	while(iLeft<iRight){
		long long curSum = array[iLeft] + array[iRight];
		if( curSum == sum ){
			num1 = array[iLeft];
			num2 = array[iRight];
			return true;
		}
		else if( curSum > sum )
			--iRight;
		else //( curSum < sum)
			++iLeft;
	}
	return false;
}

//ţ��-����ͷҪ�󣬣������vector����
vector<int>  FindNumbersWithSum2(vector<int> &array,int sum) {
	vector<int> result;
	int len = array.size();
	if(len<2 || sum<array[0])
		return result;

	int iLeft = 0;
	int iRight = len-1;
	while(iLeft<iRight){
		long long curSum = array[iLeft] + array[iRight];
		if( curSum == sum ){
			result.push_back(array[iLeft]);
			result.push_back(array[iRight]);
			break;
		}
		else if( curSum > sum )
			--iRight;
		else //( curSum < sum)
			++iLeft;
	}
	return result;
}

/*
int main(){
	vector<int> numbers;
	int temp,sum,num1,num2;

	while(1){
		cin.clear();  cin.sync();
		numbers.clear();
		cout<<"����������������:  "<<endl;
		while(cin>>temp){
			numbers.push_back(temp);
		}
		cout<<"����һ������S:  ";
		cin.clear();  cin.sync();
		cin>>sum;

		//���ͨ�� �������� ����ַ �õ��������⺯������bool����־�Ƿ���ڽ��
		if(FindNumbersWithSum(numbers,sum,num1,num2))
			cout<<"��Ϊ "<<sum<<" ��������Ϊ:  "<<num1<<"\t"<<num2<<endl<<endl;
		else
			cout<<"�����ں�Ϊ "<<sum<<" ��������"<<endl<<endl;

		//���ͨ�� ����vector �õ�������ͨ�����vector��size�ж��Ƿ���ڽ��
		vector<int> result = FindNumbersWithSum2(numbers,sum);
		if(result.size()==2)
			cout<<"��Ϊ "<<sum<<" ��������Ϊ:  "<<result[0]<<"\t"<<result[1]<<endl<<endl;
		else
			cout<<"�����ں�Ϊ "<<sum<<" ��������"<<endl<<endl;
	}
	system("pause");
}
*/
