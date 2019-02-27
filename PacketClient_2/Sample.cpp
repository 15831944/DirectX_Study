#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"
#include "stdio.h"
#include "conio.h"
#include "process.h"
#include "JProtocol.h"
#include <iostream>
#include "string"
#include <tchar.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
CRITICAL_SECTION g_Crit;
bool bPlay = false;

unsigned  int _stdcall KeyInputProcex(LPVOID arg)
{
	printf("\n[보낼메세지] : ");
	SOCKET sock = (SOCKET)arg;
	while (TRUE)
	{
		if (!bPlay)  continue;
		char buffer[256] = { 0, };
		UPACKET packet;
		ZeroMemory(&packet, sizeof(UPACKET));
		fgets(buffer, 256, stdin);
		if (buffer[0] == '\n')
		{
			continue;
		}
		int iBufSize = strlen(buffer);
		int iSendByte = 0;
		memcpy(&packet.msg, buffer, iBufSize);
		packet.LEN = strlen(packet.msg) + PACKET_HEADER_SIZE;
		packet.TYPE = PACKET_CHAT_MSG;
		iSendByte += send(sock, (char*)&packet, packet.LEN, 0);
		while (iSendByte < packet.LEN)
		{
			iSendByte += send(sock, (char*)&packet, packet.LEN, 0);
		}
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
unsigned int _stdcall RecvProcex(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	while (TRUE)
	{
		if (!bPlay)  continue;
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
					printf("\n[보낼메세지] : ");
				}break;

				case PACKET_CHAT_NAME_ACK:
				{
					UPACKET packet;
					//printf("\n%s", pPacket->msg);
					char NameBuf[] = "이준환 ";
					packet.ph.len = strlen(NameBuf) + PACKET_HEADER_SIZE;
					packet.ph.type = PACKET_CHAT_NAME_REQ;
					memcpy(packet.msg, NameBuf, packet.ph.len);
					int iSendSize = send(sock, (char*)&packet, packet.ph.len, 0);
					printf("\n[보낼메세지] : ");
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
	int ip = -1;
	std::cout << "ip  : 192.168.0.";
	std::cin >> ip;
	string strIP = "192.168.0.";
	strIP += to_string(ip);
	bPlay = true;

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET ListenSock;
	ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.S_un.S_addr = inet_addr(strIP.c_str());
	sa.sin_port = htons(10000);
	int iRet = connect(ListenSock, (sockaddr*)&sa, sizeof(sa));
	//u_long on = TRUE;
	//ioctlsocket(ListenSock, FIONBIO, &on);

	InitializeCriticalSection(&g_Crit);
	unsigned int iThreadID;
	unsigned long RecvInput = _beginthreadex(NULL, 0, RecvProcex, (LPVOID)ListenSock, 0, &iThreadID);
	unsigned long KeyInput = _beginthreadex(NULL, 0, KeyInputProcex, (LPVOID)ListenSock, 0, &iThreadID);

	//대기함수
	WaitForSingleObject((HANDLE)RecvInput, INFINITE);
	WaitForSingleObject((HANDLE)KeyInput, INFINITE);
	DeleteCriticalSection(&g_Crit);

	CloseHandle((HANDLE)KeyInput);
	CloseHandle((HANDLE)RecvInput);
	closesocket(ListenSock);
	WSACleanup();
}