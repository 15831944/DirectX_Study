#pragma once
#include "JProtocol.h"
/*
	_msize(); 할당된 크기 계산 ( 동적할당된크기가있어야함 )
	문자열 GET,PUT 할때 SIZE맞춰줘야함[최대크기로]
	strlen -> 0일떄까지찾는다
*/
#define MAX_BUFFER_SIZE 4096
class JPacket
{
public:
	/* m_szBuffer <-> m_uPacket 둘중하나사용*/
	char	m_szBuffer[MAX_BUFFER_SIZE];
	UPACKET m_uPacket;
	char*	m_pOffset;
	//char*	m_pWritePos;
	//char*	m_pReadPos;
	/* char* m_pOffset << WritePos, ReadPos -> 동시에 할 일이없다. */
public:
	void PutData(const char* data, int iSize);
	void GetData(const char* data, int iSize);
public:
	////////////////////////////////////////////////재정의
	JPacket & operator << (int data);
	JPacket & operator << (short data);
	JPacket & operator << (long data);
	JPacket & operator << (char* data);
	JPacket & operator << (string data);
	JPacket & operator << (float data);
	JPacket & operator << (double data);
	JPacket & operator >> (int data);
	JPacket & operator >> (short data);
	JPacket & operator >> (long data);
	JPacket & operator >> (char* data);
	JPacket & operator >> (string data);
	JPacket & operator >> (float data);
	JPacket & operator >> (double data);
public:
	JPacket();
	JPacket(int iType);
	virtual ~JPacket();
};

