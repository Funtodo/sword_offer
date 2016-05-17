#include "stdafx.h"
#include "list.h"
#include <iostream>
using namespace std;

//������������O(1)ʱ����ɾ������ڵ�

//˼·������ɾ��ĳ���ڵ㣬��Ҫ�������ýڵ�֮ǰ��Ȼ����ǰ�ڵ�ָ��ָ��ýڵ��next�ڵ㣬O(n)
//    o(1)���������õõ��ýڵ��ǰһ���ڵ�ָ�룻
//			   �øýڵ��һ���ڵ����ݸ��Ǹýڵ㣬Ȼ���øýڵ�nextָ��ָ��next��next
//ע�⣺ɾ���Ľڵ���β�ڵ㣻����ֻ��һ���ڵ㣬ɾ���ýڵ㣻
void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted){
	if(!pListHead || !pToBeDeleted)
		return;
	
	// Ҫɾ���Ľ�㲻��β���
	if(pToBeDeleted->m_pNext != NULL){
		ListNode* pNext = pToBeDeleted->m_pNext;
		pToBeDeleted->m_nValue = pNext->m_nValue;	//���Ƿ�ʽ������û�иı�pToBeDeleted�ڵ��ַ�ռ䣬�����в��õ�������pToBeDeleted��ͷ������
		pToBeDeleted->m_pNext = pNext->m_pNext;

		delete pNext;
		pNext = NULL;
	}
	// ����ֻ��һ����㣬ɾ��ͷ��㣨Ҳ��β��㣩
	else if(*pListHead == pToBeDeleted){   // && pToBeDeleted->m_pNext == NULL
		delete pToBeDeleted;
		pToBeDeleted = NULL;

		*pListHead = NULL;
	}
	// �������ж����㣬ɾ��β��㣬����ʱֻ����O(n)��ʽ
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

// ====================���Դ���====================
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

// �������ж����㣬ɾ���м�Ľ��
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

// �������ж����㣬ɾ��β���
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

// �������ж����㣬ɾ��ͷ���
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

// ������ֻ��һ����㣬ɾ��ͷ���
void TTest4()
{
	ListNode* pNode1 = CreateListNode(1);

	TTest(pNode1, pNode1);
}

// ����Ϊ��
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