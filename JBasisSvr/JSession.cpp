#include "JSession.h"
#include "JSessionMgr.h"
#include "JDebugLog.h"
bool JSession::Release()
{
	shutdown(m_Sock, SD_SEND);
	closesocket(m_Sock);
	return true;
}
int JSession::WaitForPacketRecv()
{
	DWORD cbTransferred;
	DWORD flags = 0;
	m_ov.m_iFlag = OVERLAPPEDEX::MODE_RECV;
	m_WSABuffer.buf = m_strBuffer;
	m_WSABuffer.len = 2048;
	int iRet = WSARecv(m_Sock, &m_WSABuffer, 1, &cbTransferred, &flags, (LPOVERLAPPED)&m_ov, NULL);
	if (iRet == SOCKET_ERROR)
	{
		int iError = WSAGetLastError();
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			I_Debug.PushError(iError);
		}
	}
	return iRet;
}
void JSession::Dispatch(DWORD dwByteSize, LPOVERLAPPED ov)
{
	OVERLAPPEDEX* pOvex = (OVERLAPPEDEX*)ov;
	if (pOvex->m_iFlag == OVERLAPPEDEX::MODE_RECV)
	{
		m_Stream.Put(m_WSABuffer, this->m_Sock);
		ZeroMemory(&m_WSABuffer, sizeof(WSABUF));
	}
	WaitForPacketRecv();
}
void JSession::Set(SOCKET sock, SOCKADDR_IN addr)
{
	m_Sock = sock;
	m_Addr = addr;
}
bool JSession::Run()
{
	//char RecvBuffer[1024] = { 0, };
	//int RecvByte = 0;
	//while (TRUE)
	//{
	//	RecvByte = recv(m_Sock, RecvBuffer, sizeof(RecvBuffer), 0);
	//	if (RecvByte == 0 || RecvByte == SOCKET_ERROR)
	//	{
	//		break;
	//	}
	//	RecvBuffer[RecvByte] = 0;
	//	m_Stream.Put(RecvBuffer, RecvByte, this);
	//}
	//I_Session.DelUser(m_Sock);
	return true;
}

JSession::JSession()
{
}

JSession::~JSession()
{
}