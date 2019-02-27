#pragma once
#include "JThread.h"
#include "JStreamPacket.h"
class JPacketPool : public JSingleton<JPacketPool>, public JThread
{
private:
	friend class JSingleton<JPacketPool>;
public:
	list<PACKET> m_PacketList;
public:
	bool	ProcessWork();
	bool	AddPacket(PACKET& packet);
	bool	Run();
public:
	JPacketPool();
	virtual ~JPacketPool();
};
#define I_Pool JPacketPool::GetInstance()