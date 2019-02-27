#include "JAcceptor.h"
#include "JSvrIOCP.h"
#include "JDebugLog.h"
#include "JSessionMgr.h"
bool JAcceptor::Init()
{
	return true;
}
bool JAcceptor::SetSockOpt()
{
	int iRet;
	int optval = 1;
	iRet = setsockopt(m_ListenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));
	if (iRet == SOCKET_ERROR)
	{
		I_Debug.PushError();
		return false;
	}
	char cFlag = 1;
	iRet = setsockopt(m_ListenSocket, IPPROTO_TCP,TCP_NODELAY, &cFlag, sizeof(char));
	if (iRet == SOCKET_ERROR)
	{
		I_Debug.PushError();
		return false;
	}
	linger optLinger;
	int iLen = sizeof(int);
	getsockopt(m_ListenSocket, SOL_SOCKET, SO_LINGER, (char*)&optLinger, &iLen);
	optLinger.l_linger = 1000;
	optLinger.l_onoff = 1;
	setsockopt(m_ListenSocket, SOL_SOCKET, SO_LINGER, (char*)&optLinger, sizeof(linger));
	C_STR msg = "linger Enable("; msg += to_string(optLinger.l_linger); msg += ")";
	msg.clear();

	int iRecvSize, iSendSize;
	iLen = sizeof(iRecvSize);

	getsockopt(m_ListenSocket, SOL_SOCKET, SO_RCVBUF, (char*)&iRecvSize, &iLen);
	getsockopt(m_ListenSocket, SOL_SOCKET, SO_SNDBUF, (char*)&iSendSize, &iLen);
	msg = "RecvBufferSize("; msg += to_string(iRecvSize); msg += ")";
	I_Debug.PushError(msg);
	msg.clear();

	msg = "SendBufferSize("; msg += to_string(iSendSize); msg += ")";
	I_Debug.PushError(msg);
	return true;
}
bool JAcceptor::Set(int port, const char* address)
{
	int iRet;
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	m_ListenSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (!SetSockOpt()) return false;

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	if (address == 0)
		sa.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	else
		sa.sin_addr.S_un.S_addr = inet_addr(address);
	sa.sin_port = htons(port);
	iRet = bind(m_ListenSocket, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		I_Debug.PushError(WSAGetLastError());
		return false;
	}
	iRet = listen(m_ListenSocket, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return false;

	CreateThread();
	return true;
}

bool JAcceptor::Run()
{
	int iRet = 0;
	C_STR msg;
	SOCKET clientsock;
	SOCKADDR_IN client;
	ZeroMemory(&client, sizeof(client));
	int len = sizeof(client);
	while (m_bStarted)
	{
		clientsock = accept(m_ListenSocket, (sockaddr*)&client, &len);
		if (iRet == SOCKET_ERROR)
		{
			I_Debug.PushError(WSAGetLastError());
			return false;
		}
		JSession* pSess = new JSession;
		pSess->Set(clientsock, client);
		I_Session.AddUser(pSess);
		I_IOCP.Bind((HANDLE)clientsock, (ULONG_PTR)pSess);


		msg += "Enter Session (IP : "; msg += inet_ntoa(client.sin_addr); 
		msg += " Port : "; msg += to_string(ntohs(client.sin_port)); msg += ")"; 
		I_Debug.PushError(msg); 
		msg.clear();
	}
	return true;
}
bool JAcceptor::Frame()
{
	WaitForSingleObject((HANDLE)m_hThread, INFINITE);
	return true;
}
bool JAcceptor::Release()
{
	WSACleanup();
	return true;
}

JAcceptor::JAcceptor()
{
}


JAcceptor::~JAcceptor()
{
}
