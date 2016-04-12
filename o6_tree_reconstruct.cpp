#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
	int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
	//��ǰ�����������ع�������
    struct TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> in) {
		if( pre.size()==0 || in.size()==0 || pre.size() != in.size() ){
			throw("Error sequence��");
			//cout<<"Error sequence��"<<endl;
			return NULL;
		}
		return recursiveConstruct(pre.begin(),pre.end(),in.begin(),in.end());
    }
	//�ݹ�ع��������
	//�õ���������ָ������ʣ�vector=��interator��
	//ע�⣺preStartָ�����е�һ��Ԫ�أ�preEndָ���������һ��Ԫ�ص���һ����ַ
	struct TreeNode* recursiveConstruct(
		vector<int>::iterator preStart,vector<int>::iterator preEnd,
		vector<int>::iterator inStart,vector<int>::iterator inEnd
		){
			if(preStart == preEnd && inStart == inEnd) //��������
				return NULL;
			else if(preStart == preEnd || inStart == inEnd)
				throw exception("Error sequence��");

			struct TreeNode *root = new TreeNode(*preStart); //ǰ���һ��λ��Ϊ���ڵ�
			//�ҵ�root�ڵ��������е�λ��
			vector<int>::iterator inRoot = inStart;
			while(inRoot!=inEnd && *inRoot!=*preStart){
				++inRoot;
			}
			if(inRoot!=inEnd && *inRoot==*preStart){ //˵���ҵ���
				int leftSonTreeLen = inRoot-inStart; //����������
				//ע�⣺preStartָ�����е�һ��Ԫ�أ�preEndָ���������һ��Ԫ�ص���һ����ַ
				root->left = recursiveConstruct(preStart+1,preStart+1+leftSonTreeLen, inStart,inRoot); //�ݹ鹹����������������������ǰ��������
				root->right = recursiveConstruct(preStart+1+leftSonTreeLen,preEnd,inRoot+1,inEnd);//�ݹ鹹��������
			}
			else{
				throw exception("Error sequence��");
			}
			return root;
	}

	void printPre(struct TreeNode *root ){//��ӡ������tree��ǰ��
		if(root == NULL) //��������
			return;
		cout<<root->val<<" "; //������ڵ�
		if( root->left != NULL) //���������
			printPre(root->left);
		if(root->right != NULL) //���������
			printPre(root->right );
	}
	void printIn(struct TreeNode *root ){//��ӡ������tree������
		if(root == NULL) //��������
			return;
		if( root->left != NULL) //���������
			printPre(root->left);
		cout<<root->val<<" "; //������ڵ�
		if(root->right != NULL) //���������
			printPre(root->right );
	}
};

void test_example(int *pre1,int *in1,int lenPre1,int lenIn1){
	// Ϊ����Ӧ reConstructBinaryTree() ��������ת��Ϊ vector
	//vector<int> pre(pre1, pre1+sizeof(pre1)/sizeof(pre1[0])); --����������Ѿ���ָ�룬�����ڴ�ͨ�������ķ�ʽ�󳤶�
	vector<int> pre(pre1, pre1+lenPre1);
	vector<int> in(in1,in1+lenIn1);
	Solution test;
	try{ //�����쳣
		TreeNode *exampleTree = test.reConstructBinaryTree(pre,in); //���׳��쳣
		cout<<"pre: ";
		test.printPre(exampleTree); //��ӡ������tree��ǰ�����򣬼���
		cout<<endl<<"in:  ";
		test.printIn(exampleTree);
		cout<<endl;
	}catch(exception err){
		cerr<<err.what()<<endl;
	}
}

/*
int main(){
	TreeNode *root = NULL;
	//����������
	//--1,��ȫ�����������鷽���ʼ��
	int pre1[7] = {1,2,4,5,3,6,7};
	int in1[] = {4,5,2,1,6,7,3};
	//--2,ֻ��������
	int pre2[4] = {1,2,3,4};
	int in2[] = {4,3,2,1};
	//--3,ֻ��������
	int pre3[4] = {1,2,3,4};
	int in3[] = {1,2,3,4};
	//--4,��㣬����ȫ������
	int pre4[8] = {1,2,4,7,3,5,6,8};
	int in4[] = {4,7,2,1,5,3,6,8};
	//--5,ֻ��һ���ڵ�
	int pre5[1] = {1};
	int in5[] = {1};
	//--6,������ɶ�����
	int pre6[8] = {1,2,4,7,3,5,6,8};
	int in6[8] = {4,7,3,1,5,2,6,8};
	test_example(pre1,in1,sizeof(pre1)/sizeof(pre1[0]),sizeof(in1)/sizeof(in1[0]));
	test_example(pre2,in2,sizeof(pre2)/sizeof(pre2[0]),sizeof(in2)/sizeof(in2[0]));
	test_example(pre3,in3,sizeof(pre3)/sizeof(pre3[0]),sizeof(in3)/sizeof(in3[0]));
	test_example(pre4,in4,sizeof(pre4)/sizeof(pre4[0]),sizeof(in4)/sizeof(in4[0]));
	test_example(pre5,in5,sizeof(pre5)/sizeof(pre5[0]),sizeof(in5)/sizeof(in5[0]));
	test_example(pre6,in6,sizeof(pre6)/sizeof(pre6[0]),sizeof(in6)/sizeof(in6[0]));
	system("pause");
	return 0;
}
*/
