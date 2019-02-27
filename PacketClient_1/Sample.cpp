#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"
#include "stdio.h"
#include "conio.h"
#include "process.h"
#include "JProtocol.h"
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
unsigned  int WINAPI KeyInputProcex(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	while (TRUE)
	{
		UPACKET packet;
		ZeroMemory(&packet, sizeof(UPACKET));
		char buffer[256] = { 0, };
		fgets(buffer, 256, stdin);
		if (buffer[0] == '\n')
		{
			break;
		}
		int iBufSize = strlen(buffer);
		int iSendByte = 0;
		memcpy(&packet.msg, buffer, iBufSize);
		packet.LEN = strlen(packet.msg) + PACKET_HEADER_SIZE;
		packet.TYPE = PACKET_CHAT_MSG;
		iSendByte = send(sock, (char*)&packet, packet.LEN, 0);
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
		int iRecvByte = 0;
		int iStartByte = 0;
		int iLen = 0;
		iLen = recv(sock, &buffer[iStartByte], PACKET_HEADER_SIZE - iRecvByte, 0);
		iRecvByte += iLen;
		if (iRecvByte == PACKET_HEADER_SIZE)
		{
			UPACKET* pPacket = (UPACKET*)buffer;
			while (iRecvByte < pPacket->LEN)
			{
				iLen = recv(sock, &buffer[iRecvByte], pPacket->LEN - iRecvByte, 0);
				iRecvByte += iLen;
				if (iLen == 0 || iLen == SOCKET_ERROR)
				{
					break;
				}
			}
			if (iRecvByte == pPacket->LEN)
			{
				UPACKET RecvPacket;
				memset(&RecvPacket, 0, sizeof(RecvPacket));
				memcpy(&RecvPacket, pPacket, pPacket->LEN);
				switch (pPacket->TYPE)
				{
					case PACKET_CHAT_MSG:
					{
						printf("\n[받은메세지] : %s", pPacket->msg);
					}break;
				}
				iStartByte = 0;
				iRecvByte = 0;
			}
		}
		else
		{
			iStartByte += iRecvByte;
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
	sa.sin_addr.S_un.S_addr = inet_addr("192.168.0.28");
	sa.sin_port = htons(10000);
	int iRet = connect(ListenSock, (sockaddr*)&sa, sizeof(sa));
	/*u_long on = TRUE;
	ioctlsocket(ListenSock, FIONBIO, &on);*/

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