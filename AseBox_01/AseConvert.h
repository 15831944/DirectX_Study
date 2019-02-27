#pragma once
#include "JStd.h"

class AseConvert
{
public:
	char* m_pData;
	LARGE_INTEGER m_lFileSize;
	vector<string> m_Tokenlist;
public:
	bool LoadAseFile(const TCHAR* AseFileName);
	bool CuttingFile();
public:
	AseConvert();
	virtual ~AseConvert();
};