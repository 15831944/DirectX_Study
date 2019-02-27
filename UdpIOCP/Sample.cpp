#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#define MAX_BUF_SIZE 2048
#define RECV 0
#define SEND 1
HANDLE g_hIOCP = 0;
char buf[2048] = { 0, };
typedef struct OVex : OVERLAPPED
{
	DWORD dwFlag;
}OVERLAPPEDEx;
DWORD WINAPI WorkerThread(LPVOID arg)
{
	int ret = 0;
	LPDWORD trans;
	ULONG_PTR key;
	OVERLAPPEDEx* ov;
	ov->dwFlag = RECV;
	while (TRUE)
	{
		ret = GetQueuedCompletionStatus(g_hIOCP, trans, &key, (LPOVERLAPPED*)ov, INFINITE);
		if (trans != 0)
		{
			if (key != 0 && ov != 0)
			{
				SOCKET client = (SOCKET)key;

				if (ov->dwFlag == RECV)
				{
					cout << buf << endl;
				}
				if (ov->dwFlag == SEND)
				{

				}
			}
		}
	}
	return 0;
}
void main()
{
	HANDLE hExit = CreateEvent(NULL, FALSE, FALSE, L"Exit");

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

	BOOL optval = TRUE;
	int iRet = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));
	if (iRet == SOCKET_ERROR)
	{
		return;
	}

	SOCKADDR_IN Recvsa;
	ZeroMemory(&Recvsa, sizeof(Recvsa));
	Recvsa.sin_family = AF_INET;
	Recvsa.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	Recvsa.sin_port = htons(10000);
	bind(sock, (sockaddr*)&Recvsa, sizeof(Recvsa));

	ip_mreq mreq;
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	mreq.imr_multiaddr.s_addr = inet_addr("235.7.8.9");
	setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq));

	g_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	CreateIoCompletionPort((HANDLE)sock, g_hIOCP, (DWORD)sock, 0);

	DWORD ReadByte = 0;
	OVERLAPPEDEx ov;
	ZeroMemory(&ov, sizeof(ov));
	ReadFile((HANDLE)sock, buf, 2048, &ReadByte, &ov);

	DWORD id = 0;
	for (int i = 0; i < 5; i++)
	{
		HANDLE h = CreateThread(NULL, 0, WorkerThread, 0, 0, &id);
	}

	WaitForSingleObject(hExit, INFINITE);

	closesocket(sock);
	WSACleanup();
}