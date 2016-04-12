#include "stdafx.h"
#include <iostream>
#include <stack>
using namespace std;

//˼·�������==>��stack1��ţ�
//		������==>���stack2Ϊ�գ���stack1������ȫ��ѹ��stack2�����õ��������󣬴�stack2�������stack2��Ϊ�գ�ֱ�Ӵ�stack2����
class Solution
{
private:
    stack<int> stack1; // stack1
    stack<int> stack2;
public:
    void push(int node) {
		stack1.push(node);
		return;
    }

    int pop() {
		int top = 0;
		if( stack2.empty() && stack1.empty() )
			return -1;	//������-1��ʾ�����в�����Ԫ��
		if( stack2.empty() ){
			while( !stack1.empty() ){
				top = stack1.top();
				stack1.pop();
				stack2.push(top);
			}
		}
		top = stack2.top();
		stack2.pop();
		return top;
		
    }
};
/*
int main(){
	Solution testQueue;
	cout<<testQueue.pop()<<endl; //�ն��� pop
	testQueue.push(1);
	testQueue.push(2);
	testQueue.push(3);
	cout<<testQueue.pop()<<endl;
	cout<<testQueue.pop()<<endl;
	testQueue.push(4);
	testQueue.push(5);
	cout<<testQueue.pop()<<endl;
	cout<<testQueue.pop()<<endl;
	cout<<testQueue.pop()<<endl;
	cout<<testQueue.pop()<<endl; //�ն��� pop
	testQueue.push(6);
	testQueue.push(7);
	cout<<testQueue.pop()<<endl;
	cout<<testQueue.pop()<<endl;
	//������Ӧ���ǣ�1~7�����
	system("pause");
	return 0;
}
*/