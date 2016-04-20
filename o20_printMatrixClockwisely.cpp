#include"stdafx.h"
#include<iostream>
#include<vector>
using namespace std;

//将矩阵顺时针打印-------------------
//关键点：1）一圈圈打印，注意每圈打印起点与圈打印结束条件；
//		2)每一圈打印四个步骤，注意每个步骤打印的范围与打印的条件；

//columns-矩阵行，rows-矩阵列
void printMatrixInCircle(int** matrix,int rows,int columns,int start);
void printMatrixClockwisely(int** matrix,int rows,int columns) {
	if(matrix==NULL || rows<=0 || columns<=0)
		return;
	int start = 0;
	while(start*2<rows && start*2<columns){
		printMatrixInCircle(matrix,rows,columns,start);	//打印一圈
		++start;
	}
	cout<<endl;
}
void printMatrixInCircle(int** matrix,int rows,int columns,int start){
	int endCol = columns - (start+1);		//x轴方向结束坐标
	int endRow = rows - (start+1);		//y轴方向结束坐标	
	//第一步，从左到右 一定打印
	for(int i=start;i<=endCol;++i)
		//cout<<matrix[start][i]<<endl;
		cout<<*((int*)matrix + start*columns + i)<<"\t";	//手工寻址！！http://blog.csdn.net/liyongbao1988/article/details/7463481
	//第二步，从上往下
	if(start+1<=endRow)
		for(int j=start+1;j<=endRow;++j)
			//cout<<matrix[j][endCol]<<endl;
			cout<<*((int*)matrix + j*columns + endCol)<<"\t";
	//第三步，从右往左
	if(start+1<=endRow && endCol-1>=start)
		for(int i=endCol-1;i>=start;--i)
			//cout<<matrix[endRow][i]<<endl;
			cout<<*((int*)matrix + endRow*columns + i)<<"\t";
	//第四步，从下往上
	if(endRow-1 > start && endCol-1>=start)
		for(int j=endRow-1;j>start;--j)
			//cout<<matrix[j][start]<<endl;
			cout<<*((int*)matrix + j*columns + start)<<"\t";
}

//----牛客网，采用vector，且返回vector形式-----(本质一样)----
vector<int> printMatrix(vector<vector<int> > matrix);
void printMatrixInCircle_vector(vector<vector<int> > matrix,vector<int> &result,int start);

int main(){
	int array1[][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};		//功能测试
	printMatrixClockwisely((int**)array1,4,4);
	int array2[][5] = {{1,2,3,4,4},{5,6,7,8,8},{9,10,11,12,12},{13,14,15,16,17}};		//功能测试
	printMatrixClockwisely((int**)array2,4,5);
	int array3[][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};		//功能测试
	printMatrixClockwisely((int**)array3,3,4);
	int array4[][1] = {{1},{5},{9},{13}};	//只有一列
	printMatrixClockwisely((int**)array4,4,1);
	int array5[][4] = {{1,5,9,13}};			//只有一行
	printMatrixClockwisely((int**)array5,1,4);
	int array6[][1] = {{1}};				//只有一行一列
	printMatrixClockwisely((int**)array6,1,1);
	//--vector形式验证----
	vector<vector<int> > matrix;
	for(int i=0;i<4;++i)
		matrix.push_back(vector<int>(array1[i],array1[i]+4));
	vector<int> result = printMatrix(matrix);
	//打印结果
	for(vector<int>::const_iterator it=result.begin();it!=result.end();++it)
		cout<<*it<<"\t";
	cout<<endl;
	system("pause");
	return 0;
}

//----牛客网，采用vector，且返回vector形式-----
vector<int> printMatrix(vector<vector<int> > matrix) {
	vector<int> result;
	if(matrix.size()==0)
		return result;
	int start = 0;
	int rows = matrix.size();			//用下标更清晰些
	int columns = matrix[0].size();
	while(start*2<rows && start*2<columns){
		printMatrixInCircle_vector(matrix,result,start);	//打印一圈
		++start;
	}
	return result;
}
void printMatrixInCircle_vector(vector<vector<int> > matrix,vector<int> &result,int start){
	int rows = matrix.size();			//用下标更清晰些
	int columns = matrix[0].size();
	int endCol = columns - (start+1);		//x轴方向结束坐标
	int endRow = rows - (start+1);		//y轴方向结束坐标	
	//第一步，从左到右 一定打印
	for(int i=start;i<=endCol;++i)
		result.push_back(matrix[start][i]);
	//第二步，从上往下
	if(start+1<=endRow)
		for(int j=start+1;j<=endRow;++j)
			result.push_back(matrix[j][endCol]);
	//第三步，从右往左
	if(start+1<=endRow && endCol-1>=start)
		for(int i=endCol-1;i>=start;--i)
			result.push_back(matrix[endRow][i]);
	//第四步，从下往上
	if(endRow-1 > start && endCol-1>=start)
		for(int j=endRow-1;j>start;--j)
			result.push_back(matrix[j][start]);
}