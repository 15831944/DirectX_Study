#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
#define MAX_BUF_SIZE 1024*2
void main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

	BOOL optval = TRUE;
	int iRet = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));
	if (iRet == SOCKET_ERROR)
	{
		return;
	}

	SOCKADDR_IN Sendsa;
	ZeroMemory(&Sendsa, sizeof(Sendsa));
	Sendsa.sin_family = AF_INET;
	Sendsa.sin_addr.S_un.S_addr = inet_addr("235.7.8.9");
	Sendsa.sin_port = htons(10000);
	bind(sock, (sockaddr*)&Sendsa, sizeof(Sendsa));

	ip_mreq mreq;// 멀티캐스트 멤버쉽 가입
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);// 내주소
	mreq.imr_multiaddr.s_addr = inet_addr("235.7.8.9");	// 가입주소
	setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq));

	int addrlen = sizeof(SOCKADDR_IN);
	char sendbuf[] = "치킨..";
	int buflen = sizeof(sendbuf);
	while (TRUE)
	{
		int iRet = sendto(sock, sendbuf, buflen, 0, (SOCKADDR*)&Sendsa, addrlen);
		Sleep(1000);
	}
	setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
	closesocket(sock);
	WSACleanup();
}