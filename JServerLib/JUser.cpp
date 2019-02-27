#include "JUser.h"
#include "JDebugLog.h"
bool JUser::Release()
{
	shutdown(m_Sock, SD_SEND);
	closesocket(m_Sock);
	return true;
}
int JUser::WaitForPacketRecv()
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
void JUser::Dispatch(DWORD dwByteSize, LPOVERLAPPED ov)
{
	OVERLAPPEDEX* pOvex = (OVERLAPPEDEX*)ov;
	if (pOvex->m_iFlag == OVERLAPPEDEX::MODE_RECV)
	{
		// 스트림패킷 처리 put();
	}
	WaitForPacketRecv();
}
void JUser::Set(SOCKET sock, SOCKADDR_IN addr)
{
	m_Sock = sock;
	m_Addr = addr;
}
bool JUser::Run()
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
	//	//RecvBuffer[RecvByte] = 0;
	//	m_StreamPacket.Put(RecvBuffer, RecvByte, this);
	//}
	//I_UserMgr.DelUser(m_Sock);
	return true;
}
//void JUser::AddPacket(PACKET &packet)
//{
//	//{
//	//	JSynchronize sync(this);
//	//	I_Pool.m_PacketList.push_back(packet);
//	//}
//	return;
//}

JUser::JUser()
{
	//m_Sock = NULL;
	//m_hThread = _beginthreadex(NULL, 0, HandleRunner,
	//	(LPVOID)this, 0, &m_dwThreadID);
}

JUser::~JUser()
{
	//closesocket(m_Sock);
}