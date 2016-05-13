#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

//===============排列================================
//问题描述：输入一个字符串,按字典序打印出该字符串中字符的所有排列。
//		  可能有重复字符；
//【思路1】：递归方式，先设置第一位（第一位可为str里每一个不重复的字符，通过交换使第一位为不同字符），然后设置str剩下的元素，
//	   直到设置最后一位，则得到一个排列；
extern void swap(int &num1,int &num2);
void Permutation(string str,vector<string> &permuts,int curIndex);

vector<string> Permutation(string str) {
	vector<string> permuts;
	if(str.length()==0)
		return permuts;

	//--对字符串按照字符字典序排序---
	sort(str.begin(),str.end());

	Permutation(str,permuts,0);
	return permuts;
}
void Permutation(string str,vector<string> &permuts,int curIndex){
	if( curIndex == str.length()-1 ){		//固定到最后一个字符，即得到一个排列
		permuts.push_back(str);
		return;
	}
	Permutation(str,permuts,curIndex+1);		//当前位不变，排列其余位
	for(int i=curIndex+1;i<str.length();++i){	//依次以后面的各位作为当前为(交换)，并排列其余位
		if(str[curIndex]!=str[i]){				//相等，则不用交换并以该位排列
			swap(str[curIndex],str[i]);
			Permutation(str,permuts,curIndex+1);
			//swap(str[curIndex],str[i]);		//如果Permutation的str是引用传递，则此处需要再次交换恢复原样（但这样并不能得到字典序）
		}
	}
}

//【思路2】：字典序法(非递归实现)，，http://dongxicheng.org/structure/permutation-combination/#top
//思路：如何【生成给定全排列的下一个】：所谓的下一个就是这一个与下一个之间没有字典顺序中相邻的全排列字符串。
//     这就要求这一个与下一个有尽可能长的共同前缀，也即变化限制在尽可能短的后缀上。
//方法：例子:839647521的下一个排列.
//     从最右开始,找到第一个比右边小的数字4(因为4<7，而7>5>2>1),
//     再从最右开始,找到4右边比4大的数字5(因为4>2>1而4<5),交换4、5,此时5右边为7421,倒置为1247,即得下一个排列:839651247.
//     (即：全排列的非递归就是由后向前找替换数和替换点，然后由后向前找第一个比替换数大的数与替换数交换，最后颠倒替换点后的所有数据。)
//!!--C++ STL 采用此方式实现--!!!---

bool my_Next_permutation(string &str);		//下一个排列
vector<string> Permutation_non_recursion(string str) {
	vector<string> permuts;
	if(str.length()==0)
		return permuts;
	//--对字符串按照字符字典序排序---
	sort(str.begin(),str.end());

	do{
		permuts.push_back(str);
	}while(my_Next_permutation(str));

	return permuts;
}
bool my_Next_permutation(string &str){
	//bool flag_notTheLast = true;

	int iToReplace = str.length()-2;	//iEnd 指向 替换数，即第一个逆序（右边大于左边）
	while(iToReplace>=0 && str[iToReplace+1] <= str[iToReplace])
			--iToReplace;
	if(iToReplace<0){			//说明str已经是降序排列，即为最后一个排列，则下一个是第一个排列，并将标志置为false
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

//================组合==========================
//问题描述：输入一个字符串,[按字典序]打印出该字符串中字符的所有组合。
//		  暂不考虑有重复字符情况；
//        例如：abc=》a,b,c,ab,ac,bc,abc
//【思路1】：递归方式，
void combination(string &str,vector<string> &combins,string curCombin,int curLen,int curIndex);
vector<string> combination(string str){
	vector<string> combins;
	string curCombin;
	if(str.length()==0)
		return combins;

	//--对字符串按照字符字典序排序---
	sort(str.begin(),str.end());

	for(int m=1;m<=str.length();++m){	//不同组合长度（从n个字符里面选m个）
		combination(str,combins,curCombin,m,0);
	}
	return combins;
}
//输入：原字符串str，当前选取的组合长度m，当前选取起点curIndex；combins，存储所有组合，curCombine当前组合在前面递归中已经选取的字符集合
//思路：递归方式，选择m个字符，从位置curIndex选取，，则有两种选择：1）该位选取，再从后面选m-1个字符；2）该位不选，从后面选m个字符。
void combination(string &str,vector<string> &combins,string curCombin,int m,int curIndex){
	if(curIndex>str.length()-m)		//说明后面的长度已经不够组成长度为m的串
		return;
	sort(str.begin(),str.end());
	if(m==0){		//得到一个组合
		combins.push_back(curCombin);
		return;
	}		    
	combination(str,combins,curCombin+str[curIndex],m-1,curIndex+1);	//该位放入组合中
	combination(str,combins,curCombin,m,curIndex+1);				    //该位不放入组合中
}

//【思路2】：用位运算
//将每个组合与一个二进制数对应起来，枚举二进制的同时，枚举每个组合。
//例如，abcde。。00000->null,00001->a,00010->b
//--有限制，最多32位;  且得到的并非字典序
vector<string> combination_binary(string str){
	vector<string> result;
	int n = str.length();
	if(n==0) return result;
	sort(str.begin(),str.end());
	
	for(int binary=1; binary<(1<<n); ++binary){
		string tmp = "";
		for(int i=0;i<n;++i){	//判断每一位是否为1，为1则表示取该位
			if( binary & (1<<i) )
				tmp += str[i];
		}
		result.push_back(tmp);
	}
	return result;
}

//=======字符串全排列问题扩展==============

//【八皇后问题】任意两个皇后不能处于同一行、同一列或者同一对角斜线上。
//思路：由于八个皇后的任意两个不能处在同一行，那么这肯定是每一个皇后占据一行。
//     于是我们可以定义一个数组ColumnIndex[8]，数组中第i个数字表示位于第i行的皇后的列号。
//     先把ColumnIndex的八个数字分别用0-7初始化，接下来我们要做的事情就是对数组ColumnIndex做全排列。
//     由于我们是用不同的数字初始化数组中的数字，因此任意两个皇后肯定不同列。
//     我们只需要判断得到的每一个排列对应的八个皇后是不是在同一对角斜线上，也就是数组的两个下标i和j，
//     是不是i-j==ColumnIndex[i]-Column[j]或者j-i==ColumnIndex[i]-ColumnIndex[j]。
int g_number = 0;
bool Check(int ColumnIndex[] , int length);
void print_status(int ColumnIndex[] , int length);
void Permutation(int ColumnIndex[], int len, int index);
void EightQueen(int queens){
	if(queens<3)   return;
	int *ColumnIndex = new int[queens];
	for(int i=0;i<queens;++i)	//用0~7初始化（假设queens=8）
		ColumnIndex[i] = i;

	Permutation(ColumnIndex, queens, 0);

	delete ColumnIndex;
}
void Permutation(int ColumnIndex[], int len, int index){
	if(index==len){		//完成一个排列
		if(Check(ColumnIndex,len)){			//检测当前排列对应的棋盘状态是否合法
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
			if( i - j == ColumnIndex[i] - ColumnIndex[j] || j - i == ColumnIndex[i] - ColumnIndex[j])   //在正、副对角线上  
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

	int queens=9;	//皇后数（也即棋盘格数目）
	EightQueen(queens);

	string str;
	cout<<"输入一个字符串（允许有重复字符）："<<endl;
	while(cin>>str){
		cout<<"排列算法1)："<<endl;
		vector<string> result = Permutation(str);
		for(vector<string>::const_iterator it=result.begin();it!=result.end();++it)
			cout<<(*it)<<"\t";
		cout<<endl;
		cout<<"排列算法2)："<<endl;
		vector<string> result2 = Permutation_non_recursion(str);
		for(vector<string>::const_iterator it=result2.begin();it!=result2.end();++it)
			cout<<(*it)<<"\t";
		cout<<endl;

		cout<<"组合算法1)："<<endl;
		vector<string> result3 = combination(str);
		for(vector<string>::const_iterator it=result3.begin();it!=result3.end();++it)
			cout<<(*it)<<"\t";
		cout<<endl;

		cout<<"组合算法2)："<<endl;
		vector<string> result4 = combination_binary(str);
		for(vector<string>::const_iterator it=result4.begin();it!=result4.end();++it)
			cout<<(*it)<<"\t";
		cout<<endl;

		cout<<"输入下一个字符串："<<endl;
		cin.clear();  cin.sync();
	}

	system("pause");
}
*/