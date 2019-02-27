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

	SOCKADDR_IN Recvsa;
	ZeroMemory(&Recvsa, sizeof(Recvsa));
	Recvsa.sin_family = AF_INET;
	Recvsa.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	Recvsa.sin_port = htons(10000);
	bind(sock, (sockaddr*)&Recvsa, sizeof(Recvsa));

	/* IP_ADD_SOURCE_MEMBERSHIP <-> IP_DROP_SOURCE_MEMBERSHIP */
	ip_mreq mreq;// 멀티캐스트 멤버쉽 가입 ( exclude 방법 )
	// IP_ADD_MEMBERSHIP <-> IP_DROP_MEMBERSHIP
	// IP_BLOCK_SOURCE
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);// 내주소
	mreq.imr_multiaddr.s_addr = inet_addr("235.7.8.9");	// 가입주소
	setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq));

	// 제외
	ip_mreq_source mreqsrc;
	mreqsrc.imr_interface = mreq.imr_interface;
	mreqsrc.imr_multiaddr = mreq.imr_multiaddr;
	mreqsrc.imr_sourceaddr.s_addr = inet_addr("192.168.0.1");
	setsockopt(sock, IPPROTO_IP, IP_BLOCK_SOURCE, (char*)&mreqsrc, sizeof(mreqsrc));

	SOCKADDR_IN peeraddr;
	char buf[MAX_BUF_SIZE] = { 0, };
	int addrlen = sizeof(SOCKADDR_IN);
	while (TRUE)
	{
		iRet = recvfrom(sock, buf, MAX_BUF_SIZE, 0, (SOCKADDR*)&peeraddr, &addrlen);
		buf[iRet] = 0;
		cout << buf << endl;
		if (_stricmp(buf, "end") == 0)
		{
			break;
		}
	}
	setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
	closesocket(sock);
	WSACleanup();
}