#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
using namespace std;

//--要求，替换字符串中的空格；
//void replaceSpace(char *str,int length)，其中length 表示给定字符数组str的总容量
class Solution {
public:
	//！！！0通过移动原str内容（从后往前扫描，碰到空格，修改空格为%20，依次后移2位）
	//采用指针操作，且先计算空格数，即扫描两次，移动一次
	//时间复杂度为 0(n)
	void replaceSpace(char *str,int length) {
		if( str == "" || str == NULL || length <= 0)
			return;
		int count = 0; 								//计算空格个数
		char *loc = str + strlen(str)-1;
		while( loc>= str){
			if( *loc == ' ')
				count++;
			loc--;
		}
		if(strlen(str)+count*2 > length )
			return;								//超过了str允许的长度

		loc = str + strlen(str); 				//没有计算 '\0'
		char *new_strp = loc + count*2; 		//指向扩展后最后一个字符位置（str，loc，new_strp指向的是同一块内存的不同位置）
		*(new_strp+1) = '\0';  					//添加字符串结束符
		
		//扫描第二遍，替换移动字符串
		//while( loc >= str ){ 
		while( loc >= str && loc < new_strp){ //当loc前面没有空格就不用移动复制了，即此时new_strp = loc
			if( *loc == ' '){
				*(new_strp--) = '0';
				*(new_strp--) = '2';
				*(new_strp--) = '%';
				loc--;
			}else{
				*(new_strp--) = *(loc--);
			}
		}
	}

	//通过移动原str内容（从后往前扫描，碰到空格，修改空格为%20，依次后移2位）
	//采用下标操作（和指针操作等价）
	//时间复杂度为 o(n^2)
	void replaceSpace2(char *str,int length) {
		if( str == "" || str == NULL || length <= 0)
			return;
		//从后往前扫描，替换每个空格
		int loc = strlen(str)-1;
		while( loc >= 0 ){
			if( str[loc] == ' ' ){
				for(int cp_loc = strlen(str); cp_loc>loc; cp_loc--) //移动的包括 '\0'
					str[cp_loc+2] = str[cp_loc];
				str[loc] = '%';
				str[loc+1] = '2';
				str[loc+2] = '0';
			}
			loc--;
		}
	}
	
	// 通过新建一个较大的char数组，修改到该数组后复制回原数组str
	// 时间复杂度、空间复杂度都较高，且有局限性；但是简单
	void replaceSpace1(char *str,int length) {
		if( str == "" || str == NULL || length <= 0)
			return;
		char resultStr[1024];
		int loc = 0;
		for (unsigned int i = 0; i < strlen(str); ++i){
			if(str[i] != ' '){
				resultStr[loc++] = str[i];
			}else{
				resultStr[loc++] = '%';
				resultStr[loc++] = '2';
				resultStr[loc++] = '0';
			}
		}
		// 错误，，只是修改了str指向的位置，并没有修改原str指向地址的值
		//resultStr[loc] = '\0';
		//str = resultStr;
		for (int i = 0; i < loc; ++i)
        {
            str[i] = resultStr[i];
        }
        str[loc] = '\0';
	}

	void test_example( char *str, int length){
		cout<<"origin string: "<<str<<'\t';
		replaceSpace(str, length);
		cout<<"changed: "<<str<<endl;
	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	Solution test;
	// 建立测试样例
	//char *str[7];  //测试样例数组，用str[0] = "we";得到的字符数组不可修改，const char *类型
	char str0[] = " We Are Happy "; //前后，中间有空格
	char str1[] = "WeAreHappy"; //没有空格
	char str2[] = "  We  Are   Happy  "; //前后，中间有连续空格
	char str3[] = " "; //只有一个空格，在监视器中显示 type char[2],[0]'',[1]0;
	char str4[] = "   "; //只有多个空格
	char str5[] = ""; //空字符串
	cout<<"空字符串长度为："<<strlen(str5)<<endl;
	//char str6[] = NULL; //空指针--这种形式不能为NULL，语法错误

	//-----------重要！-------------------
	//char strtest[] = "we"; strtest[0]='x'; // ok ==>char strtest[] = {'w','e','\0'};
	//char *strtest2 = "we"; strtest2[0]='x';// 地址不可写入，因为此处相当于 const char *strtest2 = " We Are Happy "；
	// ---！！字符串字面值的类型就是 const char 类型的数组！！---
	//(所以给用字符串字面值给指针赋值时，最好用const char *以免错误修改)
	//------------------------------------

	int length = 500; //字符数组str最大容量，随便给定值

	// 传入的是 str 指针（指向的地址），如果在函数内部修改该指针（指向另一块内存），函数结束后，并不会修改原str指针的值（还是指向原来的地址）；
	// 所以正确的是修改 str 指针指向的那块地址的内容；
	test.test_example(str0, length);
	test.test_example(str1, length);
	test.test_example(str2, length);
	test.test_example(str3, length);
	test.test_example(str4, length);
	test.test_example(str5, length);
		
	system("pause");

	return 0;
}