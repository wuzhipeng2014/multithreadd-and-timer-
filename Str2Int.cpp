// Str2Int.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <list>

using namespace std;

enum values
{
	kvalid = 0, kinvalid
};

int kStatus = kvalid;  //用一个全局的变量来表示将要转换为int的字符串是否是合法的，以与其他情况想区别

int str2intcore(char* pstr, bool minus)
{
	long long num = 0;
	
	while (*pstr!='\0')
	{
		if (*pstr >= '0'&&*pstr <= '9')  //1. 考虑输入的字符是否合法
		{
			num = num * 10 + *pstr - '0'; //将字符转换为对应的数字
			//2.考虑转换后的整型是否溢出,因为num是long long的类型，所以可以表示的范围超出了int所能够表示的最大范围
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
	if (*pstr=='\0') //3.正常结束的话，字符串末尾的字符为一个空格结束符
	{
		kStatus = kvalid;
	}
	if (minus) //将结果转换为负数
	{
		return -1 * num;
	}
	return num;
}

//将字符串转换为整型atoi()函数，要考虑的情况有：
//1. null string 2. 含有非法输入 3. 正负号 4. 溢出处理
int str2int1(char* pstr)
{
	kStatus = kinvalid;  //默认情况下为非法的输入，只有在转换正常结束后才设置此标识位为有效状态
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
		cout << "输入的字符串非法" << endl;
	}
	
	return 0;
}

