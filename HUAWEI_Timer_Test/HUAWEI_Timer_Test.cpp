// HUAWEI_Timer_Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

using namespace std;


vector<int> vector_timerID;
struct timer
{
	timer():ID(1),time(1000){}
	timer(int i, int t) :ID(i), time(t){}
	int ID;
	int time;

};


void CALLBACK timerProc(
	HWND hwnd,
	UINT message,
	UINT idTimer,
	DWORD dwTime)
{
	cout << "��ʱ�� " << *vector_timerID.begin() <<" ʱ�䵽..."<< endl;
	vector_timerID.pop_back();
}

DWORD CALLBACK Thread(LPVOID pvoid)
{
	timer* pt = (timer*)pvoid;
	//int timerid = SetTimer(NULL, atoi(command_ID.c_str()), atoi(command_time.c_str()) * 1000, timerProc);
	int timerid = SetTimer(NULL, pt->ID, pt->time*1000, timerProc);
	vector_timerID.push_back(timerid);
	MSG msg;
	if (GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
	}
	KillTimer(NULL,timerid);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string command = "";  //���ܵ���������Ϊ��starttimer:ID,time
	size_t separator1 = 0;
	size_t separator2 = 0;

	string command_type, command_ID, command_time;
	cout << "����������" << endl;
	

	MSG msg;
	
	while (cin>>command)
	{
		if (command=="exit"||command=="q")
		{
			return 0;
		}
	 separator1=command.find(':');
	 command_type = command.substr(0, separator1);
	 separator2 = command.find(',');
	 command_ID = command.substr(separator1 + 1, separator2 - separator1-1);
	 command_time = command.substr(separator2 + 1);

	 //����һ����ʱ��
	 if (command_type=="starttimer")
	 {
		 DWORD dwThreadID;
		 timer* pt = new timer();
		 pt->ID = atoi(command_ID.c_str());
		 pt->time = atoi(command_time.c_str());
		 HANDLE hThread = CreateThread(NULL, 0, Thread, pt, 0, &dwThreadID);
		 cout << "������ʱ���ɹ�" << endl;
		 
	 }
	 if (command_type=="list")
	 {
		 for (auto item : vector_timerID)
			 cout << item << " ";
	 }
	 if (command_type=="exit"||command_type=="q")
	 {
		 break;
	 }


	}

	return 0;
}

