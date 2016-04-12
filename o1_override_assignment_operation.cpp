#include"stdafx.h"
#include <iostream>
using namespace std;

// Ϊ���� CMystring ����� ��ֵ���㺯��
class CMystring{
public:
	CMystring(char* pData = NULL);
	CMystring(const CMystring& str);
	~CMystring(void);

	CMystring& operator= (const CMystring &str); //��ӵĸ�ֵ���㺯��
	void print(){ cout<<m_pData<<endl; };
private:
	char *m_pData;
};

/*
//���ظ�ֵ�����������Ҫע�⣺
//1)����ֵ��������Ϊ�����͵����ã�����֧��������ֵ��
//2)����Ĳ�����������Ϊ ����Ӧ�ã����ⲻ��Ҫ�ĸ��ƣ�
//3)���裺�жϴ���Ĳ����뵱ǰʵ���ǲ���ͬһ��ʵ����������ǣ����ͷ�ԭ�ڴ棬�ڷ������ڴ棬Ȼ���µ����ݸ��Ƶ��·�����ڴ�ռ䣻
//---ע�⣬һ��Ҫ�жϴ���Ĳ����뵱ǰ����ͬһ��ʵ���������ͷ��ڴ�ռ䣻
CMystring& CMystring::operator= (const CMystring& str){
	if( this == &str )
		return *this;

	delete []m_pData;
	m_pData = NULL;			//�������ʹ�ã���ֹʹ�����ͷŵ��ڴ�ռ�

	m_pData = new char[strlen(str.m_pData)+1];
	strcpy_s( m_pData, strlen(str.m_pData)+1, str.m_pData );	//�м����ָ�����Ƶĳ���

	return *this;
}
*/

//������ ���߳���ⷨ���ڵ����⣺��Υ�����쳣��ȫ��ԭ��
//�������ͷ�m_pData�ڴ�ռ䣬�ٷ����¿ռ䣬����¿ռ�����ʧ�ܣ�
//m_pData���ǿ�ָ�룬CMystringʵ�������ٱ��֡���Ч����״̬���ǳ����׵��³��������
//---�����÷������ȴ���һ����ʱʵ�����ٽ�����ʱʵ����ԭ����ʵ����
CMystring& CMystring::operator= (const CMystring& str){
	if( this != &str ){
		CMystring strTemp(str);			//���ø��ƹ��캯��
		char *pTemp = strTemp.m_pData;
		strTemp.m_pData = m_pData;
		m_pData = pTemp;
	}									//�˷�ʽ�ǳ����if�������strTemp�Զ����������������Զ��ͷ�ԭ�����m_pData�ռ�
	return *this;
}


CMystring::CMystring(char* pData){
	//m_pData = pData;
	if(pData==NULL){		// �˴�һ��Ҫ�жϴ����ʵ���Ƿ�Ϊ NULL
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

	copy = copy;	//�Լ����Լ���ֵ��
	copy.print();

	copy = test;	//��ֵ
	copy.print();

	CMystring copy2;
	CMystring copy3;
	copy3 = copy2 = copy = test;  //������ֵ
	copy.print();
	copy2.print();
	copy3.print();
	system("pause");
	return 0;
}
*/