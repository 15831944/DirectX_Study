#pragma once
#include "JStd.h"
class JToken
{
public:
	char*						m_pData;
	LARGE_INTEGER				m_lFileSize;
	vector<string>				m_Tokenlist;
	string						m_CurrentToken;
	DWORD						m_dwMaxTokenLine;
	DWORD						m_dwTokenIndex;
public:
	bool LoadAseFile(const TCHAR* AseFileName);
	string DestroyToken(const char* szName, const char* szToken);
	string DestroyTokenName(const char* szName, const char* szToken);
	string DividePath(const char* pszFilaeName);
	INT FindToken(string szToken);
	INT GetLine(string szToken);
	const char* GetNextToken();
public:
	JToken();
	virtual ~JToken();
};

