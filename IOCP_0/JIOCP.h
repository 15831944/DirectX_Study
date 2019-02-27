#pragma once
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <tchar.h>
#pragma comment (lib, "ws2_32.lib")
#define MAX_THREAD_COUNT 5
#define MAX_READ_SIZE 1024* 100
using namespace std;
class JIOCP
{
public:
	HANDLE			 m_hReadFile;
	HANDLE			 m_hWriteFile;
	HANDLE		 	 m_hIOCP;
	HANDLE			 m_hWorkThread[MAX_THREAD_COUNT];
	HANDLE			 m_hEventKillThread;
	OVERLAPPED		 m_hReadOV;
	OVERLAPPED		 m_hWriteOV;
	char			 m_szReadBuf[MAX_READ_SIZE];
	LARGE_INTEGER	 m_FileSize;
public:
	bool Init();
	bool Frame();
	bool Release();
	bool WaitForRead();
	bool DispatchRead(DWORD trans);
	bool DispatchWrite(DWORD trans);
	static DWORD WINAPI WorkerThread(LPVOID pParam);
public:
	JIOCP();
	virtual ~JIOCP();
};

