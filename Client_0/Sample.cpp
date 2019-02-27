#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"
#include "stdio.h"
#include "conio.h"
#pragma comment(lib,"ws2_32.lib")

void main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.S_un.S_addr = inet_addr("222.112.233.175");
	sa.sin_port = htons(10000);
	int iRet = connect(sock, (sockaddr*)&sa, sizeof(sa));
	int iCount = 0;
	u_long on = TRUE;
	ioctlsocket(sock, FIONBIO, &on);
	char buffer[256] = { 0, };
	while (1)
	{
		
		if (_kbhit()==1)
		{
			int iValue = _getche();
			if (iValue == 0)	continue;
			if (iValue == '\r')
			{
				//system("cls");
				//fgets(buffer, sizeof(char) * 256, stdin);
				int iBufSize = strlen(buffer);
				int iSendByte = send(sock, buffer, iBufSize, 0);
				iCount = 0;
				ZeroMemory(buffer, sizeof(char) * 256);
				if (iSendByte == SOCKET_ERROR)
				{
					if (iSendByte == 0)
					{
						break;
					}
				}
			}
			else
			{
				buffer[iCount++] = iValue;
			}
		}
		else
		{
			int iRecvByte = recv(sock, buffer, sizeof(char) * 256, 0);
			if (iRecvByte == SOCKET_ERROR)
			{
				continue;
			}
			else
			{
				printf("%s\n", buffer);
				ZeroMemory(buffer, sizeof(char) * 256);
			}
			if (iRecvByte == 0)
			{
				printf("서버 실행종료\n");
				break;
			}
		}
	}
	if (iRet = SOCKET_ERROR) return;
	closesocket(sock);
	WSACleanup();
}