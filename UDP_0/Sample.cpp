#include "winsock2.h"
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#define MAX_BUF_SIZE 1024*2
void main()
{
	//HANDLE m_hWriteFile = CreateFile(L"Sample.iso", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.S_un.S_addr = INADDR_ANY;
	sa.sin_port = htons(10000);
	bind(sock, (sockaddr*)&sa, sizeof(sa));

	SOCKADDR_IN peeraddr;
	char buf[MAX_BUF_SIZE] = { 0, };
	int addrlen = sizeof(peeraddr);
	while (TRUE)
	{
		int iRet = recvfrom(sock, buf, MAX_BUF_SIZE, 0, (SOCKADDR*)&peeraddr, &addrlen);
		buf[iRet] = 0;
		char buff[] = "end";
		cout << buf << endl;
		if (_stricmp(buf, "end") == 0)
		{
			break;
		}
		DWORD WriteBytes = 0;
		//WriteFile(m_hWriteFile, buf, iRet, &WriteBytes, NULL);
	}
	//CloseHandle(m_hWriteFile);
	closesocket(sock);
	WSACleanup();
}