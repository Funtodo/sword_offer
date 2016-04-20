#include"stdafx.h"
#include<iostream>
#include<vector>
using namespace std;

//������˳ʱ���ӡ-------------------
//�ؼ��㣺1��һȦȦ��ӡ��ע��ÿȦ��ӡ�����Ȧ��ӡ����������
//		2)ÿһȦ��ӡ�ĸ����裬ע��ÿ�������ӡ�ķ�Χ���ӡ��������

//columns-�����У�rows-������
void printMatrixInCircle(int** matrix,int rows,int columns,int start);
void printMatrixClockwisely(int** matrix,int rows,int columns) {
	if(matrix==NULL || rows<=0 || columns<=0)
		return;
	int start = 0;
	while(start*2<rows && start*2<columns){
		printMatrixInCircle(matrix,rows,columns,start);	//��ӡһȦ
		++start;
	}
	cout<<endl;
}
void printMatrixInCircle(int** matrix,int rows,int columns,int start){
	int endCol = columns - (start+1);		//x�᷽���������
	int endRow = rows - (start+1);		//y�᷽���������	
	//��һ���������� һ����ӡ
	for(int i=start;i<=endCol;++i)
		//cout<<matrix[start][i]<<endl;
		cout<<*((int*)matrix + start*columns + i)<<"\t";	//�ֹ�Ѱַ����http://blog.csdn.net/liyongbao1988/article/details/7463481
	//�ڶ�������������
	if(start+1<=endRow)
		for(int j=start+1;j<=endRow;++j)
			//cout<<matrix[j][endCol]<<endl;
			cout<<*((int*)matrix + j*columns + endCol)<<"\t";
	//����������������
	if(start+1<=endRow && endCol-1>=start)
		for(int i=endCol-1;i>=start;--i)
			//cout<<matrix[endRow][i]<<endl;
			cout<<*((int*)matrix + endRow*columns + i)<<"\t";
	//���Ĳ�����������
	if(endRow-1 > start && endCol-1>=start)
		for(int j=endRow-1;j>start;--j)
			//cout<<matrix[j][start]<<endl;
			cout<<*((int*)matrix + j*columns + start)<<"\t";
}

//----ţ����������vector���ҷ���vector��ʽ-----(����һ��)----
vector<int> printMatrix(vector<vector<int> > matrix);
void printMatrixInCircle_vector(vector<vector<int> > matrix,vector<int> &result,int start);

int main(){
	int array1[][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};		//���ܲ���
	printMatrixClockwisely((int**)array1,4,4);
	int array2[][5] = {{1,2,3,4,4},{5,6,7,8,8},{9,10,11,12,12},{13,14,15,16,17}};		//���ܲ���
	printMatrixClockwisely((int**)array2,4,5);
	int array3[][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};		//���ܲ���
	printMatrixClockwisely((int**)array3,3,4);
	int array4[][1] = {{1},{5},{9},{13}};	//ֻ��һ��
	printMatrixClockwisely((int**)array4,4,1);
	int array5[][4] = {{1,5,9,13}};			//ֻ��һ��
	printMatrixClockwisely((int**)array5,1,4);
	int array6[][1] = {{1}};				//ֻ��һ��һ��
	printMatrixClockwisely((int**)array6,1,1);
	//--vector��ʽ��֤----
	vector<vector<int> > matrix;
	for(int i=0;i<4;++i)
		matrix.push_back(vector<int>(array1[i],array1[i]+4));
	vector<int> result = printMatrix(matrix);
	//��ӡ���
	for(vector<int>::const_iterator it=result.begin();it!=result.end();++it)
		cout<<*it<<"\t";
	cout<<endl;
	system("pause");
	return 0;
}

//----ţ����������vector���ҷ���vector��ʽ-----
vector<int> printMatrix(vector<vector<int> > matrix) {
	vector<int> result;
	if(matrix.size()==0)
		return result;
	int start = 0;
	int rows = matrix.size();			//���±������Щ
	int columns = matrix[0].size();
	while(start*2<rows && start*2<columns){
		printMatrixInCircle_vector(matrix,result,start);	//��ӡһȦ
		++start;
	}
	return result;
}
void printMatrixInCircle_vector(vector<vector<int> > matrix,vector<int> &result,int start){
	int rows = matrix.size();			//���±������Щ
	int columns = matrix[0].size();
	int endCol = columns - (start+1);		//x�᷽���������
	int endRow = rows - (start+1);		//y�᷽���������	
	//��һ���������� һ����ӡ
	for(int i=start;i<=endCol;++i)
		result.push_back(matrix[start][i]);
	//�ڶ�������������
	if(start+1<=endRow)
		for(int j=start+1;j<=endRow;++j)
			result.push_back(matrix[j][endCol]);
	//����������������
	if(start+1<=endRow && endCol-1>=start)
		for(int i=endCol-1;i>=start;--i)
			result.push_back(matrix[endRow][i]);
	//���Ĳ�����������
	if(endRow-1 > start && endCol-1>=start)
		for(int j=endRow-1;j>start;--j)
			result.push_back(matrix[j][start]);
}