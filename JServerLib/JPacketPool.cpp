#include "JPacketPool.h"

//bool JPacketPool::ProcessWork(PACKET* pUserData)
//{
	//list<PACKET>::iterator ITOR;
	//for (ITOR = m_PacketList.begin(); ITOR != m_PacketList.end(); ITOR++)
	//{
	//	PACKET* pUser = (PACKET*)&(*ITOR);
	//	UPACKET* pPacket = &(pUser->packet);
	//	switch (pPacket->ph.type)
	//	{
	//	case PACKET_CHAT_MSG:
	//	{

	//	}break;
	//	case PACKET_CHAT_NAME_ACK:
	//	{

	//	}break;
	//	}
	//}
	//m_PacketList.clear();
//	return true;
//}

JPacketPool::JPacketPool()
{
}


JPacketPool::~JPacketPool()
{
}
