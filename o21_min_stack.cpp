//����min������ջ
//Ҫ�󣺶���ջ�����ݽṹ��Ҫ���ڸ�������ʵ�ֵõ�ջ����СԪ�ص�min������
//	   �ڸ�ջ�У�����min��push��pop��ʱ�临�Ӷȶ�ΪO(1)

//˼·������ջ��ÿ��push��ͬʱѹ�뵱ǰ��С������ջ����ʹ��Сû��Ҳ�ٴ�ѹ�룻
//			ÿ��pop��ͬʱ��������ջջ���� 
//			����ջջ��������ջ��ǰ��СԪ�أ�


#include "stdafx.h"
#include <iostream>
#include <stack>
using namespace std;

//ģ����
template <typename T> class StackWithMin{
public:
	void push(const T &value);
	void pop();
	const T& top() const; 
	const T& min() const;		//const����
private:
	stack<T> m_data;			//����ջ
	stack<T> m_min;				//����ջ�����ÿ��push��ǰ��СԪ�أ�ջ��Ϊ��ǰ����ջ����СԪ��
};

template <typename T>
void StackWithMin<T>::push(const T &value){
	m_data.push(value);
	if(m_min.size()==0 || value < m_min.top())
		m_min.push(value);
	else
		m_min.push(m_min.top());
}
template <typename T>
void StackWithMin<T>::pop(){
	//assert(m_data.size()>0 && m_min.size()>0);
	
	m_data.pop();
	m_min.pop();
}
template <typename T>
const T& StackWithMin<T>::top() const{
	//assert(m_data.size()>0 && m_min.size()>0);
	return m_data.top();
}
template <typename T>
const T& StackWithMin<T>::min() const{
	//assert(m_data.size()>0 && m_min.size()>0);
	return m_min.top();
}

/*
int main(){
	StackWithMin<int> testStack;
	testStack.push(3);
	cout<<testStack.min()<<" (expect 3)"<<endl;
	testStack.push(5);
	cout<<testStack.min()<<" (expect 3)"<<endl;
	testStack.push(1);
	cout<<testStack.min()<<" (expect 1)"<<endl;
	testStack.pop();
	cout<<testStack.min()<<" (expect 3)"<<endl;
	testStack.pop();
	cout<<testStack.min()<<" (expect 3)"<<endl;
	system("pause");
}
*/