#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

//����������ͳ�����������������г��ֵĴ���
//˼·�����ֲ���˼·���ֱ���ֲ��ҵ��ҵ���һ�������һ�����ֵ����꣬Ȼ��������

//�˴����õݹ���ʽ�����룺vector��Ҫ���ҵ����֣���ǰ���ҷ�Χ����ֹ�±�
int GetFirstK(vector<int> &data,int k,int iLeft,int iRight){
	//if(left>right)		//-!!--ע�⣺left��right��C++�ı����ؼ��֣����ڸ�ʽ�����������룬�Ҷ��룩�����˴���ԶΪtrue��
	if(iLeft>iRight)		//û���ҵ������� -1 
		return -1;
	

	int iFirstK = 0;
	int iMid = (iLeft+iRight)/2;

	if(k==data[iMid]){
		if(iMid>0 && data[iMid-1]!=k || iMid==0)		//�ҵ��˵�һ��k����������
			iFirstK = iMid;
		else					//(iMid>0 && data[iMid-1]==k)
			iFirstK = GetFirstK(data,k,iLeft,iMid-1);
	}
	else if(k>data[iMid])
		iFirstK = GetFirstK(data,k,iMid+1,iRight);
	else			//(k<data[iMid])
		iFirstK = GetFirstK(data,k,iLeft,iMid-1);	

	return iFirstK;
}
int GetLastK(vector<int> &data,int k,int iLeft,int iRight){
	if(iLeft>iRight)		//û���ҵ������� -1 
		return -1;

	int iLastK = 0;
	int iMid = (iLeft+iRight)/2;

	if(k==data[iMid]){
		if(iMid<iRight && data[iMid+1]!=k || iMid==iRight)	//�ҵ������һ��k����������
			iLastK = iMid;
		else					//(iMid<iRight && data[iMid+1]==k)
			iLastK = GetLastK(data,k,iMid+1,iRight);
	}
	else if(k>data[iMid])
		iLastK = GetLastK(data,k,iMid+1,iRight);
	else			//(k<data[iMid])
		iLastK = GetLastK(data,k,iLeft,iMid-1);	

	return iLastK;
}

int GetNumberOfK(vector<int> data ,int k) {
	if(data.size()==0)
		return 0;
	int firstIndex = GetFirstK(data,k,0,data.size()-1);		//����k�ĵ�һ�������±꣬�ݹ���ֲ��ң����±���ʽ
	int lastIndex = GetLastK(data,k,0,data.size()-1);		//����k�����һ�����ֵ��±�
	if(firstIndex>-1 && lastIndex>-1)						//������ʱ��GetLastK��GetFirstK����-1
		return lastIndex - firstIndex + 1;
	return 0;
}

/*
int main(){
	vector<int> numbers;
	int temp;

	while(1){
		cin.clear();  cin.sync();
		numbers.clear();
		cout<<"�����ź�����������飺"<<endl;
		while(cin>>temp){
			numbers.push_back(temp);
		}
		cin.clear();  cin.sync();
		cout<<"������ҵ����֣�";
		cin>>temp;
		cout<<temp;
		cout<<" ���ֵĴ���Ϊ:  ";
		cout<<GetNumberOfK(numbers,temp)<<endl<<endl;
	}
	system("pause");
}
*/