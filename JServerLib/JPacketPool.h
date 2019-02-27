#pragma once
#include "JThread.h"
#include "JStreamPacket.h"
class JPacketPool : public JSingleton<JPacketPool>
{
private:
	friend class JSingleton<JPacketPool>;
//public:
//	list<PACKET> m_PacketList;
//public:
//	bool	ProcessWork(PACKET* pUserData);
public:
	JPacketPool();
	virtual ~JPacketPool();
};
#define I_Pool JPacketPool::GetInstance()