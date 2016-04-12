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
	//从前序、中序序列重构二叉树
    struct TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> in) {
		if( pre.size()==0 || in.size()==0 || pre.size() != in.size() ){
			throw("Error sequence！");
			//cout<<"Error sequence！"<<endl;
			return NULL;
		}
		return recursiveConstruct(pre.begin(),pre.end(),in.begin(),in.end());
    }
	//递归地构造二叉树
	//用迭代器比用指针更合适（vector=》interator）
	//注意：preStart指向序列第一个元素；preEnd指向序列最后一个元素的下一个地址
	struct TreeNode* recursiveConstruct(
		vector<int>::iterator preStart,vector<int>::iterator preEnd,
		vector<int>::iterator inStart,vector<int>::iterator inEnd
		){
			if(preStart == preEnd && inStart == inEnd) //结束条件
				return NULL;
			else if(preStart == preEnd || inStart == inEnd)
				throw exception("Error sequence！");

			struct TreeNode *root = new TreeNode(*preStart); //前序第一个位置为根节点
			//找到root节点在中序中的位置
			vector<int>::iterator inRoot = inStart;
			while(inRoot!=inEnd && *inRoot!=*preStart){
				++inRoot;
			}
			if(inRoot!=inEnd && *inRoot==*preStart){ //说明找到了
				int leftSonTreeLen = inRoot-inStart; //左子树长度
				//注意：preStart指向序列第一个元素；preEnd指向序列最后一个元素的下一个地址
				root->left = recursiveConstruct(preStart+1,preStart+1+leftSonTreeLen, inStart,inRoot); //递归构造左子树，传入左子树的前、中序列
				root->right = recursiveConstruct(preStart+1+leftSonTreeLen,preEnd,inRoot+1,inEnd);//递归构造右子树
			}
			else{
				throw exception("Error sequence！");
			}
			return root;
	}

	void printPre(struct TreeNode *root ){//打印构造后的tree的前序
		if(root == NULL) //结束条件
			return;
		cout<<root->val<<" "; //输出根节点
		if( root->left != NULL) //输出左子树
			printPre(root->left);
		if(root->right != NULL) //输出右子树
			printPre(root->right );
	}
	void printIn(struct TreeNode *root ){//打印构造后的tree的中序
		if(root == NULL) //结束条件
			return;
		if( root->left != NULL) //输出左子树
			printPre(root->left);
		cout<<root->val<<" "; //输出根节点
		if(root->right != NULL) //输出右子树
			printPre(root->right );
	}
};

void test_example(int *pre1,int *in1,int lenPre1,int lenIn1){
	// 为了适应 reConstructBinaryTree() 函数，先转换为 vector
	//vector<int> pre(pre1, pre1+sizeof(pre1)/sizeof(pre1[0])); --传入进来是已经是指针，不能在此通过这样的方式求长度
	vector<int> pre(pre1, pre1+lenPre1);
	vector<int> in(in1,in1+lenIn1);
	Solution test;
	try{ //处理异常
		TreeNode *exampleTree = test.reConstructBinaryTree(pre,in); //会抛出异常
		cout<<"pre: ";
		test.printPre(exampleTree); //打印构造后的tree的前序，中序，检验
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
	//测试样例：
	//--1,完全二叉树，数组方便初始化
	int pre1[7] = {1,2,4,5,3,6,7};
	int in1[] = {4,5,2,1,6,7,3};
	//--2,只有左子树
	int pre2[4] = {1,2,3,4};
	int in2[] = {4,3,2,1};
	//--3,只有右子树
	int pre3[4] = {1,2,3,4};
	int in3[] = {1,2,3,4};
	//--4,随便，不完全二叉树
	int pre4[8] = {1,2,4,7,3,5,6,8};
	int in4[] = {4,7,2,1,5,3,6,8};
	//--5,只有一个节点
	int pre5[1] = {1};
	int in5[] = {1};
	//--6,不能组成二叉树
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
