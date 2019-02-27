#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "winsock2.h"
#include "stdio.h"
#include "conio.h"
#include "vector"
#include "list"
#include "string"
#include "process.h"
#include "JPacket.h"
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
bool ListDelete(std::list<JUser>::iterator ITOR);
unsigned int _stdcall Recv(LPVOID arg);
bool ListAdd(SOCKET clientsock, SOCKADDR_IN client);
unsigned int _stdcall Accept(LPVOID arg);
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
	sa.sin_addr.S_un.S_addr = INADDR_ANY;
	sa.sin_port = htons(10000);
	int iRet = bind(listenSocket, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) return false;
	iRet = listen(listenSocket, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return false;

	u_long on = TRUE;
	ioctlsocket(listenSocket, FIONBIO, &on);
	return true;
}
unsigned int _stdcall Recv(LPVOID arg)
{
	std::list<JUser>::iterator ITOR;
	while (TRUE)
	{
		EnterCriticalSection(&g_Crit); // 진입
		//JPacket packet(PACKET_PLAYERINFO_ACK);
		//PLAYER_DATA data;
		//memcpy(data.m_szName, "dddz", 5);
		//data.m_fDmg = 5;
		//data.m_fSpeed = 6;
		//packet << data.m_szName <<data.m_fDmg << data.m_fSpeed;

		//JPacket aaaa(PACKET_PLAYERINFO_ACK);
		//PLAYER_DATA aaa;
		//memset(&aaa, 0, sizeof(PLAYER_DATA));
		//packet >> aaaa.m_szBuffer;


		for (ITOR = List.begin(); ITOR != List.end(); ITOR++)
		{
			JUser User = (*ITOR);
			(*ITOR).m_iRecvSize = recv((*ITOR).m_Socket, (*ITOR).m_szBuffer, sizeof(char) * 256, 0);
			if ((*ITOR).m_iRecvSize == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					ListDelete(ITOR);
					break;
				}
			}
			else
			{
				printf("[%s] : %s \n", (*ITOR).m_szName, (*ITOR).m_szBuffer);
			}
			if ((*ITOR).m_iRecvSize == 0)
			{
				ListDelete(ITOR);
				break;
			}
		}
		for (ITOR = List.begin(); ITOR != List.end(); ITOR++)
		{
			std::list<JUser>::iterator ITORAll;
			for (ITORAll = List.begin(); ITORAll != List.end(); ITORAll++)
			{
				string Temp = "[";
				Temp += (*ITOR).m_szName;
				Temp += "] : ";
				Temp += (*ITOR).m_szBuffer;
				int len = strlen(Temp.c_str());
				if (len == strlen(Temp.c_str()) - strlen((*ITOR).m_szBuffer))
				{
					continue;
				}
				(*ITORAll).m_iSendSize = send((*ITORAll).m_Socket, Temp.c_str(), len, 0);
				if ((*ITORAll).m_iSendSize == SOCKET_ERROR)
				{
					break;
				}
			}
			ZeroMemory((*ITOR).m_szBuffer, sizeof(char) * 256);
		}
		Sleep(1);
		LeaveCriticalSection(&g_Crit); // 진입
	}
	return true;
}
bool ListAdd(SOCKET clientsock, SOCKADDR_IN client)
{
	JUser user;
	user.m_Socket = clientsock;
	user.m_Addr = client;
	char m_szBuffer[256] = "이름입력 : ";
	int length = strlen(m_szBuffer);
	int SendSize = send(clientsock, m_szBuffer, length, 0);
	while (user.m_szName[0] == '\0')
	{
		length = strlen(m_szBuffer);
		int RecvSize = recv(clientsock, user.m_szName, length, 0);
		if (RecvSize == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return false;
			}
		}
	}
	user.m_szName[strlen(user.m_szName) - 1] = 0;
	printf("[%s]님 입장     IP : %s     PORT : %d \n", user.m_szName, inet_ntoa(user.m_Addr.sin_addr), ntohs(user.m_Addr.sin_port));
	List.push_back(user);
	return true;
}
bool ListDelete(std::list<JUser>::iterator ITOR)
{
	printf("[%s]님 탈퇴     IP : %s     PORT : %d \n", (*ITOR).m_szName, inet_ntoa((*ITOR).m_Addr.sin_addr), ntohs((*ITOR).m_Addr.sin_port));
	closesocket((*ITOR).m_Socket);
	List.erase(ITOR);
	return true;
}
unsigned int _stdcall Accept(LPVOID arg)
{
	SOCKET ListenSocket = (SOCKET)arg;
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
			Sleep(1);
			continue;
		}
		else
		{
			ListAdd(clientsock, client);
			Sleep(1);
		}
	}
	return 0;
}
void main()
{
	Init(ListenSocket);
	InitializeCriticalSection(&g_Crit);

	unsigned int iThreadID;

	unsigned long AcceptThread = _beginthreadex(NULL, 0, Accept, (LPVOID)ListenSocket, 0, &iThreadID);
	unsigned long RecvThread = _beginthreadex(NULL, 0, Recv, (LPVOID)ListenSocket, 0, &iThreadID);

	WaitForSingleObject((HANDLE)AcceptThread, INFINITE);
	WaitForSingleObject((HANDLE)RecvThread, INFINITE);

	DeleteCriticalSection(&g_Crit);
	closesocket(ListenSocket);
	WSACleanup();
	_getch();
}
/*
Sleep(); => 넣어주면 스레드 스위칭되는 빈도가 비슷해진다
*/