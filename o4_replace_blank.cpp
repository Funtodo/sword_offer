#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
using namespace std;

//--Ҫ���滻�ַ����еĿո�
//void replaceSpace(char *str,int length)������length ��ʾ�����ַ�����str��������
class Solution {
public:
	//������0ͨ���ƶ�ԭstr���ݣ��Ӻ���ǰɨ�裬�����ո��޸Ŀո�Ϊ%20�����κ���2λ��
	//����ָ����������ȼ���ո�������ɨ�����Σ��ƶ�һ��
	//ʱ�临�Ӷ�Ϊ 0(n)
	void replaceSpace(char *str,int length) {
		if( str == "" || str == NULL || length <= 0)
			return;
		int count = 0; 								//����ո����
		char *loc = str + strlen(str)-1;
		while( loc>= str){
			if( *loc == ' ')
				count++;
			loc--;
		}
		if(strlen(str)+count*2 > length )
			return;								//������str����ĳ���

		loc = str + strlen(str); 				//û�м��� '\0'
		char *new_strp = loc + count*2; 		//ָ����չ�����һ���ַ�λ�ã�str��loc��new_strpָ�����ͬһ���ڴ�Ĳ�ͬλ�ã�
		*(new_strp+1) = '\0';  					//����ַ���������
		
		//ɨ��ڶ��飬�滻�ƶ��ַ���
		//while( loc >= str ){ 
		while( loc >= str && loc < new_strp){ //��locǰ��û�пո�Ͳ����ƶ������ˣ�����ʱnew_strp = loc
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

	//ͨ���ƶ�ԭstr���ݣ��Ӻ���ǰɨ�裬�����ո��޸Ŀո�Ϊ%20�����κ���2λ��
	//�����±��������ָ������ȼۣ�
	//ʱ�临�Ӷ�Ϊ o(n^2)
	void replaceSpace2(char *str,int length) {
		if( str == "" || str == NULL || length <= 0)
			return;
		//�Ӻ���ǰɨ�裬�滻ÿ���ո�
		int loc = strlen(str)-1;
		while( loc >= 0 ){
			if( str[loc] == ' ' ){
				for(int cp_loc = strlen(str); cp_loc>loc; cp_loc--) //�ƶ��İ��� '\0'
					str[cp_loc+2] = str[cp_loc];
				str[loc] = '%';
				str[loc+1] = '2';
				str[loc+2] = '0';
			}
			loc--;
		}
	}
	
	// ͨ���½�һ���ϴ��char���飬�޸ĵ���������ƻ�ԭ����str
	// ʱ�临�Ӷȡ��ռ临�Ӷȶ��ϸߣ����о����ԣ����Ǽ�
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
		// ���󣬣�ֻ���޸���strָ���λ�ã���û���޸�ԭstrָ���ַ��ֵ
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
	// ������������
	//char *str[7];  //�����������飬��str[0] = "we";�õ����ַ����鲻���޸ģ�const char *����
	char str0[] = " We Are Happy "; //ǰ���м��пո�
	char str1[] = "WeAreHappy"; //û�пո�
	char str2[] = "  We  Are   Happy  "; //ǰ���м��������ո�
	char str3[] = " "; //ֻ��һ���ո��ڼ���������ʾ type char[2],[0]'',[1]0;
	char str4[] = "   "; //ֻ�ж���ո�
	char str5[] = ""; //���ַ���
	cout<<"���ַ�������Ϊ��"<<strlen(str5)<<endl;
	//char str6[] = NULL; //��ָ��--������ʽ����ΪNULL���﷨����

	//-----------��Ҫ��-------------------
	//char strtest[] = "we"; strtest[0]='x'; // ok ==>char strtest[] = {'w','e','\0'};
	//char *strtest2 = "we"; strtest2[0]='x';// ��ַ����д�룬��Ϊ�˴��൱�� const char *strtest2 = " We Are Happy "��
	// ---�����ַ�������ֵ�����;��� const char ���͵����飡��---
	//(���Ը����ַ�������ֵ��ָ�븳ֵʱ�������const char *��������޸�)
	//------------------------------------

	int length = 500; //�ַ�����str���������������ֵ

	// ������� str ָ�루ָ��ĵ�ַ��������ں����ڲ��޸ĸ�ָ�루ָ����һ���ڴ棩�����������󣬲������޸�ԭstrָ���ֵ������ָ��ԭ���ĵ�ַ����
	// ������ȷ�����޸� str ָ��ָ����ǿ��ַ�����ݣ�
	test.test_example(str0, length);
	test.test_example(str1, length);
	test.test_example(str2, length);
	test.test_example(str3, length);
	test.test_example(str4, length);
	test.test_example(str5, length);
		
	system("pause");

	return 0;
}