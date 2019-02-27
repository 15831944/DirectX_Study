#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "winsock2.h"
#include "stdio.h"
#include "conio.h"
#include "vector"
#include "list"
#include "string"
#pragma comment(lib,"ws2_32.lib")
using namespace std;
CRITICAL_SECTION g_Crit;
struct JUser
{
public:
	SOCKET m_Socket;
	char	m_szBuffer[256];
	SOCKADDR_IN m_Addr;
	char	m_szName[256];
	int		m_iRecvSize;
	int		m_iSendSize;
	JUser()
	{
		ZeroMemory(m_szName, sizeof(char) * 256);
		m_Socket = NULL;
		ZeroMemory(m_szBuffer, sizeof(char) * 256);
		ZeroMemory(&m_Addr, sizeof(SOCKADDR_IN));
		m_iRecvSize = 0;
	}
	~JUser() {}
};
std::list<JUser> List;
SOCKET ListenSocket;
bool Init(SOCKET& listenSocket)
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.S_un.S_addr = inet_addr("192.168.0.122");
	sa.sin_port = htons(10000);
	int iRet = bind(listenSocket, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) return false;
	iRet = listen(listenSocket, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return false;

	u_long on = TRUE;
	ioctlsocket(listenSocket, FIONBIO, &on);
	return true;
}
bool Recv()
{
	std::list<JUser>::iterator ITOR;
	for (ITOR = List.begin(); ITOR != List.end(); ITOR++)
	{
		JUser User = (*ITOR);
		(*ITOR).m_iRecvSize = recv((*ITOR).m_Socket, (*ITOR).m_szBuffer, sizeof(char) * 256, 0);
		if ((*ITOR).m_iRecvSize == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				printf("[%s]´Ô Å»Åð     IP : %s     PORT : %d \n", (*ITOR).m_szName, inet_ntoa((*ITOR).m_Addr.sin_addr), ntohs((*ITOR).m_Addr.sin_port));
				closesocket((*ITOR).m_Socket);
				List.erase(ITOR);
				return false;
			}
		}
		else
		{
			printf("[%s] : %s \n", (*ITOR).m_szName, (*ITOR).m_szBuffer);
		}
		if ((*ITOR).m_iRecvSize == 0)
		{
			printf("[%s]´Ô Å»Åð     IP : %s     PORT : %d \n", (*ITOR).m_szName, inet_ntoa((*ITOR).m_Addr.sin_addr), ntohs((*ITOR).m_Addr.sin_port));
			closesocket((*ITOR).m_Socket);
			List.erase(ITOR);
			continue;
		}
	}
	return true;
}
bool Send()
{
	std::list<JUser>::iterator ITOR;
	for (ITOR = List.begin(); ITOR != List.end(); ITOR++)
	{
		std::list<JUser>::iterator ITORAll;
		for (ITORAll = List.begin(); ITORAll != List.end(); ITORAll++)
		{	
			//string Temp = "[";
			//Temp += (*ITOR).m_szName;
			//Temp += "] : ";
			//Temp += (*ITOR).m_szBuffer;
			//int len = strlen(Temp.c_str());
			//if (len == strlen(Temp.c_str()) - strlen((*ITOR).m_szBuffer))
			//{
			//	continue;
			//}
			int length = strlen((*ITOR).m_szBuffer);
			(*ITORAll).m_iSendSize = send((*ITORAll).m_Socket, (*ITOR).m_szBuffer, length, 0);//Temp.c_str(), len, 0);
			if ((*ITORAll).m_iSendSize == SOCKET_ERROR)
			{
				return false;
			}
		}
		ZeroMemory((*ITOR).m_szBuffer, sizeof(char) * 256);
	}
	return true;
}
bool ListAdd(SOCKET clientsock, SOCKADDR_IN client)
{
	JUser user;
	user.m_Socket = clientsock;
	user.m_Addr = client;
	//char m_szBuffer[256] = "ÀÌ¸§ÀÔ·Â : ";
	//int length = strlen(m_szBuffer);
	//int SendSize = send(clientsock, m_szBuffer, length, 0);
	//while (user.m_szName[0] == '\0')
	//{
	//	length = strlen(m_szBuffer);
	//	int RecvSize = recv(clientsock, user.m_szName, length, 0);
	//	if (RecvSize == SOCKET_ERROR)
	//	{
	//		if (WSAGetLastError() != WSAEWOULDBLOCK)
	//		{
	//			return false;
	//		}
	//	}
	//}
	//user.m_szName[strlen(user.m_szName) - 1] = 0;
	printf("[%s]´Ô ÀÔÀå     IP : %s     PORT : %d \n", user.m_szName, inet_ntoa(user.m_Addr.sin_addr), ntohs(user.m_Addr.sin_port));
	List.push_back(user);
	return true;
}
void main()
{
	Init(ListenSocket);
	SOCKET clientsock;
	SOCKADDR_IN client;
	ZeroMemory(&client, sizeof(client));
	int len = sizeof(client);
	while (TRUE)
	{
		clientsock = accept(ListenSocket, (sockaddr*)&client, &len);
		if (clientsock == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				break;
			}
			Recv();
			Send();
			continue;
		}
		ListAdd(clientsock, client);
	}
	DeleteCriticalSection(&g_Crit);
	closesocket(ListenSocket);
	WSACleanup();
	_getch();
}
/*
	Sleep(); => ³Ö¾îÁÖ¸é ½º·¹µå ½ºÀ§ÄªµÇ´Â ºóµµ°¡ ºñ½ÁÇØÁø´Ù
*/