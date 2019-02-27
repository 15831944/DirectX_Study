#pragma once
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <conio.h>
#define MAX_THREAD_COUNT 5
#define MAX_BUFFER_SIZE 1024 * 100
using namespace std;
class JIocp
{
public:
	HANDLE m_hReadFile;
	HANDLE m_hWriteFile;
	HANDLE m_Thread[MAX_THREAD_COUNT];
	HANDLE m_ThreadKillEvent;
	HANDLE m_IOCP;
	char*   m_szBuffer[MAX_BUFFER_SIZE];
	OVERLAPPED m_ReadOv;
	OVERLAPPED m_WriteOv;
public:
	bool Init();
	bool Frame();
	bool Release();
public:
	bool WaitForRead();
	bool DispatchRead(DWORD Trans);
	bool DispatchWrite(DWORD Trans);
public:
	static DWORD WINAPI WorkThread(LPVOID pParam);
public:
	JIocp();
	virtual ~JIocp();
};