#include "JStreamPacket.h"
void JStreamPacket::Put(char* RecvBuf, int iSize, JUser* pUser)
{
	// MAX_RECV_SIZE를 넘었을때 초기화 + 잔여량 보존
	if (m_iWritePos + iSize > MAX_RECV_SIZE)
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
	memcpy(&m_szRecvBuf[m_iWritePos], RecvBuf, iSize);
	m_iWritePos += iSize;
	m_iReadPos += iSize;

	m_pPacket = (UPACKET*)m_szRecvBuf[m_iStartPos];
	// 짜르기
	if (m_iReadPos >= m_pPacket->ph.len)
	{
		do
		{
			PACKET add;
			ZeroMemory(&add, sizeof(PACKET));
			memcpy(&add.packet, (UPACKET*)&m_szRecvBuf[m_iStartPos], m_pPacket->ph.len);
			add.pUser = pUser;

			pUser->AddPacket(add);
			m_iReadPos -= m_pPacket->ph.len;
			m_iStartPos += m_pPacket->ph.len;
			if (m_iReadPos < PACKET_HEADER_SIZE) break;
			if (add.packet.ph.len == iSize) break;

			m_pPacket = (UPACKET*)m_szRecvBuf[m_iStartPos];
		} while (m_iReadPos >= m_pPacket->ph.len);
	}
}

JStreamPacket::JStreamPacket()
{
	m_pPacket = NULL;
	ZeroMemory(m_szRecvBuf, sizeof(char)*MAX_RECV_SIZE);
	m_iStartPos = 0;
	m_iWritePos = 0;
	m_iReadPos = 0;
}


JStreamPacket::~JStreamPacket()
{
}
