#include "JIOCP.h"
#define SAFE_CLOSE_HANDLE(h) {if (h != INVALID_HANDLE_VALUE){	CloseHandle(h);}}

DWORD WINAPI JIOCP::WorkerThread(LPVOID pParam)
{
	JIOCP* pIocp = (JIOCP*)pParam;
	DWORD bytesTransfer;
	ULONG_PTR KeyValue;
	OVERLAPPED* ov;
	BOOL ret;
	while (TRUE)
	{
		// 종료
		if (WaitForSingleObject(pIocp->m_hEventKillThread, 1) == WAIT_OBJECT_0)
		{
			break;
		}
		// 다른 스레드의 입출력작업을 확인 가능
		// 데이터형 중요
		// 스레드 풀(5) -> 깨운다. 
		ret = GetQueuedCompletionStatus(pIocp->m_hIOCP, &bytesTransfer, &KeyValue, &ov, 5000);
		if (ret == TRUE)
		{
			// 입출력작업이 완료된것을 하나 가져옴
			if (bytesTransfer != 0)
			{
				if (KeyValue != 0 && ov != 0)
				{
					// 3가지 조건이 만족해야 정상적인 완료
					if (KeyValue == 1111)
					{
						//Dispatch 분배
						pIocp->DispatchRead(bytesTransfer);
					}
					if (KeyValue == 2222)
					{
						//Dispatch 분배
						pIocp->DispatchWrite(bytesTransfer);
					}
				}
			}
			else
			{
				SetEvent(pIocp->m_hEventKillThread);
			}
		}
		else
		{
			DWORD dwError = GetLastError();
			if (dwError == WAIT_TIMEOUT)
			{
				continue;
			}
			else
			{
				if (ov != NULL)
				{
					if (dwError == ERROR_HANDLE_EOF)
					{
						SetEvent(pIocp->m_hEventKillThread);
					}
					else
					{
						cout << "ERROR" << endl;
					}
				}
			}
		}
	}
	return 0;
}
bool JIOCP::DispatchRead(DWORD trans)
{
	cout << trans << "Bytes Read" << endl;
	DWORD WriteBytes = 0;
	WriteFile(m_hWriteFile, m_szReadBuf, trans, &WriteBytes, &m_hWriteOV);

	LARGE_INTEGER LI;
	LI.QuadPart = trans;
	m_hReadOV.Offset += LI.LowPart;
	m_hReadOV.OffsetHigh += LI.HighPart;
	if (WaitForRead() == false)
	{
		//SetEvent(m_hEventKillThread);
		return false;
	}
	return true;
}
bool JIOCP::DispatchWrite(DWORD trans)
{
	LARGE_INTEGER size;
	size.LowPart = m_hWriteOV.Offset;
	size.HighPart = m_hWriteOV.OffsetHigh;
	if (m_FileSize.QuadPart <= size.QuadPart)
	{
		SetEvent(m_hEventKillThread);
	}
	cout << trans << "Bytes Write" << endl;
	LARGE_INTEGER LI;
	LI.QuadPart = trans;
	m_hWriteOV.Offset += LI.LowPart;
	m_hWriteOV.OffsetHigh += LI.HighPart;

	return true;
}
bool JIOCP::WaitForRead()
{
	DWORD byteRead = 0;
	DWORD dwRet = ReadFile(m_hReadFile, m_szReadBuf, MAX_READ_SIZE, &byteRead, &m_hReadOV);
	// iocp -> queue 완료하면 iocp queue에 넣는다
	if (dwRet == FALSE)
	{
		DWORD LastError = GetLastError();
		if (LastError == ERROR_IO_PENDING) // 정상 진행중(읽는중)
		{
			return true;
		}
		if (LastError == ERROR_HANDLE_EOF)
		{
			return false;
		}
		return false;
	}
	else
	{
		if (byteRead == 0 || ERROR_HANDLE_EOF == GetLastError()) // 파일의 끝이거나 파일을 못읽었을때
		{
			return false;
		}
	}
	return true;
}
bool JIOCP::Init()
{
	m_hReadFile = CreateFile(L"Sample.mp4", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);
	m_hWriteFile = CreateFile(L"SampleCopy.mp4", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);

	GetFileSizeEx(m_hReadFile,&m_FileSize);

	DWORD id;
	for (int iThread = 0; iThread < MAX_THREAD_COUNT; iThread++)
	{
		m_hWorkThread[iThread] = ::CreateThread(0, 0, WorkerThread, this, 0, &id);
	}

	//스레드 종료용
	m_hEventKillThread = ::CreateEvent(0, TRUE, FALSE, 0);
	// i/o Completion port(IOCP) 핸들생성
	// iocp를 사용하면 다른스레드에서 비동기결과확인가능 
	m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	// iocp 핸들에 바인딩
	::CreateIoCompletionPort(m_hReadFile, m_hIOCP, 1111, 0); // 1111키를 통지한다.(완료키)
	::CreateIoCompletionPort(m_hWriteFile, m_hIOCP,	2222, 0);

	ZeroMemory(&m_hReadOV,sizeof(OVERLAPPED));
	ZeroMemory(&m_hWriteOV, sizeof(OVERLAPPED));

	return true;
}
bool JIOCP::Frame()
{
	WaitForRead();
	WaitForMultipleObjects(MAX_THREAD_COUNT, m_hWorkThread, TRUE, INFINITE); // 전체 Thread 종료 기다림(TRUE)
	return true;
}

bool JIOCP::Release()
{
	SAFE_CLOSE_HANDLE(m_hReadFile);
	SAFE_CLOSE_HANDLE(m_hWriteFile);
	SAFE_CLOSE_HANDLE(m_hIOCP);
	SAFE_CLOSE_HANDLE(m_hEventKillThread);
	return true;
}
JIOCP::JIOCP()
{
	m_hReadFile = 0;
	m_hWriteFile = 0;
}
JIOCP::~JIOCP()
{

}