#include "stdafx.h"
#include <iostream>
#include <queue>
using namespace std;

//思路：入栈==>往stack1里放；
//		出栈==>如果stack2为空，则将stack1的内容全部压入stack2（正好倒过来）后，从stack2出；如果stack2不为空，直接从stack2出；
class Solution
{
private:
    queue<int> queue1; // stack1
    queue<int> queue2;
public:
    void push(int node) {
		queue1.push(node);
		return;
    }

	//出栈，将queue1的元素都转到queue2，除最后一个元素外（最后一个元素即栈要弹出的元素）
	//如此之后，可将queue2的内容在全部转回queue1
	//（如果不这样，也可以每次判断哪个队列是空的，存元素往非空的队列存；取元素把非空队列元素除最后一个以外转到空队列，最后一个元素弹出）
    int pop() {
		int top = 0;
		if( queue1.empty() )
			return -1;	//暂且用-1表示栈中不存在元素
		while( queue1.size() > 1 ){
			queue2.push(queue1.front());
			queue1.pop();
		}
		top = queue1.front();
		queue1.pop();
		while( !queue2.empty() ){
			queue1.push(queue2.front());
			queue2.pop();
		}
		return top;
    }
};

/*
int main(){
	Solution testStack;
	cout<<testStack.pop()<<endl; //空队列 pop
	testStack.push(1);
	testStack.push(2);
	testStack.push(3);
	cout<<testStack.pop()<<endl;
	cout<<testStack.pop()<<endl;
	testStack.push(4);
	testStack.push(5);
	cout<<testStack.pop()<<endl;
	cout<<testStack.pop()<<endl;
	cout<<testStack.pop()<<endl;
	cout<<testStack.pop()<<endl; //空队列 pop
	testStack.push(6);
	testStack.push(7);
	cout<<testStack.pop()<<endl;
	cout<<testStack.pop()<<endl;
	//输出结果：-1,3,2,5,4,1,-1,7,6
	system("pause");
	return 0;
}
*/