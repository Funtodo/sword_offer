#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

//===============����================================
//��������������һ���ַ���,���ֵ����ӡ�����ַ������ַ����������С�
//		  �������ظ��ַ���
//��˼·1�����ݹ鷽ʽ�������õ�һλ����һλ��Ϊstr��ÿһ�����ظ����ַ���ͨ������ʹ��һλΪ��ͬ�ַ�����Ȼ������strʣ�µ�Ԫ�أ�
//	   ֱ���������һλ����õ�һ�����У�
extern void swap(int &num1,int &num2);
void Permutation(string str,vector<string> &permuts,int curIndex);

vector<string> Permutation(string str) {
	vector<string> permuts;
	if(str.length()==0)
		return permuts;

	//--���ַ��������ַ��ֵ�������---
	sort(str.begin(),str.end());

	Permutation(str,permuts,0);
	return permuts;
}
void Permutation(string str,vector<string> &permuts,int curIndex){
	if( curIndex == str.length()-1 ){		//�̶������һ���ַ������õ�һ������
		permuts.push_back(str);
		return;
	}
	Permutation(str,permuts,curIndex+1);		//��ǰλ���䣬��������λ
	for(int i=curIndex+1;i<str.length();++i){	//�����Ժ���ĸ�λ��Ϊ��ǰΪ(����)������������λ
		if(str[curIndex]!=str[i]){				//��ȣ����ý������Ը�λ����
			swap(str[curIndex],str[i]);
			Permutation(str,permuts,curIndex+1);
			//swap(str[curIndex],str[i]);		//���Permutation��str�����ô��ݣ���˴���Ҫ�ٴν����ָ�ԭ���������������ܵõ��ֵ���
		}
	}
}

//��˼·2�����ֵ���(�ǵݹ�ʵ��)����http://dongxicheng.org/structure/permutation-combination/#top
//˼·����Ρ����ɸ���ȫ���е���һ��������ν����һ��������һ������һ��֮��û���ֵ�˳�������ڵ�ȫ�����ַ�����
//     ���Ҫ����һ������һ���о����ܳ��Ĺ�ͬǰ׺��Ҳ���仯�����ھ����̵ܶĺ�׺�ϡ�
//����������:839647521����һ������.
//     �����ҿ�ʼ,�ҵ���һ�����ұ�С������4(��Ϊ4<7����7>5>2>1),
//     �ٴ����ҿ�ʼ,�ҵ�4�ұ߱�4�������5(��Ϊ4>2>1��4<5),����4��5,��ʱ5�ұ�Ϊ7421,����Ϊ1247,������һ������:839651247.
//     (����ȫ���еķǵݹ�����ɺ���ǰ���滻�����滻�㣬Ȼ���ɺ���ǰ�ҵ�һ�����滻����������滻�����������ߵ��滻�����������ݡ�)
//!!--C++ STL ���ô˷�ʽʵ��--!!!---

bool my_Next_permutation(string &str);		//��һ������
vector<string> Permutation_non_recursion(string str) {
	vector<string> permuts;
	if(str.length()==0)
		return permuts;
	//--���ַ��������ַ��ֵ�������---
	sort(str.begin(),str.end());

	do{
		permuts.push_back(str);
	}while(my_Next_permutation(str));

	return permuts;
}
bool my_Next_permutation(string &str){
	//bool flag_notTheLast = true;

	int iToReplace = str.length()-2;	//iEnd ָ�� �滻��������һ�������ұߴ�����ߣ�
	while(iToReplace>=0 && str[iToReplace+1] <= str[iToReplace])
			--iToReplace;
	if(iToReplace<0){			//˵��str�Ѿ��ǽ������У���Ϊ���һ�����У�����һ���ǵ�һ�����У�������־��Ϊfalse
		reverse(str.begin(),str.end());
		return false;
	}
	int iBigThenReplace = str.length()-1;
	while(iBigThenReplace>iToReplace){
		if(str[iBigThenReplace]>str[iToReplace])
			break;
		--iBigThenReplace;
	}
	swap(str[iToReplace],str[iBigThenReplace]);
	reverse(str.begin()+iToReplace+1,str.end());
	return true;
}

//================���==========================
//��������������һ���ַ���,[���ֵ���]��ӡ�����ַ������ַ���������ϡ�
//		  �ݲ��������ظ��ַ������
//        ���磺abc=��a,b,c,ab,ac,bc,abc
//��˼·1�����ݹ鷽ʽ��
void combination(string &str,vector<string> &combins,string curCombin,int curLen,int curIndex);
vector<string> combination(string str){
	vector<string> combins;
	string curCombin;
	if(str.length()==0)
		return combins;

	//--���ַ��������ַ��ֵ�������---
	sort(str.begin(),str.end());

	for(int m=1;m<=str.length();++m){	//��ͬ��ϳ��ȣ���n���ַ�����ѡm����
		combination(str,combins,curCombin,m,0);
	}
	return combins;
}
//���룺ԭ�ַ���str����ǰѡȡ����ϳ���m����ǰѡȡ���curIndex��combins���洢������ϣ�curCombine��ǰ�����ǰ��ݹ����Ѿ�ѡȡ���ַ�����
//˼·���ݹ鷽ʽ��ѡ��m���ַ�����λ��curIndexѡȡ������������ѡ��1����λѡȡ���ٴӺ���ѡm-1���ַ���2����λ��ѡ���Ӻ���ѡm���ַ���
void combination(string &str,vector<string> &combins,string curCombin,int m,int curIndex){
	if(curIndex>str.length()-m)		//˵������ĳ����Ѿ�������ɳ���Ϊm�Ĵ�
		return;
	sort(str.begin(),str.end());
	if(m==0){		//�õ�һ�����
		combins.push_back(curCombin);
		return;
	}		    
	combination(str,combins,curCombin+str[curIndex],m-1,curIndex+1);	//��λ���������
	combination(str,combins,curCombin,m,curIndex+1);				    //��λ�����������
}

//��˼·2������λ����
//��ÿ�������һ������������Ӧ������ö�ٶ����Ƶ�ͬʱ��ö��ÿ����ϡ�
//���磬abcde����00000->null,00001->a,00010->b
//--�����ƣ����32λ;  �ҵõ��Ĳ����ֵ���
vector<string> combination_binary(string str){
	vector<string> result;
	int n = str.length();
	if(n==0) return result;
	sort(str.begin(),str.end());
	
	for(int binary=1; binary<(1<<n); ++binary){
		string tmp = "";
		for(int i=0;i<n;++i){	//�ж�ÿһλ�Ƿ�Ϊ1��Ϊ1���ʾȡ��λ
			if( binary & (1<<i) )
				tmp += str[i];
		}
		result.push_back(tmp);
	}
	return result;
}

//=======�ַ���ȫ����������չ==============

//���˻ʺ����⡿���������ʺ��ܴ���ͬһ�С�ͬһ�л���ͬһ�Խ�б���ϡ�
//˼·�����ڰ˸��ʺ�������������ܴ���ͬһ�У���ô��϶���ÿһ���ʺ�ռ��һ�С�
//     �������ǿ��Զ���һ������ColumnIndex[8]�������е�i�����ֱ�ʾλ�ڵ�i�еĻʺ���кš�
//     �Ȱ�ColumnIndex�İ˸����ֱַ���0-7��ʼ��������������Ҫ����������Ƕ�����ColumnIndex��ȫ���С�
//     �����������ò�ͬ�����ֳ�ʼ�������е����֣�������������ʺ�϶���ͬ�С�
//     ����ֻ��Ҫ�жϵõ���ÿһ�����ж�Ӧ�İ˸��ʺ��ǲ�����ͬһ�Խ�б���ϣ�Ҳ��������������±�i��j��
//     �ǲ���i-j==ColumnIndex[i]-Column[j]����j-i==ColumnIndex[i]-ColumnIndex[j]��
int g_number = 0;
bool Check(int ColumnIndex[] , int length);
void print_status(int ColumnIndex[] , int length);
void Permutation(int ColumnIndex[], int len, int index);
void EightQueen(int queens){
	if(queens<3)   return;
	int *ColumnIndex = new int[queens];
	for(int i=0;i<queens;++i)	//��0~7��ʼ��������queens=8��
		ColumnIndex[i] = i;

	Permutation(ColumnIndex, queens, 0);

	delete ColumnIndex;
}
void Permutation(int ColumnIndex[], int len, int index){
	if(index==len){		//���һ������
		if(Check(ColumnIndex,len)){			//��⵱ǰ���ж�Ӧ������״̬�Ƿ�Ϸ�
			++g_number;
			print_status(ColumnIndex,len);
		}
	}else{
		for(int i=index;i<len;++i){
			swap(ColumnIndex[index],ColumnIndex[i]);
			Permutation(ColumnIndex,len,index+1);
			swap(ColumnIndex[index],ColumnIndex[i]);
		}
	}
}

bool Check(int ColumnIndex[], int length){  
	int i,j;  
	for(i = 0 ; i < length; ++i)  
		for(j = i + 1 ; j < length; ++j)  
			if( i - j == ColumnIndex[i] - ColumnIndex[j] || j - i == ColumnIndex[i] - ColumnIndex[j])   //���������Խ�����  
				return false;
	return true;
}
void print_status(int ColumnIndex[] , int length){  
	printf("%d\n",g_number);  
	for(int i = 0 ; i < length; ++i)  
		printf("%d ",ColumnIndex[i]);  
	printf("\n");  
}
/*
void main(){

	int queens=9;	//�ʺ�����Ҳ�����̸���Ŀ��
	EightQueen(queens);

	string str;
	cout<<"����һ���ַ������������ظ��ַ�����"<<endl;
	while(cin>>str){
		cout<<"�����㷨1)��"<<endl;
		vector<string> result = Permutation(str);
		for(vector<string>::const_iterator it=result.begin();it!=result.end();++it)
			cout<<(*it)<<"\t";
		cout<<endl;
		cout<<"�����㷨2)��"<<endl;
		vector<string> result2 = Permutation_non_recursion(str);
		for(vector<string>::const_iterator it=result2.begin();it!=result2.end();++it)
			cout<<(*it)<<"\t";
		cout<<endl;

		cout<<"����㷨1)��"<<endl;
		vector<string> result3 = combination(str);
		for(vector<string>::const_iterator it=result3.begin();it!=result3.end();++it)
			cout<<(*it)<<"\t";
		cout<<endl;

		cout<<"����㷨2)��"<<endl;
		vector<string> result4 = combination_binary(str);
		for(vector<string>::const_iterator it=result4.begin();it!=result4.end();++it)
			cout<<(*it)<<"\t";
		cout<<endl;

		cout<<"������һ���ַ�����"<<endl;
		cin.clear();  cin.sync();
	}

	system("pause");
}
*/