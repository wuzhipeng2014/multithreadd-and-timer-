// BookingTicket_multiThread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;


//定义连个线程模拟买票的小程序
DWORD WINAPI Fun1Proc(LPVOID lpParameter);
DWORD WINAPI Fun2Proc(LPVOID lpParameter);

int index = 0;
int tickets = 1000000;
HANDLE hMutex;


int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hThread1;
	HANDLE hThread2;
	//创建线程
	hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	hMutex = CreateMutex(NULL, true, _T("tickets"));
	if (hMutex)
	{
		if (ERROR_ALREADY_EXISTS==GetLastError())
		{
			cout << "only one instance can run" << endl;
			return 0;
		}
		else
		{
			cout << "everything is ok" << endl;
		}
	}
	WaitForSingleObject(hMutex, INFINITE);
	ReleaseMutex(hMutex);
	ReleaseMutex(hMutex);
	cout << "休眠4秒" << endl;
	Sleep(100000);
	cout << "休眠结束" << endl;
	return 0;

	return 0;
}

DWORD WINAPI Fun1Proc(LPVOID lpParameter)
{
	while (true)
	{
		//ReleaseMutex(hMutex);
		WaitForSingleObject(hMutex, INFINITE);
		if (tickets>0)
		{
			Sleep(100);
			cout << "thread1 sell 1 ticket"<<tickets-- << endl;

		}
		else
		{
			break;
		}
		ReleaseMutex(hMutex);
	}
	return 0;
}

DWORD WINAPI Fun2Proc(LPVOID lpParameter)
{
	while (true)
	{
		//ReleaseMutex(hMutex);
		WaitForSingleObject(hMutex, INFINITE);
		if (tickets>0)
		{
			Sleep(10);
			cout << "thread2 sell 1 ticket" << tickets-- << endl;

		}
		else
		{
			break;
		}
		ReleaseMutex(hMutex);
	}
	return 0;
}


