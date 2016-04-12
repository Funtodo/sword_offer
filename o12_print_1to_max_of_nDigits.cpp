#include"stdafx.h"
#include<iostream>
using namespace std;

/*问题描述：输入数字n，按顺序打印出从1到最大的n位十进制数；
  例如，输入3，打印1、2、3……999；
  关键点：大数问题【表达一个大数，最常用的方法是用字符串或者数组表达大数，在字符串或数组上模拟所需要的运算】
*/

//------------------------------------------------------------------------------
//---方法1：用字符串模拟加法，将字符串表达的数字打印出来-----------
//------------------------------------------------------------------------------
bool Increment(char *number);
void PrintNumber(const char *number);
void Print1ToMaxOfNDigits(int n){
	if( n == 0)
		return;

	char *number = new char[n+1];
	//memset(number,0,n);  //错误，，number是char*，存储 char ‘0’
	memset(number,'0',n);
	number[n] = '\0';

	while( !Increment(number) ){			//number字符串表示的数字做自增运算
		PrintNumber(number);		//打印数字
	}

	delete []number;				//养成好习惯，，动态生成，记得手动delete
}
bool Increment(char *number){
	bool isOverflow = false;
	int nTakeOver = 0;
	int nLength = strlen(number);
	for(int i=nLength-1; i>=0; --i){
		if( i== nLength-1 )				//最后一位，自增1
			nTakeOver = 1;
		int nSum = number[i] - '0' + nTakeOver;
		if( nSum>9 ){					//产生进位
			if( i==0 ){					//第0位产生进位
				isOverflow = true;
			}
			nTakeOver = 1;
			nSum -= 10;
			number[i] = nSum + '0';			//转换为字符
		}
		else{								//没有产生进位，则计算完毕
			number[i] = nSum + '0';			
			break;
		}
	}
	return isOverflow;
}
//打印字符串数组表示的数组，不打印前面的0
void PrintNumber(const char *number){
	bool isBegining0 = true;						//是否仍为开头的0位
	for(int i=0;i<strlen(number);++i){
		if( isBegining0 && number[i]!='0' )			//找到第一个非'0'，置isBegining0为false
			isBegining0 = false;
		if( !isBegining0 )							//不是开头的0位，都得打印
			cout<<number[i];
	}
	if(!isBegining0)	//0不打印，也不打印“、”
		cout<<"、";
}

//------------------------------------------------------------------------------
//-----方法2：将打印的数字看成n位0~9数字的排列，只是当前面为0时不打印-----------
//采用递归的方式依次设置n位字符数组的数字，当最后一位设置完成时，打印字符数组代表的数字
//------------------------------------------------------------------------------
void SetLeftDigits(char *number,const int n,int lastIndex);
void Print1ToMaxOfNDigits2(int n){
	if(n==0)
		return;
	char *number = new char[n+1];
	number[n] = '\0';

	for(int i=0;i<=9;++i){
		number[0] = i + '0';			//将第0位依次设置为0~9
		SetLeftDigits(number,n,0);				//设置剩下的位数并打印
	}
	delete []number;
}
//设置剩下的位置，当最后一位设置完成时，打印
//输入：字符数组number，数组位数n，上一次设置的位置lastIndex
void SetLeftDigits(char *number,const int n,int lastIndex){
	if(lastIndex==n-1){					//上一次已经设置了最后一位
		PrintNumber(number);
		return;
	}
	for(int i=0;i<=9;++i){				//设置剩下的位置
		number[lastIndex+1] = i + '0';
		SetLeftDigits(number,n,lastIndex+1);
	}
}

//------------------------------------------------------------------------------
//---扩展，实现两个任意整数的加法；只考虑正数的情况
//---由于没有限定输入的数的大小范围，要当做大数问题来处理，用字符串数组表示数字，并模拟加法
//--用STL实现，string，algorithm--
//--思路：1.反转两个字符串，便于从低位到高位相加；
//		 2.加和结果最大长度为max(len1,len2)+1，将两个字符串补齐为结果字符串长度（补'0'）;
//		 3.把两个字符串相加，一位一位的加并加上进位；结果反序输出，且不输出高位0；
//------------------------------------------------------------------------------
#include<string>
#include <algorithm>
string reversalAndFillUp0(const string &str, int maxLen);
string SumTwoAnyInteger(const string &add1,const string &add2){
	int len1 = add1.size();
	int len2 = add2.size();
	int lenSum = max(len1,len2) + 1;							//+1，要比最大的加数多一位，防止溢出
	string rAdd1 = reversalAndFillUp0(add1,lenSum);				//反转字符串，使字符串的低位对应整数的地位，方便计算
	string rAdd2 = reversalAndFillUp0(add2,lenSum);				//同时，将整数字符串高位补充0，补为和结果可能的位数相同
	//cout<<rAdd1<<endl<<rAdd2<<endl;
	
	//----先只考虑正数的情况-----
	string sum(lenSum,'0');
	int isTakeOver = 0;
	for(int i=0;i<lenSum;++i){
		int curNumber = (rAdd1[i]-'0') + (rAdd2[i]-'0') + isTakeOver;
		if(curNumber>9){
			isTakeOver = 1;
			curNumber -= 10;
		}else{						//！！没有进位，置isTakeOver为0
			isTakeOver = 0;				
		}
		sum[i] = curNumber + '0';
	}

	return sum;
}
string reversalAndFillUp0(const string &str, int maxLen){
	string rStr(str);						//复制构造函数，拷贝一份
	reverse(rStr.begin(), rStr.end());		//反转
	rStr.append(maxLen-str.size(),'0');		//如果短于maxLen，添加'0'
	return rStr;
}

//低位表示数字的低位，因此要逆序打印，且高位多余的0不用打印---最多只有1个0？
void PrintReversalNumber(const string &str){
	if(str.empty())
		return;
	bool isBegining0 = true;
	for(int i=str.size()-1; i>=0; --i ){
		if(isBegining0 && str[i]!='0'){
			isBegining0 = false;
		}
		if( !isBegining0 )
			cout<<str[i];
	}
}

/*
int main(){
	int n;
	cout<<"输入要打印的整数位数n"<<endl;
	while(cin>>n){
		Print1ToMaxOfNDigits(n);
		cout<<endl<<"222---------222"<<endl;
		Print1ToMaxOfNDigits2(n);
		cout<<endl<<"---------"<<endl;
	}
	
	cin.clear(); cin.sync();		//清除错误信息，并清除缓冲区
	cout<<"输入两个整数（暂时只考虑不带+号的正数）："<<endl;
	//-----char*字符串初始化------------------------------------------
	//char* 型字符串要声明时初始化，直接指向字符串字面值，或者分配长度，，
	//char *add1;						
	//cin.get(add1,2);			//会出错：使用未初始化变量
	//cin>>add1;
	//----------------------------------------------------------------

	string add1,add2,sum;
	while(cin>>add1>>add2){
		sum = SumTwoAnyInteger(add1,add2);
		cout<<add1<<"+";
		cout<<add2<<"=";
		PrintReversalNumber(sum); cout<<endl;
	}
	return 0;
}
*/