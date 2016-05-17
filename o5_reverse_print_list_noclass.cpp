#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//牛客网上要求形式;要求返回数组，数组值为 链表从尾到头的值

//typedef ListNode *pNode;
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :val(x), next(NULL) {	}
};

//反向打印，结果输出到vector；

//先正向输出到zhVector，再从后向前扫描zhVector，并将值复制到fanVector
//空间复杂度 2n，时间复杂度也为 2n
//返回 vector<int> 这种形式，，似乎用不了递归，，
vector<int> printListFromTailToHead2(struct ListNode* head) {
	vector<int> zhVector;
	ListNode *pNode = head;
	while(pNode!=NULL){
		zhVector.push_back(pNode->val);
		pNode = pNode->next;
	}
	vector<int> fanVector;
	//错误 zhVector.end() 只能作为哨兵，，当zhVector为空时，报错
	//for(vector<int>::iterator iter = zhVector.end()-1;
	//	    iter >= zhVector.begin(); --iter){
	//		fanVector.push_back( *iter );
	//}
	for(int i=zhVector.size()-1; i>=0; --i){
		fanVector.push_back( zhVector[i] );
	}
	return fanVector;
}
//使用栈
vector<int> printListFromTailToHead(struct ListNode* head) {
	stack<struct ListNode*> st;
	ListNode *pNode = head;
	while(pNode!=NULL){
		st.push(pNode);
		pNode = pNode->next;
	}
	vector<int> fanVector;
	while(st.size()!=0){
		fanVector.push_back(st.top()->val);
		st.pop();
	}
	return fanVector;
}
//正常打印，结果输出到vector
vector<int> printListFromHeadToTail(struct ListNode* head){
	vector<int> zhVector;
	ListNode *pNode = head;
	while(pNode!=NULL){
		zhVector.push_back(pNode->val);
		pNode = pNode->next;
	}
	return zhVector;
}
//正反打印
void printListZF(struct ListNode* head) {
	vector<int> zhVector;
	vector<int> fanVector;
	zhVector = printListFromHeadToTail(head);
	fanVector =  printListFromTailToHead(head);
	cout<<"==>";
	for(vector<int>::iterator iter = zhVector.begin();
		iter!=zhVector.end(); ++iter)
		cout<<*iter<<" ";
	cout<<endl;
	cout<<"<==";
	for(vector<int>::iterator iter = fanVector.begin();
		iter!=fanVector.end(); ++iter)
		cout<<*iter<<" ";
	cout<<endl;
}

// 为测试添加的其他函数----
//添加节点到链表尾部
// 调用时，AAddToTail(&head,1);
void AAAddToTail(struct ListNode **head,int value){ //可能修改head的值，则必须传入head的地址，&head，即ListNode **
	//ListNode pNew(value); //！！！一定注意，，链表要动态申请节点空间！！！
	ListNode *pNew = new ListNode(value);
	if(*head == NULL){
		*head = pNew;
		return;
	}
	ListNode *pNode = *head;
	while(pNode->next!=NULL){
		pNode = pNode->next ;
	}
	pNode->next = pNew;
}
// -- 传入指针的引用作为参数，，函数体使用head，不需要解地址操作
// 相应的，调用时，也不需要取地址操作，直接 AAddToTail(head,1);
void AAddToTail_useReference(struct ListNode *&head,int value){ //可能修改head的值，则可以传入指针head的引用
	//ListNode pNew(value); //！！！一定注意，，链表要动态申请节点空间！！！
	ListNode *pNew = new ListNode(value);
	if(head == NULL){
		head = pNew;
		return;
	}
	ListNode *pNode = head;
	while(pNode->next!=NULL){
		pNode = pNode->next ;
	}
	pNode->next = pNew;
}

// 删除第一个值为value的节点
void RRemoveNode(struct ListNode **head,int value){
	if(*head==NULL)
		return;
	ListNode *pToRemoved = NULL;
	if((*head)->val == value) //单独处理需要更改头结点的
	{
		pToRemoved = *head;
		*head = (*head)->next ;
		return;
	}
	ListNode *pNode = *head;
	while( pNode->next != NULL && pNode->next->val != value)
		pNode = pNode->next;
	if( pNode->next != NULL){ //说明找到了
		pToRemoved = pNode->next ;
		pNode->next = pNode->next->next ;
	}
	if(pToRemoved != NULL){ // ---！！！莫漏！！！---
		delete pToRemoved;
		pToRemoved = NULL;
	}
}
// 清空链表
void toEmptyList(struct ListNode **head){
	if(*head == NULL)
		return;
	ListNode *pNode = NULL;
	while(*head != NULL){
		pNode = *head;
		*head = (*head)->next;
		delete pNode;
	}
	if(*head == NULL)
		cout<<"List is Emptied"<<endl;
}

/*
int main(){
	
	ListNode *head = NULL;
	// 测试：
	RRemoveNode(&head,2); //测试：链表为空时删除
	printListZF(head);  // 正向反向打印

	AAddToTail(&head,1);	//测试：添加第一个节点；
	//test.AAddToTail_useReference(head,1);	//测试：添加第一个节点；
	printListZF(head);  // 正向反向打印

	RRemoveNode(&head,1);	//测试：只有一个节点时删除；
	printListZF(head);  // 正向反向打印

    AAddToTail(&head,1);	//测试：删除后添加第一个节点；
	printListZF(head);  // 正向反向打印
	
	AAddToTail(&head,2);	//测试：添加；
	printListZF(head);  // 正向反向打印

	AAddToTail(&head,3);	//测试：添加；
	printListZF(head);  // 正向反向打印

	AAddToTail(&head,4);	//测试：添加；
	printListZF(head);  // 正向反向打印

	AAddToTail(&head,5);	//测试：添加；
	printListZF(head);  // 正向反向打印

	AAddToTail(&head,6);	//测试：添加；
	printListZF(head);  // 正向反向打印
	
	RRemoveNode(&head,1);	//测试：删除开头
	printListZF(head);  // 正向反向打印

	RRemoveNode(&head,4);	//测试：删除中间
	printListZF(head);  // 正向反向打印

	RRemoveNode(&head,6);	//测试：删除最后
	printListZF(head);  // 正向反向打印

	toEmptyList(&head);
	
	system("pause");
	return 0;
}
*/