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
	ListNode *pHead; //����ͷָ��,ָ���һ���ڵ�
	// ListNode **pNode; //���������������γ�ʼ����pNode=NULL�������*pNode=pNew��д0��ַ��*pNode=NULL����ʼ����**pHead��0xccccc,�õ�ַ����д
	void PrintListReversingly_recursion(ListNode *pHead);
public:
	//void AddToTail(ListNode **pHead, int value); //������ݣ������ö�����ʽдʱ��Ҫ����ͷָ��ĵ�ַ &pNode�� **pHead��������Ƕ�����listʵ�֣�
	void AddToTail(int value); //�������,���ڶ�����࣬����Ҫ����ͷָ����������Ҷ�pHead���޸Ļᱣ��
	void RemoveNode(int value); //�Ƴ���һ��Ϊvalue��node

	void PrintListReversingly(); //�����ӡlist
	void PrintListReversingly2(); //�汾2
	void printList(); //������ӡlist������)

	MyList(){
		pHead = NULL;
	}
	~MyList();  ///�ڵ�ͨ��new���ɣ�Ҫ�����εĻ������нڵ��ڴ�
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
	//������Ϊ�˴�newNode����ʱ���������������н��������ͷŴ˱���ռ���ڴ�ռ䣬��ָ��ýڵ�����
	//ListNode pNew;	pNew.value = value; 	pNew.pNext = NULL;
	//�˴�Ӧ���ö�̬�ڴ����
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
	if(pHead->value == value){ //ɾ����һ���ڵ㣬�����pHead
		pToRemoved = pHead;
		//pHead = NULL; //!--!����������Ҫ��ֻ��һ���ڵ���ж���ڵ�ֱ�������
		pHead = pHead->pNext; //--!---���ֻ��һ���ڵ㣬pHead->pNext = NULL��������ж���ڵ㣬pHead->pNextָ��ɾ���ڵ����һ���ڵ�
	}else{
		ListNode *pNode = pHead;
		while( pNode->pNext!=NULL && pNode->pNext->value != value) // -!- pNode->pNext!=NULL ����Ҫ��ǰ����
			pNode = pNode->pNext;
		if( pNode->pNext!=NULL){
			pToRemoved = pNode->pNext;
			pNode->pNext = pNode->pNext->pNext;
		}
	}
	if(pToRemoved != NULL ){ //--������---��Ҫ���ж��Ƿ���Ҫɾ���Ľڵ�
		delete pToRemoved;
		pToRemoved = NULL; //�ǵ���ΪNULL����ֹ�����ͷŵ��ڴ�ռ����
	}
}

//�ݹ�汾---
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
	//while(pNode->pNext != NULL){ //--��������-�ݹ��ǲ���Ҫѭ���ģ���������޵ݹ���ѭ������������
	if(pNode->pNext != NULL) //������һ���ڵ�ʱ���������һ���ڵ�
		PrintListReversingly_recursion(pNode->pNext);
	cout<<pNode->value<<" "; //�����ǰ�ڵ�
}

//ʹ��ջ----
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
	MyList myList;	//����һ�����󣬵���Ĭ�Ϲ��캯�����޲ι��캯����myList.AAddToTail(0)
	//MyList *myList = new MyList; // new���ض����ָ�룻myList->AAddToTail(0) �� (*myList).AddToTail(0);
	// ���ԣ�
	myList.RemoveNode(2); //���ԣ�����Ϊ��ʱɾ��
	myList.printList(); myList.PrintListReversingly();  // �������ӡ

	myList.AddToTail(1);	//���ԣ���ӵ�һ���ڵ㣻
	myList.printList(); myList.PrintListReversingly();  // �������ӡ

	myList.RemoveNode(1);	//���ԣ�ֻ��һ���ڵ�ʱɾ����
	myList.printList(); myList.PrintListReversingly();  // �������ӡ

	myList.AddToTail(1);	//���ԣ�ɾ������ӵ�һ���ڵ㣻
	myList.printList(); myList.PrintListReversingly();  // �������ӡ

	myList.AddToTail(2);	//���ԣ���ӣ�
	myList.printList(); myList.PrintListReversingly();  // �������ӡ

	myList.AddToTail(3);	//���ԣ���ӣ�
	myList.printList(); myList.PrintListReversingly();  // �������ӡ

	myList.AddToTail(4);	//���ԣ���ӣ�
	myList.printList(); myList.PrintListReversingly();  // �������ӡ

	myList.AddToTail(5);	//���ԣ���ӣ�
	myList.printList(); myList.PrintListReversingly();  // �������ӡ

	myList.AddToTail(6);	//���ԣ���ӣ�
	myList.printList(); myList.PrintListReversingly();  // �������ӡ

	myList.RemoveNode(1);	//���ԣ�ɾ����ͷ
	myList.printList(); myList.PrintListReversingly();  // �������ӡ

	myList.RemoveNode(4);	//���ԣ�ɾ���м�
	myList.printList(); myList.PrintListReversingly();  // �������ӡ

	myList.RemoveNode(6);	//���ԣ�ɾ�����
	myList.printList(); myList.PrintListReversingly();  // �������ӡ
	} //��������ֻ��Ϊ�˿������������
	system("pause");
	return 0;
}
//*/