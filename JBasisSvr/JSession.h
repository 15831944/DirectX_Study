#pragma once
#include "JSynchronize.h"
#include "JStreamPacket.h"
typedef struct _OVERLAPPED2 : OVERLAPPED
{
	enum { MODE_RECV = 0, MODE_SEND = 1 };
	int m_iFlag;
	_OVERLAPPED2()
	{
		m_iFlag = MODE_RECV;
	}
}OVERLAPPEDEX;

class JSession
{
public:
	SOCKET m_Sock;
	SOCKADDR_IN m_Addr;
	OVERLAPPEDEX m_ov;
	WSABUF m_WSABuffer;
	char m_strBuffer[2048];
	JStreamPacket m_Stream;
public:
	int WaitForPacketRecv();
	bool Run();
	bool Release();
	void Set(SOCKET sock, SOCKADDR_IN addr);
	void Dispatch(DWORD dwByteSize, LPOVERLAPPED ov);
public:
	JSession();
	virtual ~JSession();
};
