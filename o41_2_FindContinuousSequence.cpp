#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;

//问题描述：输出所有和为S的连续正数序列（至少含有两个数）。序列内按照从小至大的顺序，序列间按照开始数字从小到大的顺序
vector<int> PushContinuousSequence(int small,int big);
vector<vector<int> > FindContinuousSequence(int sum) {
	vector<vector<int> > result;
	if(sum<3)
		return result;
	int small = 1;		//连续序列中较小的数
	int big = 2;
	int curSum = small+big;
	while( small <= sum/2){	//连续序列至少两个数，则small超过sum一半时，不可能存在和为sum的连续序列
		if( curSum == sum ){		//找到一组
			result.push_back(PushContinuousSequence(small,big));  //将从samll到big的连续序列压入result中
			curSum -= small;			//要找出所有的连续序列，必须继续移动指针
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
		cout<<"输入一个正整数 s ："<<endl;
		cin>>s;
		cout<<"和为 "<<s<<" 的正数序列为："<<endl;
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