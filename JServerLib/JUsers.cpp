#include "JUsers.h"
#include "JSynchronize.h"
bool JUsers::Run()
{
	char RecvBuffer[1024] = { 0, };
	int RecvByte = 0;
	while (TRUE)
	{
		RecvByte = recv(m_Sock, RecvBuffer, sizeof(RecvBuffer), 0);
		if (RecvByte == 0 || RecvByte == SOCKET_ERROR)
		{
			break;
		}
		//RecvBuffer[RecvByte] = 0;
		m_StreamPacket.Put(RecvBuffer, RecvByte, this);
	}
	DelUser(m_Sock);
	return true;
}
void JUsers::AddPacket(PACKET &packet)
{
	{
		JSynchronize sync(this);
		m_StreamPacket.m_PacketList.push_back(packet);
	}
	//return;
}
void JUsers::DelUser(SOCKET sock)
{
}

JUsers::JUsers()
{
	m_Sock = NULL;
}

JUsers::~JUsers()
{
	closesocket(m_Sock);
}