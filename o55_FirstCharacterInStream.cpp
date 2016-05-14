#include "stdafx.h"
#include <vector>
#include <limits>

using namespace std;

//����������ʵ��һ�����������ҳ��ַ����е�һ��ֻ����һ�ε��ַ������磬�����ַ�����ֻ����ǰ�����ַ�"go"ʱ����һ��ֻ����һ�ε��ַ���"g"��
//        ���Ӹ��ַ����ж���ǰ�����ַ���google"ʱ����һ��ֻ����һ�ε��ַ���"l"�� 
//		  �����ǰ�ַ���û�д��ڳ���һ�ε��ַ�������#�ַ�
class CharStatistics
{
public:
	CharStatistics() : index (0){
		for(int i = 0; i < 256; ++i)
			occurrence[i] = -1;
	}

	void Insert(char ch){
		if(occurrence[ch] == -1)
			occurrence[ch] = index;
		else if(occurrence[ch] >= 0)
			occurrence[ch] = -2;
		index++;  
	}

	char FirstAppearingOnce(){
		char ch = '#';
		int minIndex = numeric_limits<int>::max();		//��ʼ��Ϊ���ֵ
		for(int i = 0; i < 256; ++i)
			if(occurrence[i] >= 0 && occurrence[i] < minIndex){
				ch = (char)i;
				minIndex = occurrence[i];
			}
		return ch;
	}

private:
	// occurrence[i]:      ASCII��Ϊi���ַ����ֵ����
	// occurrence[i] = -1: ���ַ���δ���ֹ�
	// occurrence[i] = -2: ���ַ��Ѿ����ֲ�ֹһ��
	// occurrence[i] >= 0: ���ַ�Ŀǰֻ������һ�Σ���occurrence[i]Ϊ����ֵ�λ��
	int occurrence[256];
	int index;
};

// ==================== Test Code ====================
void Test(char* testName, CharStatistics chars, char expected)
{
	if(testName != NULL)
		printf("%s begins: ", testName);

	if(chars.FirstAppearingOnce() == expected)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

/*
int main(int argc, char* argv[])
{
	CharStatistics chars;

	Test("Test1", chars, '#');

	chars.Insert('g');
	Test("Test2", chars, 'g');

	chars.Insert('o');
	Test("Test3", chars, 'g');

	chars.Insert('o');
	Test("Test4", chars, 'g');

	chars.Insert('g');
	Test("Test5", chars, '#');

	chars.Insert('l');
	Test("Test6", chars, 'l');

	chars.Insert('e');
	Test("Test7", chars, 'l');

	system("pause");
	return 0;
}
*/