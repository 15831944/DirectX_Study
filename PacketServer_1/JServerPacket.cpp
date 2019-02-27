#include "JServerPacket.h"
int JServerPacket::PutData(const char* pData, int iSize)
{
	memcpy(m_pOffset, pData, iSize);
	m_pOffset += iSize;
	m_uPacket.ph.len = iSize;
	return iSize;
}
int JServerPacket::GetData(char* pData, int iSize)
{
	memcpy(pData, m_pOffset, iSize);
	m_pOffset += iSize;
	return iSize;
}
JServerPacket&  JServerPacket::operator << (int  iValue)
{
	PutData(reinterpret_cast<char*>(&iValue), sizeof(int));
	return *this;
}
JServerPacket&  JServerPacket::operator >> (int&  iValue)
{
	GetData(reinterpret_cast<char*>(&iValue), sizeof(int));
	return *this;
}
JServerPacket&  JServerPacket::operator << (float  fValue)
{
	PutData(reinterpret_cast<char*>(&fValue), sizeof(float));
	return *this;
}
JServerPacket&  JServerPacket::operator >> (float&  fValue)
{
	GetData(reinterpret_cast<char*>(&fValue), sizeof(float));
	return *this;
}
JServerPacket&  JServerPacket::operator << (char  cValue)
{
	PutData(reinterpret_cast<char*>(&cValue), sizeof(char));
	return *this;
}
JServerPacket&  JServerPacket::operator >> (char&  cValue)
{
	GetData(reinterpret_cast<char*>(&cValue), sizeof(char));
	return *this;
}
JServerPacket&  JServerPacket::operator << (WORD  iValue)
{
	PutData(reinterpret_cast<char*>(&iValue), sizeof(WORD));
	return *this;
}
JServerPacket&  JServerPacket::operator >> (WORD&  iValue)
{
	GetData(reinterpret_cast<char*>(&iValue), sizeof(WORD));
	return *this;
}
JServerPacket&  JServerPacket::operator << (C_STR  iValue)
{
	PutData(iValue.c_str(), iValue.size() + 1);
	return *this;
}
JServerPacket&  JServerPacket::operator >> (C_STR&  iValue)
{
	int ilen = strlen(m_pOffset) + 1;
	char buffer[256] = { 0 };
	GetData(reinterpret_cast<char*>(buffer), ilen);
	iValue = buffer;
	return *this;
}
JServerPacket&  JServerPacket::operator << (CHAR*  iValue)
{
	PutData(reinterpret_cast<char*>(iValue), strlen(iValue) + 1);
	return *this;
}
JServerPacket&  JServerPacket::operator >> (CHAR*  iValue)
{
	int ilen = strlen(m_pOffset) + 1;
	GetData(reinterpret_cast<char*>(iValue), ilen);
	return *this;
}
JServerPacket::JServerPacket()
{
	m_pOffset = m_uPacket.msg;
	m_uPacket.ph.len = 0;
}
JServerPacket::JServerPacket(DWORD dwType)
{
	m_uPacket.ph.type = dwType;
	m_uPacket.ph.len = 0;
	m_pOffset = m_uPacket.msg;
}


JServerPacket::~JServerPacket()
{
}
