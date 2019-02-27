#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"
#include "stdio.h"
#include "conio.h"
#include "process.h"
#pragma comment(lib,"ws2_32.lib")
unsigned  int WINAPI KeyInputProcex(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	while (TRUE)
	{
		char buffer[256] = { 0, };
		fgets(buffer, 256, stdin);
		if (buffer[0] == '\n')
		{
			break;
		}
		int iBufSize = strlen(buffer);
		int iSendByte  = send(sock, buffer, iBufSize, 0);
		if (iSendByte == SOCKET_ERROR || iSendByte == 0)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				printf("=================서버종료=================");
				break;
			}
		}
	}
	closesocket(sock);
	return 0;
}
unsigned int WINAPI RecvProcex(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	while (TRUE)
	{
		char buffer[256] = { 0, };
		int iRecvByte = recv(sock, buffer, sizeof(char) * 256, 0);
		if (iRecvByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				printf("=================서버종료=================");
				break;
			}
			if (iRecvByte == 0)
			{
				break;
			}
		}
		if (iRecvByte > 0)
		{
			printf("\n%s", buffer);
		}
	}
	closesocket(sock);
	return 0;
}
void main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET ListenSock;
	ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.S_un.S_addr = inet_addr("192.168.0.122");
	sa.sin_port = htons(10000);
	int iRet = connect(ListenSock, (sockaddr*)&sa, sizeof(sa));
	u_long on = TRUE;
	ioctlsocket(ListenSock, FIONBIO, &on);

	char buffer[256] = { 0, };
	unsigned int iThreadID;
	unsigned long KeyInput = _beginthreadex(NULL, 0, KeyInputProcex, (LPVOID)ListenSock, 0, &iThreadID);
	unsigned long RecvInput = _beginthreadex(NULL, 0, RecvProcex, (LPVOID)ListenSock, 0, &iThreadID);

	//대기함수
	WaitForSingleObject((HANDLE)RecvInput, INFINITE);
	WaitForSingleObject((HANDLE)KeyInput, INFINITE);

	CloseHandle((HANDLE)KeyInput);
	CloseHandle((HANDLE)RecvInput);
	closesocket(ListenSock);
	WSACleanup();
}