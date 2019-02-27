#include "windows.h"
#include "iostream"
using namespace std;

CHAR* g_Buffer;
DWORD Load(const TCHAR* pszFileName)
{
	HANDLE hRead = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	LARGE_INTEGER  FileSize = { 0, };
	DWORD TotalByte = 0;
	if (hRead != NULL)
	{

		GetFileSizeEx(hRead, &FileSize);
		TotalByte = FileSize.LowPart;
		g_Buffer = new char[TotalByte];
		if (g_Buffer == NULL)
		{
			return 0;
		}
		DWORD dwReadSize = 0;
		OVERLAPPED ReadOv;
		ZeroMemory(&ReadOv, sizeof(OVERLAPPED));
		BOOL bRet = ReadFile(hRead, g_Buffer, TotalByte, &dwReadSize, &ReadOv);
		if (bRet == FALSE)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				cout << "Loading..." << endl;
			}
		}
		else
		{
			cout << "Read" << endl;
		}
		while (TRUE)
		{
			DWORD dwRet = WaitForSingleObject(hRead, 0);

			if (dwRet == WAIT_OBJECT_0)
			{
				DWORD dwByte;
				BOOL bRet = GetOverlappedResult(hRead, &ReadOv, &dwByte, FALSE);
				if (dwByte >= TotalByte)
				{
					// 다읽음
					break;
				}
			}
			else if (dwRet == WAIT_TIMEOUT)
			{
				DWORD dwByte;
				BOOL bRet = GetOverlappedResult(hRead, &ReadOv, &dwByte, FALSE);
				if (bRet == FALSE)
				{
					if (GetLastError() == ERROR_IO_INCOMPLETE)
					{
						cout << "읽는중";
					}
				}
				else if(bRet == TRUE)
				{
					//다읽음
					break;
				}
				else
				{
					cout << "ERROR";
				}
			}
		}
	}
	CloseHandle(hRead);
	return TotalByte;
}

void main()
{
	DWORD total = Load(L"Samplee.txt");

	HANDLE hWrite = CreateFile(L"SampleeCopy.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);

	if (hWrite != NULL)
	{
		DWORD dwWrite = 0;
		OVERLAPPED WriteOv;
		ZeroMemory(&WriteOv, sizeof(OVERLAPPED));
		BOOL bRet = WriteFile(hWrite, g_Buffer, total, &dwWrite, &WriteOv);
		if (bRet == FALSE)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				cout << "Loading...";
			}
		}
		else
		{
			cout << "출력완료 ";
		}
		while (TRUE)
		{
			DWORD dwRet = WaitForSingleObject(hWrite, 0);

			if (dwRet == WAIT_OBJECT_0)
			{
				DWORD WriteByte;
				BOOL bRet = GetOverlappedResult(hWrite, &WriteOv, &WriteByte, FALSE);
				cout << "Write Clear";
				break;
			}
			else if (dwRet == WAIT_TIMEOUT)
			{
				DWORD WriteByte;
				BOOL bRet = GetOverlappedResult(hWrite, &WriteOv, &WriteByte, FALSE);
				if (bRet == FALSE)
				{
					if(GetLastError() == ERROR_IO_INCOMPLETE)
					cout << "Write...";
				}
				else
				{
					cout << "Write Clear";
					break;
				}
			}
			else
			{
				cout << "Write ERROR";
			}
		}
	}
	CloseHandle(hWrite);
}