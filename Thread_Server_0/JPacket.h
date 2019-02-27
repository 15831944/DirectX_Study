#pragma once
#include "JProtocol.h"
/*
	_msize(); �Ҵ�� ũ�� ��� ( �����Ҵ��ũ�Ⱑ�־���� )
	���ڿ� GET,PUT �Ҷ� SIZE���������[�ִ�ũ���]
	strlen -> 0�ϋ�����ã�´�
*/
#define MAX_BUFFER_SIZE 4096
class JPacket
{
public:
	/* m_szBuffer <-> m_uPacket �����ϳ����*/
	char	m_szBuffer[MAX_BUFFER_SIZE];
	UPACKET m_uPacket;
	char*	m_pOffset;
	//char*	m_pWritePos;
	//char*	m_pReadPos;
	/* char* m_pOffset << WritePos, ReadPos -> ���ÿ� �� ���̾���. */
public:
	void PutData(const char* data, int iSize);
	void GetData(const char* data, int iSize);
public:
	////////////////////////////////////////////////������
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

