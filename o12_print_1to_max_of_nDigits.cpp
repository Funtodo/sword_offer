#include"stdafx.h"
#include<iostream>
using namespace std;

/*������������������n����˳���ӡ����1������nλʮ��������
  ���磬����3����ӡ1��2��3����999��
  �ؼ��㣺�������⡾���һ����������õķ��������ַ���������������������ַ�����������ģ������Ҫ�����㡿
*/

//------------------------------------------------------------------------------
//---����1�����ַ���ģ��ӷ������ַ����������ִ�ӡ����-----------
//------------------------------------------------------------------------------
bool Increment(char *number);
void PrintNumber(const char *number);
void Print1ToMaxOfNDigits(int n){
	if( n == 0)
		return;

	char *number = new char[n+1];
	//memset(number,0,n);  //���󣬣�number��char*���洢 char ��0��
	memset(number,'0',n);
	number[n] = '\0';

	while( !Increment(number) ){			//number�ַ�����ʾ����������������
		PrintNumber(number);		//��ӡ����
	}

	delete []number;				//���ɺ�ϰ�ߣ�����̬���ɣ��ǵ��ֶ�delete
}
bool Increment(char *number){
	bool isOverflow = false;
	int nTakeOver = 0;
	int nLength = strlen(number);
	for(int i=nLength-1; i>=0; --i){
		if( i== nLength-1 )				//���һλ������1
			nTakeOver = 1;
		int nSum = number[i] - '0' + nTakeOver;
		if( nSum>9 ){					//������λ
			if( i==0 ){					//��0λ������λ
				isOverflow = true;
			}
			nTakeOver = 1;
			nSum -= 10;
			number[i] = nSum + '0';			//ת��Ϊ�ַ�
		}
		else{								//û�в�����λ����������
			number[i] = nSum + '0';			
			break;
		}
	}
	return isOverflow;
}
//��ӡ�ַ��������ʾ�����飬����ӡǰ���0
void PrintNumber(const char *number){
	bool isBegining0 = true;						//�Ƿ���Ϊ��ͷ��0λ
	for(int i=0;i<strlen(number);++i){
		if( isBegining0 && number[i]!='0' )			//�ҵ���һ����'0'����isBegining0Ϊfalse
			isBegining0 = false;
		if( !isBegining0 )							//���ǿ�ͷ��0λ�����ô�ӡ
			cout<<number[i];
	}
	if(!isBegining0)	//0����ӡ��Ҳ����ӡ������
		cout<<"��";
}

//------------------------------------------------------------------------------
//-----����2������ӡ�����ֿ���nλ0~9���ֵ����У�ֻ�ǵ�ǰ��Ϊ0ʱ����ӡ-----------
//���õݹ�ķ�ʽ��������nλ�ַ���������֣������һλ�������ʱ����ӡ�ַ�������������
//------------------------------------------------------------------------------
void SetLeftDigits(char *number,const int n,int lastIndex);
void Print1ToMaxOfNDigits2(int n){
	if(n==0)
		return;
	char *number = new char[n+1];
	number[n] = '\0';

	for(int i=0;i<=9;++i){
		number[0] = i + '0';			//����0λ��������Ϊ0~9
		SetLeftDigits(number,n,0);				//����ʣ�µ�λ������ӡ
	}
	delete []number;
}
//����ʣ�µ�λ�ã������һλ�������ʱ����ӡ
//���룺�ַ�����number������λ��n����һ�����õ�λ��lastIndex
void SetLeftDigits(char *number,const int n,int lastIndex){
	if(lastIndex==n-1){					//��һ���Ѿ����������һλ
		PrintNumber(number);
		return;
	}
	for(int i=0;i<=9;++i){				//����ʣ�µ�λ��
		number[lastIndex+1] = i + '0';
		SetLeftDigits(number,n,lastIndex+1);
	}
}

//------------------------------------------------------------------------------
//---��չ��ʵ���������������ļӷ���ֻ�������������
//---����û���޶���������Ĵ�С��Χ��Ҫ���������������������ַ��������ʾ���֣���ģ��ӷ�
//--��STLʵ�֣�string��algorithm--
//--˼·��1.��ת�����ַ��������ڴӵ�λ����λ��ӣ�
//		 2.�Ӻͽ����󳤶�Ϊmax(len1,len2)+1���������ַ�������Ϊ����ַ������ȣ���'0'��;
//		 3.�������ַ�����ӣ�һλһλ�ļӲ����Ͻ�λ���������������Ҳ������λ0��
//------------------------------------------------------------------------------
#include<string>
#include <algorithm>
string reversalAndFillUp0(const string &str, int maxLen);
string SumTwoAnyInteger(const string &add1,const string &add2){
	int len1 = add1.size();
	int len2 = add2.size();
	int lenSum = max(len1,len2) + 1;							//+1��Ҫ�����ļ�����һλ����ֹ���
	string rAdd1 = reversalAndFillUp0(add1,lenSum);				//��ת�ַ�����ʹ�ַ����ĵ�λ��Ӧ�����ĵ�λ���������
	string rAdd2 = reversalAndFillUp0(add2,lenSum);				//ͬʱ���������ַ�����λ����0����Ϊ�ͽ�����ܵ�λ����ͬ
	//cout<<rAdd1<<endl<<rAdd2<<endl;
	
	//----��ֻ�������������-----
	string sum(lenSum,'0');
	int isTakeOver = 0;
	for(int i=0;i<lenSum;++i){
		int curNumber = (rAdd1[i]-'0') + (rAdd2[i]-'0') + isTakeOver;
		if(curNumber>9){
			isTakeOver = 1;
			curNumber -= 10;
		}else{						//����û�н�λ����isTakeOverΪ0
			isTakeOver = 0;				
		}
		sum[i] = curNumber + '0';
	}

	return sum;
}
string reversalAndFillUp0(const string &str, int maxLen){
	string rStr(str);						//���ƹ��캯��������һ��
	reverse(rStr.begin(), rStr.end());		//��ת
	rStr.append(maxLen-str.size(),'0');		//�������maxLen�����'0'
	return rStr;
}

//��λ��ʾ���ֵĵ�λ�����Ҫ�����ӡ���Ҹ�λ�����0���ô�ӡ---���ֻ��1��0��
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
	cout<<"����Ҫ��ӡ������λ��n"<<endl;
	while(cin>>n){
		Print1ToMaxOfNDigits(n);
		cout<<endl<<"222---------222"<<endl;
		Print1ToMaxOfNDigits2(n);
		cout<<endl<<"---------"<<endl;
	}
	
	cin.clear(); cin.sync();		//���������Ϣ�������������
	cout<<"����������������ʱֻ���ǲ���+�ŵ���������"<<endl;
	//-----char*�ַ�����ʼ��------------------------------------------
	//char* ���ַ���Ҫ����ʱ��ʼ����ֱ��ָ���ַ�������ֵ�����߷��䳤�ȣ���
	//char *add1;						
	//cin.get(add1,2);			//�����ʹ��δ��ʼ������
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