// timer_test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;


int counttime = 0;

//1. sleep(����)ʵ�ּ򵥵Ķ�ʱ��
void timer(int sec)
{
	cout << "��ʱ" << sec << "��" << endl;
	Sleep(sec * 1000);
	cout << "ʱ�䵽" << endl;
}

//3.����windows����Ϣ���ݻ��ƺ�settimer����ʵ�ֶ�ʱ��
void CALLBACK TimeProc(
	HWND hwnd,
	UINT message,
	UINT idTimer,
	DWORD dwTime)
{
	cout << "������ʱ����" << counttime++ << endl;
}
//2.���ö��߳�ʵ�ֶ�ʱ��

DWORD CALLBACK Thread(LPVOID pvoid)
{
	cout << "�߳̿�ʼִ��" << endl;
	MSG msg;
	//PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	UINT timerID = SetTimer(NULL, 1, 1000, TimeProc);
	bool bRet;
	int * p = (int*)pvoid;
	int time = *p;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			//handle the error
		}
		else
		{
			//TranslateMessage(&msg);
			if (time>counttime)
			{
				DispatchMessage(&msg);
			}
			else
			{
				break;
			}

		}
	}
	KillTimer(NULL, timerID);
	cout << "�߳̽���" << endl;
	return 0;
}



//�ڴ������߳���ִ�еĺ���


int _tmain(int argc, _TCHAR* argv[])
{
#pragma region //1. ��sleep()����ʵ�ּ򵥵Ķ�ʱ��
	/*int time;
	while (cin>>time)
	{
		if (time==0)
		{
			return 0;
		}
		timer(time);
	}*/

#pragma endregion

#pragma region //2. ���ö��߳�ʵ�ֶ�ʱ��
	DWORD dwThreadID;
	int time = 5;
	int* pint = &time;
	HANDLE hThread = CreateThread(NULL,0,Thread,pint,0,&dwThreadID);
	int a;
	cin >> a;
	return 0;

#pragma endregion

#pragma region //3. ����window����Ϣ���ݻ��ƺ�settimer����ʵ�ֶ�ʱ��
	/*SetTimer(NULL, 1, 1000, TimeProc);
	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		DispatchMessage(&msg);
	}
*/
#pragma endregion


	return 0;
}

