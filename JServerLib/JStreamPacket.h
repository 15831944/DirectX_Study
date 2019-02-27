#pragma once
#include "JServerStd.h"
#include "JProtocol.h"
#define MAX_RECV_SIZE 10000

class JStreamPacket
{
//public:
//	list<PACKET> m_PacketList;
//public:
//	UPACKET* m_pPacket;
//	char m_szRecvBuf[MAX_RECV_SIZE];
//public:
//	int  m_iStartPos;
//	int  m_iWritePos;
//	int  m_iReadPos;
//public:
//	void Put(char* RecvBuf, int iSize, JUser* pUser);
public:
	JStreamPacket();
	virtual ~JStreamPacket();
};

