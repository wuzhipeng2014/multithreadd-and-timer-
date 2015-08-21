// ShellSortTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
using	 namespace	std;


//一趟shell排序的函数过程
//R表示存放元素的数组首元素地址
//len 数组长度
//step表示步长
void shellpass(int * R, int len,int step)
{
	//默认情况下R[0]的位置不存放数组元素
	for (size_t i = step+1; i < len+1; i++)
	{
		R[0] = R[i];
		int j = i;
		if (R[i]<R[i-step])
		{
			
			do
			{
				R[j] = R[j - step]; //元素后移
					j -= step;
			} while (j>0&&R[0]<R[j-step]);

			R[j] = R[0]; //将元素插入到合适的位置
		}
		
	}
}

void shellsort(int* R, int len)
{
	int increment = len;
	do
	{
		increment = increment / 3 + 1;
		shellpass(R,len,increment);
	} while (increment>1);
}


//将int类型转换为string类型
char* int2string(int i)
{
	int remainder = 0;
	int len = 0;
	int it = i;
	while (it>0)
	{
		it = it/ 10;
		++len;
	}
	char* result = new char[len + 1];
	
	
	int count = 0;
	while (i>0)
	{
		remainder = i % 10;
		char temp = '0' + remainder;
		result[len - count-1] = temp;
		count++;
		i = i / 10;
	}
	result[count] = '\0';
	return result;
}

//字符串的移动
//ps指向要移动的字符串
//n表示要移动的位数
void strshift (char * ps,int n)
{
	//实现字符串右移的思路
	//1. 将字符串前段的n个字符串逆序，同理将后端的字符串逆序
	//2. 将整个字符串逆序，就可以是实现字符串的右移操作

	//step1. 将前段的字符串逆序
	int len = strlen(ps);
	char temp;
	char * p1=ps, *p2=&ps[n-1];
	while (p1<p2)
	{
		temp = *p1;
		*p1 = *p2;
		*p2 = temp;
		++p1;
		--p2;
	}

	
	//step 2 将后端的字符串逆序
	p1 = &ps[n];
	p2 = &ps[len - 1];
	while (p1<p2)
	{
		temp = *p1;
		*p1 = *p2;
		*p2 = temp;
		++p1;
		--p2;
	}

	//step 3 将整个字符串反转
	p1 = ps;
	p2 = &ps[len - 1];
	while (p1<p2)
	{
		temp = *p1;
		*p1 = *p2;
		*p2 = temp;
		++p1;
		--p2;
	}


}

int ga[10]; //全局范围内的数组默认进行初始化

/***************************************************************/
/*******************@@@@@@@ 面试题 程序员面试宝典 p236******************************/
/***************************************************************/

//字符串中连续出现次数最多的子串
//返回出现最多的字符串的次数
int max_frequency_substr(char * str)
{
	//创建一个数组，存放所有的后缀字符串
	int len = strlen(str);  //len记录字符串的长度
	char** suffix = (char**) new char*[len]; //存放后缀字符串的数组
	for (size_t i = 0; i < len; i++)
	{
		suffix[i] = &str[i];
	}

	int max_time = 0; //记录出现的最大次数
	char * address = 0; //记录重复最多次数的子串的地址
	int size = 0; //记录重复最多次数的子串的长度

	int tmp_time = 0; //查找过程中用到的计数变量

	//由连续子串出现的规律可知，子串的最大长度为（len+1）/2，并且在后缀字符串数组中的index为x ,x+step,x+2step,其中，step为重复子串的长度
	for (size_t step = 1; step < (len+1)/2; step++)
	{
		//注意结束的条件为i+step,因为要保证至少重复一次
		for (size_t i = 0; i+step < len; i+=step)
		{
			tmp_time = 0;
			int t = i;
			while (t+step<len&&(strncmp(suffix[t],suffix[t+step],step)==0))
			{
				tmp_time++;
				t += step;

			}
			if (tmp_time>max_time)
			{
				max_time = tmp_time;
				size = step;
				address = suffix[i];
			}
		}
		
	}
	cout << "重复次数最多的子串的长度为：" << size << endl;
	cout << "重复次数最多的字符串为：" << address << endl;
	return max_time;


}

//寻找字符串中重复的最长子字符串
//返回最长子字符串的长度
int max_size_repeate_substr(char *str)
{
	//在不允许子字符串交叉的情况下，子字符串的最大长度为(len+1)/2
	int len = strlen(str);
	char** suffix = new char*[len]; //记录后缀字符串的数组
	for (size_t i = 0; i < len; i++)
	{
		suffix[i] = &str[i];
	}
	int max_size = 0;  //最大子字符串的长度
	int time = 0; //最大子字符串出现的次数 
	char * address = 0; //最大子字符串首次出现的地址
	int tmp_size = 0;  //查找过程中用到的计数变量


	for (size_t step = (len+1)/2; step >0; step--)
	{
		
		for (size_t i = 0; i < len; i++)
		{
			time = 0;
			tmp_size = step;
			int t = i;
			while (t+step<len)
			{
				if ((strncmp(suffix[i], suffix[t + step], step) == 0))
				{
					time++;
					max_size = step;
					cout << "子字符串的最大长度为" << max_size << endl;
					cout << "首次出现的地址为" << suffix[i] << endl;
					return max_size;
				}
				else
				{
					t++;
				}
				
				
			}
			
		}
	}

}

//主字符串中某个子字符串以后的所有字符
//不要使用任何已有的C程序（函数）
char * strstr1(char* str, char* sub_str)
{
	if (str==NULL||sub_str==NULL)
	{
		return NULL;
	}
	for (size_t i = 0; str[i]!='\0'; i++)
	{
		int j = 0;
		if (str[i] == sub_str[j])
		{
			int tmp = i; //记录开始比较的位置
			
			while (str[i++]==sub_str[j++])
			{
				if (sub_str[j]=='\0') //子字符串已经完全匹配
				{
					return &str[tmp];
				}
				if (str[i]=='\0')
				{
					return NULL;
				}
			}
			i = tmp; //如果子字符串中途匹配失败，会在for循环语句中执行i++操作
		}
	}
	return NULL;
}


/***************************************************************/
/***************************************************************/
/***************************************************************/



int _tmain(int argc, _TCHAR* argv[])
{
#pragma region //shell sort test
	/*srand(0);
	int R[21];
	for (size_t i = 0; i <= 20; i++)
	{
		R[i] = rand()%100;
	}
	for (size_t i = 1; i < 21; i++)
	{
		cout << R[i] << " ";
	}
	cout << endl;
	shellsort(R,20);
	cout << "排序后" << endl;
	for (size_t i = 1; i < 20; i++)
	{
		cout << R[i] << " ";
	}
	cout << endl;*/
#pragma endregion

#pragma region //multimap test
	/*multimap<int,int> mm;
	mm.insert(pair<int,int>(1,1));
	mm.insert(pair<int, int>(1, 1));
	mm.insert(pair<int, int>(1, 1));
	mm.insert(pair<int, int>(1, 1));
	mm.insert(pair<int,int>(1,5));
	mm.insert(pair<int, int>(2, 1));
	mm.insert(pair<int, int>(2, 1));
		cout<<"key 1 occurs "<<mm.count(1)<<"times";
		cout << endl;*/


#pragma endregion

#pragma region //输出char对应的ASCII码
	/*int A = 'A';
	int a = 'a';
	int b = '1';
	cout << "A= " << A << endl;
	cout << "a= " << a << endl;
	cout << "1= " << b << endl;
	char x = char(b);
	cout << "x=" << x << endl;
	char y = '0'+1;
	cout <<int( y) << endl;*/


#pragma endregion

#pragma region //将int类型转换为字符串
	/*int x=12345;
	char* re = int2string(x);
	cout << int2string(x) << endl;*/

#pragma endregion

#pragma region //字符串的复制
	/*char s[] = "123456789";
	char d[] = "1235678910";
	strcpy_s(d,s);
	cout << d << endl;
	cout << s << endl;

	strshift(s, 3);
	cout << s << endl;*/

#pragma endregion

#pragma region //数组定义
	//int a[10] = {}; //此种形式默认初始化为0
	//for (size_t i = 0; i < 10; i++)
	//{
	//	cout << a[i] << " ";
	//}
	//cout << endl;
	//cout << "cout global ga" << endl;
	//for (size_t i = 0; i < 10; i++)
	//{
	//	cout << ga[i] << " ";
	//}
	//cout << endl;
#pragma endregion

#pragma region //重复次数最多的子字符串
	//char * str = "abcdbcddbcabc";
	//char * str = "abcebcebcebmn";
	//char * s = "abcdefgbhhikdfaba";
	//char* ts = "yyabcdabjcabceg";
	//char * t = "abcdefghijkc";
	//
	////int len = max_frequency_substr(str);
	//int len = max_size_repeate_substr(t);

#pragma endregion

#pragma region //返回匹配的子字符串之后的所有字符
	char* str = "abcdefghijtestklmnopqrstuvwxyz";
	char* sub_str = "xyza";
	char* re = strstr1(str,sub_str);
	if (re)
	{
		cout << re << endl;
	}
	else
	{

		cout << "sub_str not found" << endl;
	}


#pragma endregion



	return 0;
}

