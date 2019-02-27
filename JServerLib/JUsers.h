#pragma once
#include "JPacketPool.h"
class JUsers : public JServerObject
{
public:
	JStreamPacket m_StreamPacket;
	SOCKET m_Sock;
	SOCKADDR_IN m_Addr;
public:
	bool Run();
	void AddPacket(PACKET& packet);
	void DelUser(SOCKET sock);
public:
	JUsers();
	virtual ~JUsers();
};
