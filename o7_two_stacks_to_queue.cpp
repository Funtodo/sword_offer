#include "stdafx.h"
#include <iostream>
#include <stack>
using namespace std;

//思路：入队列==>往stack1里放；
//		出队列==>如果stack2为空，则将stack1的内容全部压入stack2（正好倒过来）后，从stack2出；如果stack2不为空，直接从stack2出；
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
			return -1;	//暂且用-1表示队列中不存在元素
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
	cout<<testQueue.pop()<<endl; //空队列 pop
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
	cout<<testQueue.pop()<<endl; //空队列 pop
	testQueue.push(6);
	testQueue.push(7);
	cout<<testQueue.pop()<<endl;
	cout<<testQueue.pop()<<endl;
	//输出结果应该是，1~7按序的
	system("pause");
	return 0;
}
*/