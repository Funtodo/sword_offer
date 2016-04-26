#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;

//����������������к�ΪS�������������У����ٺ������������������ڰ��մ�С�����˳�����м䰴�տ�ʼ���ִ�С�����˳��
vector<int> PushContinuousSequence(int small,int big);
vector<vector<int> > FindContinuousSequence(int sum) {
	vector<vector<int> > result;
	if(sum<3)
		return result;
	int small = 1;		//���������н�С����
	int big = 2;
	int curSum = small+big;
	while( small <= sum/2){	//����������������������small����sumһ��ʱ�������ܴ��ں�Ϊsum����������
		if( curSum == sum ){		//�ҵ�һ��
			result.push_back(PushContinuousSequence(small,big));  //����samll��big����������ѹ��result��
			curSum -= small;			//Ҫ�ҳ����е��������У���������ƶ�ָ��
			++small;
		}else if(curSum < sum){
			++big;
			curSum += big;
		}else{
			curSum -= small;
			++small;
		}
	}
	return result;
}
vector<int> PushContinuousSequence(int small,int big){
	vector<int> seq;
	for(int i=small;i<=big;i++)
		seq.push_back(i);
	return seq;
}
/*
int main(){
	int s;
	while(1){
		cin.clear();  cin.sync();
		cout<<"����һ�������� s ��"<<endl;
		cin>>s;
		cout<<"��Ϊ "<<s<<" ����������Ϊ��"<<endl;
		vector<vector<int> > result = FindContinuousSequence(s);
		for(vector<vector<int> >::const_iterator i=result.begin();i!=result.end();++i){
			for(vector<int>::const_iterator j=(*i).begin();j!=(*i).end();++j)
				cout<<*j<<" ";
			cout<<endl;
		}
		cout<<endl;
	}
	system("pause");
}
*/