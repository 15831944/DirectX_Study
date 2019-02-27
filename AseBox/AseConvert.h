#pragma once
#include "JStd.h"
class AseConvert
{
public:
	char* m_pData;
	LARGE_INTEGER m_iFileSize;
	vector<string> m_TokenList;
public:
	bool LoadAseFile(const TCHAR* szFileName);
	bool CuttingFile();
public:
	AseConvert();
	virtual ~AseConvert();
};

