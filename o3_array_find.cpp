// array_find.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

class Solution {
public:
    bool Find(vector<vector<int> > array,int target){
		vector<int>::size_type col_right = 0;
		vector<int>::size_type row_up = array.size() -1;
		while( row_up>=0 && col_right != array[0].size()){
				if( target < array[row_up][col_right] ){
					row_up--;
					continue;
				}
				else if( target > array[row_up][col_right] ){
					col_right++;
					continue;
				}
				else
					return true;
		}
		return false;
    }
};
/*
int _tmain(int argc, _TCHAR* argv[])
{
	Solution test_s;
	
	//新建测试用例，，暂时不知道怎样更方便；
	vector<vector<int> > vi(4,vector<int>(5));
	int a[4][5] = {{1,2,3,4,5},{7,12,14,15,16},{8,13,15,16,18},{9,16,17,18,20}}; 
	for(int m=0;m<4;m++)
		for(int n=0;n<5;n++)
			vi[m][n] = a[m][n];

	vector<vector<int>>::iterator i;
	vector<int>::iterator j;
	for(i = vi.begin(); i != vi.end(); i++){
		for(j = i->begin(); j != i->end(); j++){
			cout<<*(j)<<"  ";
		}
		cout<<endl;
	}
	cout<<vi.size()<<"	"<<vi[0].size()<<endl;

	int target = 12;
	bool tt = test_s.Find(vi,target);
	cout<<"找到了？"<<tt<<endl;

	system("pause");
	return 0;
}
*/