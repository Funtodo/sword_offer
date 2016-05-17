#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//ţ������Ҫ����ʽ;Ҫ�󷵻����飬����ֵΪ �����β��ͷ��ֵ

//typedef ListNode *pNode;
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :val(x), next(NULL) {	}
};

//�����ӡ����������vector��

//�����������zhVector���ٴӺ���ǰɨ��zhVector������ֵ���Ƶ�fanVector
//�ռ临�Ӷ� 2n��ʱ�临�Ӷ�ҲΪ 2n
//���� vector<int> ������ʽ�����ƺ��ò��˵ݹ飬��
vector<int> printListFromTailToHead2(struct ListNode* head) {
	vector<int> zhVector;
	ListNode *pNode = head;
	while(pNode!=NULL){
		zhVector.push_back(pNode->val);
		pNode = pNode->next;
	}
	vector<int> fanVector;
	//���� zhVector.end() ֻ����Ϊ�ڱ�������zhVectorΪ��ʱ������
	//for(vector<int>::iterator iter = zhVector.end()-1;
	//	    iter >= zhVector.begin(); --iter){
	//		fanVector.push_back( *iter );
	//}
	for(int i=zhVector.size()-1; i>=0; --i){
		fanVector.push_back( zhVector[i] );
	}
	return fanVector;
}
//ʹ��ջ
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
//������ӡ����������vector
vector<int> printListFromHeadToTail(struct ListNode* head){
	vector<int> zhVector;
	ListNode *pNode = head;
	while(pNode!=NULL){
		zhVector.push_back(pNode->val);
		pNode = pNode->next;
	}
	return zhVector;
}
//������ӡ
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

// Ϊ������ӵ���������----
//��ӽڵ㵽����β��
// ����ʱ��AAddToTail(&head,1);
void AAAddToTail(struct ListNode **head,int value){ //�����޸�head��ֵ������봫��head�ĵ�ַ��&head����ListNode **
	//ListNode pNew(value); //������һ��ע�⣬������Ҫ��̬����ڵ�ռ䣡����
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
// -- ����ָ���������Ϊ��������������ʹ��head������Ҫ���ַ����
// ��Ӧ�ģ�����ʱ��Ҳ����Ҫȡ��ַ������ֱ�� AAddToTail(head,1);
void AAddToTail_useReference(struct ListNode *&head,int value){ //�����޸�head��ֵ������Դ���ָ��head������
	//ListNode pNew(value); //������һ��ע�⣬������Ҫ��̬����ڵ�ռ䣡����
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

// ɾ����һ��ֵΪvalue�Ľڵ�
void RRemoveNode(struct ListNode **head,int value){
	if(*head==NULL)
		return;
	ListNode *pToRemoved = NULL;
	if((*head)->val == value) //����������Ҫ����ͷ����
	{
		pToRemoved = *head;
		*head = (*head)->next ;
		return;
	}
	ListNode *pNode = *head;
	while( pNode->next != NULL && pNode->next->val != value)
		pNode = pNode->next;
	if( pNode->next != NULL){ //˵���ҵ���
		pToRemoved = pNode->next ;
		pNode->next = pNode->next->next ;
	}
	if(pToRemoved != NULL){ // ---������Ī©������---
		delete pToRemoved;
		pToRemoved = NULL;
	}
}
// �������
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
	// ���ԣ�
	RRemoveNode(&head,2); //���ԣ�����Ϊ��ʱɾ��
	printListZF(head);  // �������ӡ

	AAddToTail(&head,1);	//���ԣ���ӵ�һ���ڵ㣻
	//test.AAddToTail_useReference(head,1);	//���ԣ���ӵ�һ���ڵ㣻
	printListZF(head);  // �������ӡ

	RRemoveNode(&head,1);	//���ԣ�ֻ��һ���ڵ�ʱɾ����
	printListZF(head);  // �������ӡ

    AAddToTail(&head,1);	//���ԣ�ɾ������ӵ�һ���ڵ㣻
	printListZF(head);  // �������ӡ
	
	AAddToTail(&head,2);	//���ԣ���ӣ�
	printListZF(head);  // �������ӡ

	AAddToTail(&head,3);	//���ԣ���ӣ�
	printListZF(head);  // �������ӡ

	AAddToTail(&head,4);	//���ԣ���ӣ�
	printListZF(head);  // �������ӡ

	AAddToTail(&head,5);	//���ԣ���ӣ�
	printListZF(head);  // �������ӡ

	AAddToTail(&head,6);	//���ԣ���ӣ�
	printListZF(head);  // �������ӡ
	
	RRemoveNode(&head,1);	//���ԣ�ɾ����ͷ
	printListZF(head);  // �������ӡ

	RRemoveNode(&head,4);	//���ԣ�ɾ���м�
	printListZF(head);  // �������ӡ

	RRemoveNode(&head,6);	//���ԣ�ɾ�����
	printListZF(head);  // �������ӡ

	toEmptyList(&head);
	
	system("pause");
	return 0;
}
*/