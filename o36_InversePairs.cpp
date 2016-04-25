#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;

int InversePairsCore(vector<int> &data,vector<int> &copy,int pLeft,int pRight);
int InversePairs(vector<int> data) {
	if(data.size()==0)
		return 0;
	vector<int> copy;
	for(vector<int>::const_iterator it=data.begin();it!=data.end();++it)	//һ�Ρ����롱�ռ䣬����merge��ÿ������ռ��Ч
		copy.push_back(*it);
	return InversePairsCore(data,copy,0,data.size()-1);			//�����±�����㣬������������Ե�һ��Ԫ��ǰһ��Ϊ�ڱ������������ǵ����������ʹ����临��
	//return InversePairsCore(data.begin(),data.end()-1,copy.begin(),copy.end()-1);			//����Եݹ���㣬�õ���������ֱ�Ӵ���vector�ĵ�������Χ
}

int InversePairsCore(vector<int> &data,vector<int> &copy,int iLeft,int iRight){
	if(iLeft==iRight){
		copy[iLeft] = data[iLeft];
		return 0;
	}
	int halfLen = (iRight-iLeft)/2;				//�볤����
	int countLeft = InversePairsCore(copy,data,iLeft,iLeft+halfLen);				//copy �� data ��Ϊ�����ռ�
	int countRight = InversePairsCore(copy,data,iLeft+halfLen+1,iRight);
	//Merge ���֣�mergeͬʱ���������(�ϲ���copy����������copy�ö�������õ�)
	int countMerge=0;
	int iData1 = iLeft+halfLen;			//ǰ������һ��Ԫ�ص��±�
	int iData2 = iRight;				//�������һ��Ԫ�ص��±�
	int iCopy = iRight;				    //copy�����һ��λ�õ��±�
	while(iData1>=iLeft && iData2>=iLeft+halfLen+1){
		if(data[iData1]>data[iData2]){					//��������
			countMerge += iData2-(iLeft+halfLen);		//����ʣ�µ�Ԫ�ض���*pData1С���������ΪpData2-dataMid
			copy[iCopy--] = data[iData1--];
		}else
			copy[iCopy--] = data[iData2--];
	}
	while(iData1>=iLeft)					//ǰ���û����
		copy[iCopy--] = data[iData1--];
	while(iData2>=iLeft+halfLen+1)			//����û����(����whileֻ����һ������)
		copy[iCopy--] = data[iData2--];
	//�����ٴ�copy���ƻ�data����Ϊ����Ŀ��ֻ�Ǽ�������ԣ�����Ҫ��ԭ�������򣬿�����copy��data��Ϊ�����ռ�
	return countLeft+countRight+countMerge;
}

int main(){
	vector<int> numbers;
	int temp;

	while(1){
		cin.clear();  cin.sync();
		numbers.clear();
		cout<<"�����������飺"<<endl;
		while(cin>>temp){
			numbers.push_back(temp);
		}
		cout<<"����Ը���:"<<"\t";
		cout<<InversePairs(numbers)<<endl;
	}
	system("pause");
}