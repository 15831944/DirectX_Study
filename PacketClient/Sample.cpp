#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"
#include "stdio.h"
#include "conio.h"
#include "process.h"
#include "JProtocol.h"
#pragma comment(lib,"ws2_32.lib")
unsigned  int WINAPI KeyInputProcex(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	UPACKET packet;
	ZeroMemory(&packet, sizeof(UPACKET));
	while (TRUE)
	{
		char buffer[256] = { 0, };
		fgets(buffer, 256, stdin);
		if (buffer[0] == '\n')
		{
			break;
		}
		int iBufSize = strlen(buffer);
		int iSendByte = 0;
		memcpy(packet.msg, buffer, iBufSize);
		packet.ph.len = strlen(packet.msg) + PACKET_HEADER_SIZE;
		packet.ph.type = PACKET_CHAT_MSG;
		iSendByte = send(sock, (char*)&packet, packet.ph.len, 0);
		if (iSendByte == SOCKET_ERROR || iSendByte == 0)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				printf("=================서버종료=================");
				break;
			}
		}
	}
	return 0;
}
unsigned int WINAPI RecvProcex(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;
	while (TRUE)
	{
		char buf[2048] = { 0, };
		int iRecvByte = 0;
		int iStartByte = 0;
		while (TRUE)
		{
			int iLen = 0;
			iLen = recv(sock, &buf[iStartByte], PACKET_HEADER_SIZE - iRecvByte, 0);
			iRecvByte += iLen;
			if (iRecvByte == PACKET_HEADER_SIZE)
			{
				UPACKET* pPacket = (UPACKET*)&buf;
				while (iRecvByte < pPacket->ph.len)
				{
					iLen = recv(sock, &buf[iRecvByte],pPacket->ph.len - iRecvByte, 0);
					iRecvByte += iLen;
					if (iLen == 0 || iLen == SOCKET_ERROR)
					{
						break;
					}
				}
				if (iRecvByte == pPacket->ph.len)
				{
					UPACKET recvmsg;
					memset(&recvmsg, 0, sizeof(recvmsg));
					memcpy(&recvmsg, pPacket, pPacket->ph.len);
					switch (recvmsg.ph.type)
					{
					case PACKET_CHAT_MSG:
					{
						printf("\n[받은메세지]: %s", recvmsg.msg);
						printf("\n보낼 데이터 입력하시오?");
					}break;
					}
					iStartByte = iRecvByte = 0;
				}
			}
			else
			{
				iStartByte += iRecvByte;
			}
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
	sa.sin_addr.S_un.S_addr = inet_addr("192.168.0.63");
	sa.sin_port = htons(10000);
	int iRet = connect(ListenSock, (sockaddr*)&sa, sizeof(sa));
	//u_long on = TRUE;
	//ioctlsocket(ListenSock, FIONBIO, &on);

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