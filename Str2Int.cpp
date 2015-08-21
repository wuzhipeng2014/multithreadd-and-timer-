// Str2Int.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <list>

using namespace std;

enum values
{
	kvalid = 0, kinvalid
};

int kStatus = kvalid;  //��һ��ȫ�ֵı�������ʾ��Ҫת��Ϊint���ַ����Ƿ��ǺϷ��ģ������������������

int str2intcore(char* pstr, bool minus)
{
	long long num = 0;
	
	while (*pstr!='\0')
	{
		if (*pstr >= '0'&&*pstr <= '9')  //1. ����������ַ��Ƿ�Ϸ�
		{
			num = num * 10 + *pstr - '0'; //���ַ�ת��Ϊ��Ӧ������
			//2.����ת����������Ƿ����,��Ϊnum��long long�����ͣ����Կ��Ա�ʾ�ķ�Χ������int���ܹ���ʾ�����Χ
			if ((!minus&&num>0x7FFFFFFF)||(minus&&num>0x80000000))
			{
				num = 0;
				break;
			}
			pstr++;
		}
		else
		{
			num = 0;
			break;
		}
	}
	if (*pstr=='\0') //3.���������Ļ����ַ���ĩβ���ַ�Ϊһ���ո������
	{
		kStatus = kvalid;
	}
	if (minus) //�����ת��Ϊ����
	{
		return -1 * num;
	}
	return num;
}

//���ַ���ת��Ϊ����atoi()������Ҫ���ǵ�����У�
//1. null string 2. ���зǷ����� 3. ������ 4. �������
int str2int1(char* pstr)
{
	kStatus = kinvalid;  //Ĭ�������Ϊ�Ƿ������룬ֻ����ת����������������ô˱�ʶλΪ��Ч״̬
	long long num = 0;
	if (pstr!=NULL&&*pstr!='\0')
	{
		bool minus = false;
		if (*pstr=='-')
		{
			minus = true;
			pstr++;
		}
		else if (*pstr == '+')
		{
			minus = false;
			pstr++;
		}

		 if (*pstr!='\0')
		{
			num = str2intcore(pstr,minus);
		}
		
	}
	return num;
}


int _tmain(int argc, _TCHAR* argv[])
{
	char* str = "+";
	int re = str2int1(str);
	if (kStatus==kvalid)
	{
		cout << re << endl;
	}
	else
	{
		cout << "������ַ����Ƿ�" << endl;
	}
	
	return 0;
}

