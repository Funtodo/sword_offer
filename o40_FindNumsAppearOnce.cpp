#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;

//问题描述：一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。
//思路：如果一个整形数组只包含一个只出现一次的数字(其余都出现两次)，则可以依次异或数组中的元素，最后得到的结果即只出现一次的数字；
//     包含两个，则依次异或数组元素，结果一定不为0，按照异或结果的某一个不为0的位可将数组分为两组，每组恰好只包含一个只出现一次的数字，
//     依次异或每组，得到的即为两个只出现一次的数字；

//更赞的方式是引用 vector<int> &data,int &num1,int &num2
typedef vector<int>::const_iterator pIndex;
unsigned int FindFirstBitIs1(int num);
bool IsBit1(int num,unsigned int indexBit);
void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
	if(data.size()<2)
		return;

	int resultExclusiveOR = 0;
	for(pIndex it=data.begin();it!=data.end();++it)
		resultExclusiveOR ^= *it;

	unsigned int indexOf1 = FindFirstBitIs1(resultExclusiveOR);		//找到异或结果中第一个不为1的位
	//遍历原数组，若元素的indexOf1位为1，则异或num1； 为0，则异或num2；
	//相当于以indexOf1位将原数组分为两组，相同的数被分为一组，则两组中正好分别含一个只出现一次的数，，则每组元素依次异或得到的正好是该出现一次的数字
	*num1 = *num2 = 0;
	for(pIndex it=data.begin();it!=data.end();++it){
		if(IsBit1(*it,indexOf1))			//判断indexOf1位是否为1
			*num1 ^= *it;
		else
			*num2 ^= *it;
	}
}

//在整数num的二进制表示中找到最右边是1的位
unsigned int FindFirstBitIs1(int num){
	unsigned int indexBit = 0;
	while( (num & 1) == 0 && ( indexBit<8*sizeof(int) ) ){		//8*sizeof(int)--int对应的二进制位数; 2)(num & 1) == 0一定要加括号，== 优先于 &
		num = num>>1;		//右移一位
		++indexBit;
	}
	return indexBit;
}
//判断num的二进制表示中从右边数起的indexBit位是不是为1
bool IsBit1(int num,unsigned int indexBit){
	num = num>>indexBit;
	/*if( num & 1)	//傻代码
		return true;
	return false;  */
	return num & 1;
}

/*
int main(){
	vector<int> numbers;
	int temp,num1,num2;

	while(1){
		cin.clear();  cin.sync();
		numbers.clear();
		cout<<"输入整数数组(除了两个数字之外，其他的数字都出现了两次)："<<endl;
		while(cin>>temp){
			numbers.push_back(temp);
		}
		cout<<"只出现一次的两个数为:  ";
		FindNumsAppearOnce(numbers,&num1,&num2);	//如果为引用，FindNumsAppearOnce(numbers,num1,num2)
		cout<<num1<<"\t"<<num2<<endl<<endl;
	}
	system("pause");
}
*/
