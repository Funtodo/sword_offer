#include "stdafx.h"
#include <iostream>
#include <stack>
using namespace std;

//typedef ListNode *pNode;
struct ListNode{
	int value;
	ListNode *pNext;
};

class MyList{
private:
	ListNode *pHead; //链表头指针,指向第一个节点
	// ListNode **pNode; //错误，如果这样，如何初始化？pNode=NULL？错，随后*pNode=pNew将写0地址；*pNode=NULL，初始化的**pHead是0xccccc,该地址不可写
	void PrintListReversingly_recursion(ListNode *pHead);
public:
	//void AddToTail(ListNode **pHead, int value); //添加数据；当不用对象形式写时，要传入头指针的地址 &pNode即 **pHead（具体见非对象版的list实现）
	void AddToTail(int value); //添加数据,由于定义的类，不需要传入头指针参数，并且对pHead的修改会保留
	void RemoveNode(int value); //移除第一个为value的node

	void PrintListReversingly(); //反向打印list
	void PrintListReversingly2(); //版本2
	void printList(); //正常打印list（正向)

	MyList(){
		pHead = NULL;
	}
	~MyList();  ///节点通过new生成，要负责任的回收所有节点内存
};
MyList::~MyList(){
	if(pHead = NULL)
		return;
	ListNode *pNode = NULL;
	while(pHead!=NULL){
		pNode = pHead;
		pHead = pHead->pNext;
		delete pNode;
	}
	pNode = NULL;
	if(pHead==NULL)
		cout<<"Now list is emptied!"<<endl;
}
void MyList::AddToTail(int value){
	//错误，因为此处newNode是临时变量，当函数运行结束，会释放此变量占的内存空间，则指向该节点会出错；
	//ListNode pNew;	pNew.value = value; 	pNew.pNext = NULL;
	//此处应该用动态内存分配
	ListNode *pNew = new ListNode;
	pNew->value = value;
	pNew->pNext = NULL;
	
	if( pHead == NULL){
		pHead = pNew;
		return;
	}
	ListNode *pNode = pHead;
	while(pNode->pNext != NULL)
		pNode = pNode->pNext;
	pNode->pNext = pNew;
}

void MyList::RemoveNode(int value){
	if(pHead == NULL)
		return;
	ListNode *pToRemoved = NULL;
	if(pHead->value == value){ //删除第一个节点，会更改pHead
		pToRemoved = pHead;
		//pHead = NULL; //!--!不合理，否则要对只有一个节点和有多个节点分别做处理
		pHead = pHead->pNext; //--!---如果只有一个节点，pHead->pNext = NULL，，如果有多个节点，pHead->pNext指向被删除节点的下一个节点
	}else{
		ListNode *pNode = pHead;
		while( pNode->pNext!=NULL && pNode->pNext->value != value) // -!- pNode->pNext!=NULL 条件要在前？？
			pNode = pNode->pNext;
		if( pNode->pNext!=NULL){
			pToRemoved = pNode->pNext;
			pNode->pNext = pNode->pNext->pNext;
		}
	}
	if(pToRemoved != NULL ){ //--！！！---重要，判断是否有要删除的节点
		delete pToRemoved;
		pToRemoved = NULL; //记得置为NULL，防止对已释放的内存空间访问
	}
}

//递归版本---
void MyList::PrintListReversingly2(){
	if(pHead == NULL){
		cout<<"empty list!"<<endl;
		return;
	}
	cout<<"<==";
	PrintListReversingly_recursion(pHead);
	cout<<endl;
}
void MyList::PrintListReversingly_recursion(ListNode *pHead){
	ListNode *pNode = pHead;
	//while(pNode->pNext != NULL){ //--！！！！-递归是不需要循环的（会造成无限递归死循环）！！！！
	if(pNode->pNext != NULL) //存在下一个节点时，先输出下一个节点
		PrintListReversingly_recursion(pNode->pNext);
	cout<<pNode->value<<" "; //输出当前节点
}

//使用栈----
void MyList::PrintListReversingly(){
	if(pHead == NULL){
		cout<<"empty list!"<<endl;
		return;
	}
	stack<ListNode *> nodes;
	ListNode *pNode = pHead;
	cout<<"<==";
	while( pNode!=NULL ){
		nodes.push(pNode);
		pNode = pNode->pNext ;
	}
	while( ! nodes.empty()){
		cout<<(nodes.top())->value<<" ";
		nodes.pop();
	}
	cout<<endl;
}

void MyList::printList(){
	if(pHead == NULL){
		cout<<"empty list!"<<endl;
		return;
	}
	ListNode *pNode = pHead;
	cout<<"==>";
	while(pNode != NULL){
		cout<<pNode->value<<' ';
		pNode = pNode->pNext;
	}
	cout<<endl;
}

/*
int main(){
	{
	MyList myList;	//定义一个对象，调用默认构造函数或无参构造函数；myList.AAddToTail(0)
	//MyList *myList = new MyList; // new返回对象的指针；myList->AAddToTail(0) 或 (*myList).AddToTail(0);
	// 测试：
	myList.RemoveNode(2); //测试：链表为空时删除
	myList.printList(); myList.PrintListReversingly();  // 正向反向打印

	myList.AddToTail(1);	//测试：添加第一个节点；
	myList.printList(); myList.PrintListReversingly();  // 正向反向打印

	myList.RemoveNode(1);	//测试：只有一个节点时删除；
	myList.printList(); myList.PrintListReversingly();  // 正向反向打印

	myList.AddToTail(1);	//测试：删除后添加第一个节点；
	myList.printList(); myList.PrintListReversingly();  // 正向反向打印

	myList.AddToTail(2);	//测试：添加；
	myList.printList(); myList.PrintListReversingly();  // 正向反向打印

	myList.AddToTail(3);	//测试：添加；
	myList.printList(); myList.PrintListReversingly();  // 正向反向打印

	myList.AddToTail(4);	//测试：添加；
	myList.printList(); myList.PrintListReversingly();  // 正向反向打印

	myList.AddToTail(5);	//测试：添加；
	myList.printList(); myList.PrintListReversingly();  // 正向反向打印

	myList.AddToTail(6);	//测试：添加；
	myList.printList(); myList.PrintListReversingly();  // 正向反向打印

	myList.RemoveNode(1);	//测试：删除开头
	myList.printList(); myList.PrintListReversingly();  // 正向反向打印

	myList.RemoveNode(4);	//测试：删除中间
	myList.printList(); myList.PrintListReversingly();  // 正向反向打印

	myList.RemoveNode(6);	//测试：删除最后
	myList.printList(); myList.PrintListReversingly();  // 正向反向打印
	} //括起来，只是为了看析构函数输出
	system("pause");
	return 0;
}
//*/