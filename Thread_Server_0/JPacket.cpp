#include "JPacket.h"

void JPacket::PutData(const char* data, int iSize)
{
	memcpy(m_pOffset, data, iSize);
	m_pOffset += iSize;
}
void JPacket::GetData(const char* data, int iSize)
{
	memcpy(const_cast<char*>(data), m_pOffset, iSize);
	m_pOffset += iSize;
}
JPacket & JPacket::operator << (int data)
{
	PutData((char*)&data, sizeof(int));
	return *this;
}
JPacket & JPacket::operator << (short data)
{
	PutData((char*)&data, sizeof(short));
	return *this;
}
JPacket & JPacket::operator << (long data)
{
	PutData((char*)&data, sizeof(long));
	return *this;
}
JPacket & JPacket::operator << (char* data)
{
	PutData((char*)&data, strlen(data) + 1);
	return *this;
}
JPacket & JPacket::operator << (string data)
{
	PutData((char*)&data, sizeof(int));
	return *this;
}
JPacket & JPacket::operator << (float data)
{
	PutData((char*)&data, sizeof(float));
	return *this;
}
JPacket & JPacket::operator << (double data)
{
	PutData((char*)&data, sizeof(double));
	return *this;
}

JPacket & JPacket::operator >> (int data)
{
	GetData((char*)&data, sizeof(int));
	return *this;
}
JPacket & JPacket::operator >> (short data)
{
	GetData((char*)&data, sizeof(short));
	return *this;
}
JPacket & JPacket::operator >> (long data)
{
	GetData((char*)&data, sizeof(long));
	return *this;
}
JPacket & JPacket::operator >> (char* data)
{
	int iLen = strlen(m_pOffset) + 1;
	GetData((char*)&data, iLen);
	return *this;
}
JPacket & JPacket::operator >> (string data)
{
	GetData((char*)&data, sizeof(int));
	return *this;
}
JPacket & JPacket::operator >> (float data)
{
	GetData((char*)&data, sizeof(float));
	return *this;
}
JPacket & JPacket::operator >> (double data)
{
	GetData((char*)&data, sizeof(double));
	return *this;
}

JPacket::JPacket()
{
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_pOffset = m_szBuffer;
}
JPacket::JPacket(int iType)
{
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_uPacket.ph.type = iType;
	m_pOffset = m_szBuffer;
}


JPacket::~JPacket()
{
}
