#include "JIocp.h"
#define SAFE_HANDLE_KILL(h) {if (h != INVALID_HANDLE_VALUE) { CloseHandle(h); }}
DWORD WINAPI JIocp::WorkThread(LPVOID pParam)
{
	JIocp* iocp = (JIocp*)pParam;
	DWORD Trans;
	ULONG_PTR Key;
	OVERLAPPED* Ov;
	BOOL Ret;
	while (TRUE)
	{
		if (WaitForSingleObject(iocp->m_ThreadKillEvent,1) == WAIT_OBJECT_0)
		{
			break;
		}
		Ret = GetQueuedCompletionStatus(iocp->m_IOCP, &Trans, &Key, &Ov, 5000);
		if (Ret == TRUE)
		{
			if (Trans != 0)
			{
				if (Key != 0 && Ov != 0)
				{
					if (Key == 1111)
					{
						iocp->DispatchRead(Trans);
					}
					if (Key == 2222)
					{
						iocp->DispatchWrite(Trans);
					}
				}
			}
			else
			{
				SetEvent(iocp->m_ThreadKillEvent);
			}
		}
		else
		{
			if (GetLastError() == WAIT_TIMEOUT)
			{
				continue;
			}
			else
			{
				if (Ov != NULL)
				{
					if (GetLastError() == ERROR_HANDLE_EOF)
					{
						SetEvent(iocp->m_ThreadKillEvent);
					}
					else
					{
						cout << "ERROR!" << endl;
					}
				}
			}
		}
	}
	return 0;
}
bool JIocp::DispatchRead(DWORD Trans)
{
	cout << Trans << "Bytes Read" << endl;
	DWORD WriteByte = 0;
	WriteFile(m_hWriteFile, m_szBuffer, Trans, &WriteByte, &m_WriteOv);

	LARGE_INTEGER LI;
	LI.QuadPart = Trans;
	m_ReadOv.Offset += LI.LowPart;
	m_ReadOv.OffsetHigh += LI.HighPart;

	if (WaitForRead() == false)
	{
		SetEvent(m_ThreadKillEvent);
		return false;
	}
	return true;
}
bool JIocp::DispatchWrite(DWORD Trans)
{
	cout << Trans << "Bytes Write" << endl;
	LARGE_INTEGER LI;
	LI.QuadPart = Trans;
	m_WriteOv.Offset += LI.LowPart;
	m_WriteOv.OffsetHigh += LI.HighPart;
	return true;
}
bool JIocp::WaitForRead()
{
	DWORD ReadBytes = 0;
	DWORD Ret = ReadFile(m_hReadFile, m_szBuffer, MAX_BUFFER_SIZE, &ReadBytes, &m_ReadOv);
	if (Ret == FALSE)
	{
		if (GetLastError() == ERROR_IO_PENDING)
		{
			return true;
		}
		// 파일의 끝
		if (GetLastError() == ERROR_HANDLE_EOF)
		{
			return false;
		}
		return false;
	}
	else
	{
		if (ReadBytes == 0 || GetLastError() == ERROR_HANDLE_EOF)
		{
			return false;
		}
	}
	return true;
}
bool JIocp::Init()
{
	m_hReadFile = CreateFile(L"Sample.mp4",GENERIC_READ, 0, 0,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);
	m_hWriteFile = CreateFile(L"SampleCopy.mp4", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);

	DWORD id = 0;
	for (int iThread = 0; iThread < MAX_THREAD_COUNT; iThread++)
	{
		m_Thread[iThread] = CreateThread(0, 0, WorkThread,this, 0, &id);
	}
	m_ThreadKillEvent = CreateEvent(0, TRUE, FALSE, 0);

	m_IOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE,0,0,0);
	CreateIoCompletionPort(m_hReadFile, m_IOCP, 1111, 0);
	CreateIoCompletionPort(m_hWriteFile, m_IOCP,2222, 0);
	return true;
}
bool JIocp::Frame()
{
	WaitForRead();
	WaitForMultipleObjects(MAX_THREAD_COUNT, m_Thread, TRUE, INFINITE);
	return true;
}
bool JIocp::Release()
{
	SAFE_HANDLE_KILL(m_hReadFile);
	SAFE_HANDLE_KILL(m_hWriteFile);
	SAFE_HANDLE_KILL(m_ThreadKillEvent);
	SAFE_HANDLE_KILL(m_IOCP);
	_getch();
	return true;
}
JIocp::JIocp()
{
	ZeroMemory(&m_ReadOv,sizeof(OVERLAPPED));
	ZeroMemory(&m_WriteOv, sizeof(OVERLAPPED));
	m_hReadFile = 0;
	m_hWriteFile = 0;
}
JIocp::~JIocp()
{

}