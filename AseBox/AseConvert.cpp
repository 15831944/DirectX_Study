#include "AseConvert.h"

bool AseConvert::LoadAseFile(const TCHAR* szFileName)
{
	HANDLE hRead = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	
	if (hRead == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hRead);
		return false;
	}
	GetFileSizeEx(hRead, &m_iFileSize);
	m_pData = new char[m_iFileSize.QuadPart];

	if (m_pData == NULL)
	{
		delete[] m_pData;
		m_pData = NULL;
		CloseHandle(hRead);
		return false;
	}

	if (ReadFile(hRead, m_pData, m_iFileSize.QuadPart, 0, 0) == FALSE)
	{
		delete[] m_pData;
		m_pData = NULL;
		CloseHandle(hRead);
		return false;
	}
	
	CloseHandle(hRead);
	return true;
}

bool AseConvert::CuttingFile()
{
	string pData = m_pData;
	string cStar = "*";
	size_t start = pData.find_first_not_of(cStar);
	size_t end = pData.find_first_of(cStar, start);
	for (start;	start < pData.size();
		start = pData.find_first_not_of(cStar,end))
	{
		end = pData.find_first_of(cStar, start);
		string temp = pData.substr(start, end - start);
		m_TokenList.push_back(temp);
	}

	return true;
}

AseConvert::AseConvert()
{
}


AseConvert::~AseConvert()
{
}