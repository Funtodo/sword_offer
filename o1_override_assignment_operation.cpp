#include"stdafx.h"
#include <iostream>
using namespace std;

// 为如下 CMystring 类添加 赋值运算函数
class CMystring{
public:
	CMystring(char* pData = NULL);
	CMystring(const CMystring& str);
	~CMystring(void);

	CMystring& operator= (const CMystring &str); //添加的赋值运算函数
	void print(){ cout<<m_pData<<endl; };
private:
	char *m_pData;
};

/*
//重载赋值运算符函数，要注意：
//1)返回值类型声明为该类型的引用，用以支持连续赋值；
//2)传入的参数类型声明为 常量应用，避免不必要的复制；
//3)步骤：判断传入的参数与当前实例是不是同一个实例，如果不是，先释放原内存，在分配新内存，然后将新的内容复制到新分配的内存空间；
//---注意，一定要判断传入的参数与当前不是同一个实例，才能释放内存空间；
CMystring& CMystring::operator= (const CMystring& str){
	if( this == &str )
		return *this;

	delete []m_pData;
	m_pData = NULL;			//最好配套使用，防止使用已释放的内存空间

	m_pData = new char[strlen(str.m_pData)+1];
	strcpy_s( m_pData, strlen(str.m_pData)+1, str.m_pData );	//中间参数指定复制的长度

	return *this;
}
*/

//！！！ 上诉常规解法存在的问题：【违背了异常安全性原则】
//即，先释放m_pData内存空间，再分配新空间，如果新空间申请失败，
//m_pData将是空指针，CMystring实例将不再保持“有效”的状态，非常容易导致程序崩溃；
//---建议用法：【先创建一个临时实例，再交换临时实例和原来的实例】
CMystring& CMystring::operator= (const CMystring& str){
	if( this != &str ){
		CMystring strTemp(str);			//调用复制构造函数
		char *pTemp = strTemp.m_pData;
		strTemp.m_pData = m_pData;
		m_pData = pTemp;
	}									//此方式非常巧妙，if块结束后，strTemp自动调用析构函数，自动释放原对象的m_pData空间
	return *this;
}


CMystring::CMystring(char* pData){
	//m_pData = pData;
	if(pData==NULL){		// 此处一定要判断传入的实参是否为 NULL
		m_pData = NULL;
		return;
	}
	m_pData = new char[strlen(pData)+1];
	strcpy_s(m_pData,strlen(pData)+1,pData);
}
CMystring::CMystring(const CMystring& str){
	m_pData = new char[strlen(str.m_pData)+1];
	strcpy_s(m_pData,strlen(str.m_pData)+1,str.m_pData);
}
CMystring::~CMystring(void){
	delete []m_pData; 
};

/*
int main()
{
	cout << "Hello world!" << endl;
	CMystring test("test");
	test.print();
	CMystring copy("test_copy");
	copy.print();

	copy = copy;	//自己给自己赋值；
	copy.print();

	copy = test;	//赋值
	copy.print();

	CMystring copy2;
	CMystring copy3;
	copy3 = copy2 = copy = test;  //连续赋值
	copy.print();
	copy2.print();
	copy3.print();
	system("pause");
	return 0;
}
*/