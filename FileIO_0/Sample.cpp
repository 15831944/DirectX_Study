#include "windows.h"
#include <iostream>
using namespace std;
void main()
{
	HANDLE hWrite = CreateFile(L"test.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, 
		CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);
	
	OVERLAPPED WriteOL;
	ZeroMemory(&WriteOL, sizeof(OVERLAPPED));
	if (hWrite != NULL)
	{
		TCHAR szWriteBuf[1024] = L"KGCA";
		DWORD dwWriteByte = sizeof(szWriteBuf);
		DWORD dwWrite = 0;
		BOOL bWrite = WriteFile(hWrite, szWriteBuf, dwWriteByte, &dwWrite, &WriteOL);
		wcout << "Write" << endl;
	}
	CloseHandle(hWrite);

	HANDLE hRead = CreateFile(L"test.txt", GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

	OVERLAPPED ReadOL;
	ZeroMemory(&ReadOL, sizeof(OVERLAPPED));
	TCHAR szReadBuf[1024] = { 0, };
	DWORD dwReadByte = sizeof(szReadBuf);
	DWORD dwRead = 0;
	if (hRead != NULL)
	{
		BOOL bRead = ReadFile(hRead, szReadBuf, dwReadByte, &dwRead, &ReadOL);
		wcout << szReadBuf << " Read" << endl;
	}
	CloseHandle(hRead);

}