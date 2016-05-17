#include "stdafx.h"
#include "list.h"
#include <iostream>
using namespace std;

//问题描述：在O(1)时间内删除链表节点

//思路：常规删除某个节点，需要遍历到该节点之前，然后用前节点指针指向该节点的next节点，O(n)
//    o(1)方法：不用得到该节点的前一个节点指针；
//			   用该节点后一个节点内容覆盖该节点，然后用该节点next指针指向next的next
//注意：删除的节点是尾节点；链表只有一个节点，删除该节点；
void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted){
	if(!pListHead || !pToBeDeleted)
		return;
	
	// 要删除的结点不是尾结点
	if(pToBeDeleted->m_pNext != NULL){
		ListNode* pNext = pToBeDeleted->m_pNext;
		pToBeDeleted->m_nValue = pNext->m_nValue;	//覆盖方式，，并没有改变pToBeDeleted节点地址空间，，所有不用单独考虑pToBeDeleted是头结点情况
		pToBeDeleted->m_pNext = pNext->m_pNext;

		delete pNext;
		pNext = NULL;
	}
	// 链表只有一个结点，删除头结点（也是尾结点）
	else if(*pListHead == pToBeDeleted){   // && pToBeDeleted->m_pNext == NULL
		delete pToBeDeleted;
		pToBeDeleted = NULL;

		*pListHead = NULL;
	}
	// 链表中有多个结点，删除尾结点，，此时只能用O(n)方式
	else{								// pToBeDeleted->m_pNext == NULL  && *pListHead != pToBeDeleted
		ListNode* pNode = *pListHead;
		while(pNode->m_pNext != pToBeDeleted)
			pNode = pNode->m_pNext;

		pNode->m_pNext = NULL;
		delete pToBeDeleted;
		pToBeDeleted = NULL;
	}

}
/*

// ====================测试代码====================
void TTest(ListNode* pListHead, ListNode* pNode)
{
	printf("The original list is: \n");
	PrintList(pListHead);

	printf("The node to be deleted is: \n");
	PrintListNode(pNode);

	DeleteNode(&pListHead, pNode);

	printf("The result list is: \n");
	PrintList(pListHead);
}

// 链表中有多个结点，删除中间的结点
void TTest1()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	TTest(pNode1, pNode3);

	DestroyList(pNode1);
}

// 链表中有多个结点，删除尾结点
void TTest2()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	TTest(pNode1, pNode5);

	DestroyList(pNode1);
}

// 链表中有多个结点，删除头结点
void TTest3()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	TTest(pNode1, pNode1);

	DestroyList(pNode1);
}

// 链表中只有一个结点，删除头结点
void TTest4()
{
	ListNode* pNode1 = CreateListNode(1);

	TTest(pNode1, pNode1);
}

// 链表为空
void TTest5()
{
	TTest(NULL, NULL);
}

int _tmain(int argc, _TCHAR* argv[])
{
	TTest1();
	TTest2();
	TTest3();
	TTest4();
	TTest5();
	system("pause");
	return 0;
}

*/