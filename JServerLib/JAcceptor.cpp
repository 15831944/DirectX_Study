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
	// (리눅스, 유닉스) SO_REUSEADDR 
	// (윈도우) SO_EXCLUSIVEADDRUSE
	iRet = setsockopt(m_ListenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));//재사용
	if (iRet == SOCKET_ERROR)
	{
		I_Debug.PushError();
		return false;
	}
	// 다른 프로세스에서 해당 ip와 addr을 사용 못하게 한다.
	//iRet = setsockopt(m_ListenSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char*)&optval, sizeof(optval));//재사용
	//if (iRet == SOCKET_ERROR)
	//{
	//	I_Debug.PushError();
	//	return false;
	//}
	// TCP -> Nagle 알고리즘(작은 패킷을 모아서 한번에 전송하는 방식 :: Default) -> 게임에서 부적합(작은패킷도무조건 보내야함)
	// NODELAY -> Nagle 알고리즘을 안쓰겠다.
	char cFlag = 1;
	iRet = setsockopt(m_ListenSocket, IPPROTO_TCP,TCP_NODELAY, &cFlag, sizeof(char));
	if (iRet == SOCKET_ERROR)
	{
		I_Debug.PushError();
		return false;
	}
	// 링거옵션 :: 못다보낸 메세지 처리
	// 소켓을 닫을 때 미전송 데이터가 있으면 다 보낼때까지 blocking 처리 한다.
	linger optLinger;
	int iLen = sizeof(int);
	getsockopt(m_ListenSocket, SOL_SOCKET, SO_LINGER, (char*)&optLinger, &iLen);

	// 종료대기 여부 
	//////////////////////////////////////흐름//////////////////////////////////
	/////////////////////////////////////////////클라 -> closesock 전에 shutdown
	// 클라이언트 shutdown(s,SD_SEND) -> sever :: FIN 세그먼트(패킷) 전송
	// 서버측 -> FD_CLOSE 통보받음
	// 서버 -> 남은데이터 전송 작업(링거에서 결정)
	// 서버 -> shutdown(s, SD_SEND) -> client :: FIN 세그먼트(패킷) 전송
	// 클라측 -> FD_CLOSE 통보받음
	// 클라 ->서버에서 보낸 메세지 처리
	// 클라,서버 -> closesocket()
	optLinger.l_linger = 1000; // 타임아웃(경과되면 폐기(closesock에서발생함))
	optLinger.l_onoff = 1; // 링거옵션 쓸건지말건지 true/false
	setsockopt(m_ListenSocket, SOL_SOCKET, SO_LINGER, (char*)&optLinger, sizeof(linger));
	T_STR msg = _T("linger Enable("); msg += to_wstring(optLinger.l_linger); msg += _T(")");
	msg.clear();

	// get recv,send 크기
	int iRecvSize, iSendSize;
	iLen = sizeof(iRecvSize);

	getsockopt(m_ListenSocket, SOL_SOCKET, SO_RCVBUF, (char*)&iRecvSize, &iLen);
	getsockopt(m_ListenSocket, SOL_SOCKET, SO_SNDBUF, (char*)&iSendSize, &iLen);
	msg = _T("RecvBufferSize("); msg += to_wstring(iRecvSize); msg += _T(")");
	I_Debug.PushError(msg);
	msg.clear();

	msg = _T("SendBufferSize("); msg += to_wstring(iSendSize); msg += _T(")");
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
		sa.sin_addr.S_un.S_addr = htonl(INADDR_ANY);// InetPton(AF_INET,INADDR_ANY, &sa.sin_addr)
	else
		sa.sin_addr.S_un.S_addr = inet_addr(address);// InetPton(AF_INET,address, &sa.sin_addr)
	sa.sin_port = htons(port);
	iRet = bind(m_ListenSocket, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		I_Debug.PushError(WSAGetLastError());
		return false;
	}
	iRet = listen(m_ListenSocket, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return false;

	//u_long on = TRUE;
	//ioctlsocket(m_ListenSocket, FIONBIO, &on);
	CreateThread();
	return true;
}

bool JAcceptor::Run()
{
	int iRet = 0;
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
		JUser* pUser = new JUser;
		pUser->Set(clientsock, client);
		I_Session.AddUser(pUser);
		I_IOCP.Bind((HANDLE)clientsock, (ULONG_PTR)pUser); // Key값을 유저클래스


		C_STR msg = inet_ntoa(client.sin_addr); msg += to_string(ntohs(client.sin_port)); msg += ")"; msg.clear();

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
