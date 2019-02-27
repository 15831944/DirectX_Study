#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"
#include "stdio.h"
#include "conio.h"
#pragma comment(lib,"ws2_32.lib")
//afsdfd
void main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.S_un.S_addr = inet_addr("192.168.0.63");
	sa.sin_port = htons(10000);
	int iRet = bind(sock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) return;
	iRet = listen(sock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return;
	SOCKET clientsock;
	SOCKADDR_IN client;
	ZeroMemory(&client, sizeof(client));
	int len = sizeof(client);
	while (1)
	{
		//클라가 연결되면 accept반환
		clientsock = accept(sock, (sockaddr*)&client, &len);
		printf("접속한 사람 ip : %s, port : %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		while (1)
		{
			char buffer[256] = { 0, };
			int iRecvByte = recv(clientsock, buffer, sizeof(char) * 256, 0);
			if (iRecvByte == SOCKET_ERROR || iRecvByte == 0)
			{
				printf("클라 접속종료 ip : %s, port : %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
				break;
			}
			printf("%s\n", buffer);
			int iSendByte = send(clientsock, buffer, sizeof(char) * 256, 0);
			if (iSendByte == SOCKET_ERROR || iSendByte == 0)
			{
				printf("접속 종료\n");
				break;
			}
		}
		closesocket(clientsock);
	}
	closesocket(sock);
	WSACleanup();
	_getch();
}