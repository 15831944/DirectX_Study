#include "JPacketPool.h"
#include "JSessionMgr.h"
#include "JDebugLog.h"
bool JPacketPool::Run()
{
	while (TRUE)
	{
		list<PACKET>::iterator ITOR;
		for (ITOR = m_PacketList.begin(); ITOR != m_PacketList.end(); ITOR++)
		{
			PACKET* pPacket = &(*ITOR);
			switch (pPacket->packet.ph.type)
			{
				case PACKET_CHAT_MSG:
				{
					C_STR msg = "GetChatMSG("; msg += pPacket->packet.msg; msg.pop_back(); msg += ")";
					I_Debug.PushError(msg);
					I_Session.BroadCast(pPacket->packet);
					m_PacketList.erase(ITOR);
				}break;
				case PACKET_CHAT_NAME_ACK:
				{
				}break;
			}
			if (m_PacketList.size() <= 0) break;
		}
	}
}
bool JPacketPool::ProcessWork()
{
	return true;
}
bool JPacketPool::AddPacket(PACKET& packet)
{
	m_PacketList.push_back(packet);
	return true;
}

JPacketPool::JPacketPool()
{
	CreateThread();
}


JPacketPool::~JPacketPool()
{
}
