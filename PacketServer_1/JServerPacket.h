#pragma once
#include <windows.h>
#include <tchar.h>
#include <vector>
#include <map>
#include <list>
#include <string>
#include "JProtocol.h"
using namespace std;
typedef basic_string<TCHAR> T_STR;
typedef basic_string<wchar_t> W_STG;
typedef basic_string<char>  C_STR;

#define MAX_BUFFER_SIZE 4096

class JServerPacket
{
public:
	char*   m_pOffset;
	UPACKET	 m_uPacket;
public:
	int			PutData(const char* pData, int iSize);
	int			GetData(char* pData, int iSize);
	JServerPacket&   operator << (int  iValue);
	JServerPacket&   operator << (float fValue);
	JServerPacket&   operator << (char cValue);
	JServerPacket&   operator << (WORD Value);
	JServerPacket&   operator << (C_STR Value);
	JServerPacket&   operator << (CHAR* Value);

	JServerPacket&   operator >> (int& iValue);
	JServerPacket&   operator >> (float& fValue);
	JServerPacket&   operator >> (char& cValue);
	JServerPacket&   operator >> (WORD& Value);
	JServerPacket&   operator >> (C_STR& Value);
	JServerPacket&   operator >> (CHAR* Value);
public:
	JServerPacket(DWORD dwType);
	JServerPacket();
	virtual ~JServerPacket();
};

