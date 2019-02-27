#include "JStreamPacket.h"
#include "JPacketPool.h"
void JStreamPacket::Put(WSABUF WSABuf, SOCKET sock)
{

	// MAX_RECV_SIZE를 넘었을때 초기화 + 잔여량 보존
	if (m_iWritePos + 256 > MAX_RECV_SIZE)
	{
		char temp[MAX_RECV_SIZE] = { 0, };
		memcpy(temp, &m_szRecvBuf[m_iStartPos], m_iReadPos);
		ZeroMemory(m_szRecvBuf, sizeof(char) * MAX_RECV_SIZE);
		memcpy(m_szRecvBuf, temp, m_iReadPos);

		m_pPacket = (UPACKET*)m_szRecvBuf;
		m_iStartPos = 0;
		m_iWritePos = m_iReadPos;
	}

	// 큰 버퍼에 입력
	memcpy(&m_szRecvBuf[m_iWritePos], WSABuf.buf, 256);
	m_pPacket = (UPACKET*)&m_szRecvBuf[m_iStartPos];
	m_iWritePos += m_pPacket->ph.len;
	m_iReadPos += m_pPacket->ph.len;
	// 짜르기
	if (m_iReadPos >= m_pPacket->ph.len)
	{
		do
		{
			PACKET AddUPacket;
			ZeroMemory(&AddUPacket, sizeof(PACKET));
			memcpy(&AddUPacket, (PACKET*)&m_szRecvBuf[m_iStartPos], m_pPacket->ph.len);

			I_Pool.AddPacket(AddUPacket);
			m_iReadPos -= m_pPacket->ph.len;
			m_iStartPos += m_pPacket->ph.len;
			if (m_iReadPos < PACKET_HEADER_SIZE) break;
			if (AddUPacket.packet.ph.len == WSABuf.len) break;

			m_pPacket = (UPACKET*)&m_szRecvBuf[m_iStartPos];
		} while (m_iReadPos >= m_pPacket->ph.len);
	}
}

JStreamPacket::JStreamPacket()
{
	m_pPacket = new UPACKET;
	ZeroMemory(m_pPacket, sizeof(UPACKET));
	ZeroMemory(m_szRecvBuf, sizeof(char)*MAX_RECV_SIZE);
	m_iStartPos = 0;
	m_iWritePos = 0;
	m_iReadPos = 0;
}


JStreamPacket::~JStreamPacket()
{
}
