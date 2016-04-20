//包含min函数的栈
//要求：定义栈的数据结构，要求在该类型中实现得到栈的最小元素的min函数；
//	   在该栈中，调用min、push及pop的时间复杂度都为O(1)

//思路：辅助栈；每次push，同时压入当前最小到辅助栈，即使最小没变也再次压入；
//			每次pop，同时弹出辅助栈栈顶； 
//			辅助栈栈顶即数据栈当前最小元素；


#include "stdafx.h"
#include <iostream>
#include <stack>
using namespace std;

//模板类
template <typename T> class StackWithMin{
public:
	void push(const T &value);
	void pop();
	const T& top() const; 
	const T& min() const;		//const函数
private:
	stack<T> m_data;			//数据栈
	stack<T> m_min;				//辅助栈，存放每次push当前最小元素，栈顶为当前数据栈中最小元素
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