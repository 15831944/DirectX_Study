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
	// (������, ���н�) SO_REUSEADDR 
	// (������) SO_EXCLUSIVEADDRUSE
	iRet = setsockopt(m_ListenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval));//����
	if (iRet == SOCKET_ERROR)
	{
		I_Debug.PushError();
		return false;
	}
	// �ٸ� ���μ������� �ش� ip�� addr�� ��� ���ϰ� �Ѵ�.
	//iRet = setsockopt(m_ListenSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char*)&optval, sizeof(optval));//����
	//if (iRet == SOCKET_ERROR)
	//{
	//	I_Debug.PushError();
	//	return false;
	//}
	// TCP -> Nagle �˰���(���� ��Ŷ�� ��Ƽ� �ѹ��� �����ϴ� ��� :: Default) -> ���ӿ��� ������(������Ŷ�������� ��������)
	// NODELAY -> Nagle �˰����� �Ⱦ��ڴ�.
	char cFlag = 1;
	iRet = setsockopt(m_ListenSocket, IPPROTO_TCP,TCP_NODELAY, &cFlag, sizeof(char));
	if (iRet == SOCKET_ERROR)
	{
		I_Debug.PushError();
		return false;
	}
	// ���ſɼ� :: ���ٺ��� �޼��� ó��
	// ������ ���� �� ������ �����Ͱ� ������ �� ���������� blocking ó�� �Ѵ�.
	linger optLinger;
	int iLen = sizeof(int);
	getsockopt(m_ListenSocket, SOL_SOCKET, SO_LINGER, (char*)&optLinger, &iLen);

	// ������ ���� 
	//////////////////////////////////////�帧//////////////////////////////////
	/////////////////////////////////////////////Ŭ�� -> closesock ���� shutdown
	// Ŭ���̾�Ʈ shutdown(s,SD_SEND) -> sever :: FIN ���׸�Ʈ(��Ŷ) ����
	// ������ -> FD_CLOSE �뺸����
	// ���� -> ���������� ���� �۾�(���ſ��� ����)
	// ���� -> shutdown(s, SD_SEND) -> client :: FIN ���׸�Ʈ(��Ŷ) ����
	// Ŭ���� -> FD_CLOSE �뺸����
	// Ŭ�� ->�������� ���� �޼��� ó��
	// Ŭ��,���� -> closesocket()
	optLinger.l_linger = 1000; // Ÿ�Ӿƿ�(����Ǹ� ���(closesock�����߻���))
	optLinger.l_onoff = 1; // ���ſɼ� ������������ true/false
	setsockopt(m_ListenSocket, SOL_SOCKET, SO_LINGER, (char*)&optLinger, sizeof(linger));
	T_STR msg = _T("linger Enable("); msg += to_wstring(optLinger.l_linger); msg += _T(")");
	msg.clear();

	// get recv,send ũ��
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
		I_IOCP.Bind((HANDLE)clientsock, (ULONG_PTR)pUser); // Key���� ����Ŭ����


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
