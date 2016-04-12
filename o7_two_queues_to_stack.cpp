#include "stdafx.h"
#include <iostream>
#include <queue>
using namespace std;

//˼·����ջ==>��stack1��ţ�
//		��ջ==>���stack2Ϊ�գ���stack1������ȫ��ѹ��stack2�����õ��������󣬴�stack2�������stack2��Ϊ�գ�ֱ�Ӵ�stack2����
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

	//��ջ����queue1��Ԫ�ض�ת��queue2�������һ��Ԫ���⣨���һ��Ԫ�ؼ�ջҪ������Ԫ�أ�
	//���֮�󣬿ɽ�queue2��������ȫ��ת��queue1
	//�������������Ҳ����ÿ���ж��ĸ������ǿյģ���Ԫ�����ǿյĶ��д棻ȡԪ�ذѷǿն���Ԫ�س����һ������ת���ն��У����һ��Ԫ�ص�����
    int pop() {
		int top = 0;
		if( queue1.empty() )
			return -1;	//������-1��ʾջ�в�����Ԫ��
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
	cout<<testStack.pop()<<endl; //�ն��� pop
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
	cout<<testStack.pop()<<endl; //�ն��� pop
	testStack.push(6);
	testStack.push(7);
	cout<<testStack.pop()<<endl;
	cout<<testStack.pop()<<endl;
	//��������-1,3,2,5,4,1,-1,7,6
	system("pause");
	return 0;
}
*/