// ShellSortTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
using	 namespace	std;


//һ��shell����ĺ�������
//R��ʾ���Ԫ�ص�������Ԫ�ص�ַ
//len ���鳤��
//step��ʾ����
void shellpass(int * R, int len,int step)
{
	//Ĭ�������R[0]��λ�ò��������Ԫ��
	for (size_t i = step+1; i < len+1; i++)
	{
		R[0] = R[i];
		int j = i;
		if (R[i]<R[i-step])
		{
			
			do
			{
				R[j] = R[j - step]; //Ԫ�غ���
					j -= step;
			} while (j>0&&R[0]<R[j-step]);

			R[j] = R[0]; //��Ԫ�ز��뵽���ʵ�λ��
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


//��int����ת��Ϊstring����
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

//�ַ������ƶ�
//psָ��Ҫ�ƶ����ַ���
//n��ʾҪ�ƶ���λ��
void strshift (char * ps,int n)
{
	//ʵ���ַ������Ƶ�˼·
	//1. ���ַ���ǰ�ε�n���ַ�������ͬ����˵��ַ�������
	//2. �������ַ������򣬾Ϳ�����ʵ���ַ��������Ʋ���

	//step1. ��ǰ�ε��ַ�������
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

	
	//step 2 ����˵��ַ�������
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

	//step 3 �������ַ�����ת
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

int ga[10]; //ȫ�ַ�Χ�ڵ�����Ĭ�Ͻ��г�ʼ��

/***************************************************************/
/*******************@@@@@@@ ������ ����Ա���Ա��� p236******************************/
/***************************************************************/

//�ַ������������ִ��������Ӵ�
//���س��������ַ����Ĵ���
int max_frequency_substr(char * str)
{
	//����һ�����飬������еĺ�׺�ַ���
	int len = strlen(str);  //len��¼�ַ����ĳ���
	char** suffix = (char**) new char*[len]; //��ź�׺�ַ���������
	for (size_t i = 0; i < len; i++)
	{
		suffix[i] = &str[i];
	}

	int max_time = 0; //��¼���ֵ�������
	char * address = 0; //��¼�ظ����������Ӵ��ĵ�ַ
	int size = 0; //��¼�ظ����������Ӵ��ĳ���

	int tmp_time = 0; //���ҹ������õ��ļ�������

	//�������Ӵ����ֵĹ��ɿ�֪���Ӵ�����󳤶�Ϊ��len+1��/2�������ں�׺�ַ��������е�indexΪx ,x+step,x+2step,���У�stepΪ�ظ��Ӵ��ĳ���
	for (size_t step = 1; step < (len+1)/2; step++)
	{
		//ע�����������Ϊi+step,��ΪҪ��֤�����ظ�һ��
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
	cout << "�ظ����������Ӵ��ĳ���Ϊ��" << size << endl;
	cout << "�ظ����������ַ���Ϊ��" << address << endl;
	return max_time;


}

//Ѱ���ַ������ظ�������ַ���
//��������ַ����ĳ���
int max_size_repeate_substr(char *str)
{
	//�ڲ��������ַ������������£����ַ�������󳤶�Ϊ(len+1)/2
	int len = strlen(str);
	char** suffix = new char*[len]; //��¼��׺�ַ���������
	for (size_t i = 0; i < len; i++)
	{
		suffix[i] = &str[i];
	}
	int max_size = 0;  //������ַ����ĳ���
	int time = 0; //������ַ������ֵĴ��� 
	char * address = 0; //������ַ����״γ��ֵĵ�ַ
	int tmp_size = 0;  //���ҹ������õ��ļ�������


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
					cout << "���ַ�������󳤶�Ϊ" << max_size << endl;
					cout << "�״γ��ֵĵ�ַΪ" << suffix[i] << endl;
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

//���ַ�����ĳ�����ַ����Ժ�������ַ�
//��Ҫʹ���κ����е�C���򣨺�����
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
			int tmp = i; //��¼��ʼ�Ƚϵ�λ��
			
			while (str[i++]==sub_str[j++])
			{
				if (sub_str[j]=='\0') //���ַ����Ѿ���ȫƥ��
				{
					return &str[tmp];
				}
				if (str[i]=='\0')
				{
					return NULL;
				}
			}
			i = tmp; //������ַ�����;ƥ��ʧ�ܣ�����forѭ�������ִ��i++����
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
	cout << "�����" << endl;
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

#pragma region //���char��Ӧ��ASCII��
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

#pragma region //��int����ת��Ϊ�ַ���
	/*int x=12345;
	char* re = int2string(x);
	cout << int2string(x) << endl;*/

#pragma endregion

#pragma region //�ַ����ĸ���
	/*char s[] = "123456789";
	char d[] = "1235678910";
	strcpy_s(d,s);
	cout << d << endl;
	cout << s << endl;

	strshift(s, 3);
	cout << s << endl;*/

#pragma endregion

#pragma region //���鶨��
	//int a[10] = {}; //������ʽĬ�ϳ�ʼ��Ϊ0
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

#pragma region //�ظ������������ַ���
	//char * str = "abcdbcddbcabc";
	//char * str = "abcebcebcebmn";
	//char * s = "abcdefgbhhikdfaba";
	//char* ts = "yyabcdabjcabceg";
	//char * t = "abcdefghijkc";
	//
	////int len = max_frequency_substr(str);
	//int len = max_size_repeate_substr(t);

#pragma endregion

#pragma region //����ƥ������ַ���֮��������ַ�
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

