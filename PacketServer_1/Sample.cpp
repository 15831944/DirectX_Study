#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "winsock2.h"
#include "stdio.h"
#include "conio.h"
#include "vector"
#include "list"
#include "string"
#include <process.h>
#include "JProtocol.h"
#include "JServerPacket.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;
CRITICAL_SECTION g_Crit;
struct JUser
{
public:
	SOCKET m_Socket;
	char	m_szBuffer[256];
	UPACKET m_pPacket;
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
std::list<JUser> List;
SOCKET ListenSocket;
bool ErrorCheck(int iLength)
{
	if (iLength == 0 || iLength == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			return false;
		}
	}
	return true;
}
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
	SOCKET ListenSock = (SOCKET)arg;
	while (TRUE)
	{
		EnterCriticalSection(&g_Crit);
		std::list<JUser>::iterator ITOR;
		for (ITOR = List.begin(); ITOR != List.end(); ITOR++)
		{
			char buffer[256] = { 0, };
			int iRecvByte = 0;
			int iStartByte = 0;
			int iLen = 0;
			// HEADER 4bite 얻어오기
			iLen = recv((*ITOR).m_Socket, &buffer[iStartByte], PACKET_HEADER_SIZE - iRecvByte, 0);
			if (!ErrorCheck(iLen))
			{
				ListDelete(ITOR);
				break;
			}
			iRecvByte += iLen;
			if (iRecvByte == PACKET_HEADER_SIZE)
			{
				// msg 얻기
				UPACKET* pPacket = (UPACKET*)buffer;
				while (iRecvByte < pPacket->ph.len)
				{
					iLen = recv((*ITOR).m_Socket, &buffer[iRecvByte], pPacket->ph.len - iRecvByte, 0);
					iRecvByte += iLen;
					if (!ErrorCheck(iLen))
					{
						ListDelete(ITOR);
						break;
					}
				}
				// 처리
				if (iRecvByte == pPacket->ph.len)
				{
					UPACKET RecvPacket;
					memset(&RecvPacket, 0, sizeof(RecvPacket));
					memcpy(&RecvPacket, pPacket, pPacket->LEN);
					switch (pPacket->TYPE)
					{
					case PACKET_CHAT_MSG:
					{
						std::list<JUser>::iterator ITORAll;
						for (ITORAll = List.begin(); ITORAll != List.end(); ITORAll++)
						{
							(*ITORAll).m_iSendSize = send((*ITORAll).m_Socket, (char*)&RecvPacket, RecvPacket.ph.len, 0);//Temp.c_str(), len, 0);
							if ((*ITORAll).m_iSendSize == SOCKET_ERROR)
							{
								return false;
							}
						}
						printf("\n[%s] : %s", (*ITOR).m_szName, RecvPacket.msg);
						//ZeroMemory(&pPacket->msg, sizeof(pPacket->msg));
					}break;
					case PACKET_CHAT_NAME_REQ:
					{
						int iLength = strlen(pPacket->msg) - 1;
						memcpy((*ITOR).m_szName, pPacket->msg, iLength);
						printf("[%s]님 입장     IP : %s     PORT : %d \n", (*ITOR).m_szName, inet_ntoa((*ITOR).m_Addr.sin_addr), ntohs((*ITOR).m_Addr.sin_port));
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
		Sleep(1);
		LeaveCriticalSection(&g_Crit);
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
	UPACKET upacket;
	char buffer[] = "이름입력 : ";
	memset(&upacket, 0, sizeof(UPACKET));
	upacket.ph.type = PACKET_CHAT_NAME_ACK;
	upacket.ph.len = strlen(buffer) + PACKET_HEADER_SIZE;
	memcpy(&upacket.msg, buffer, upacket.ph.len);

	int iSendSize = send(clientsock, (char*)&upacket, upacket.ph.len, 0);

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

	JServerPacket packet(PACKET_CHAT_MSG);
	PLAYER_DATA data;
	string name = "abdc";
	int iLen = strlen(name.c_str());
	memcpy(data.m_szName, name.c_str(), iLen);
	data.m_iDamage = 1111;
	data.m_fSpeed = 2222.0f;
	packet << data.m_szName << data.m_iDamage << data.m_fSpeed;
	//JServerPacket* RecvPacket = ();
	PLAYER_DATA damage;
	packet >> damage.m_szName >> damage.m_iDamage >> damage.m_fSpeed;
	printf("%s", damage.m_szName);

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