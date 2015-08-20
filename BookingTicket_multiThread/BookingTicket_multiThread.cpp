// BookingTicket_multiThread.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;


//���������߳�ģ����Ʊ��С����
DWORD WINAPI Fun1Proc(LPVOID lpParameter);
DWORD WINAPI Fun2Proc(LPVOID lpParameter);

int index = 0;
int tickets = 1000000;
HANDLE hMutex;


int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hThread1;
	HANDLE hThread2;
	//�����߳�
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
	cout << "����4��" << endl;
	Sleep(100000);
	cout << "���߽���" << endl;
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


