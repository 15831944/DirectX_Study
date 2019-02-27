#include "AseConvert.h"

bool AseConvert::LoadAseFile(const TCHAR* AseFileName)
{
	HANDLE hRead = CreateFile(AseFileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hRead == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hRead);
		return false;
	}
	
	GetFileSizeEx(hRead, &m_lFileSize);
	m_pData = new char[m_lFileSize.QuadPart];

	if (m_pData == NULL)
	{
		SAFE_DELETE(m_pData);
		CloseHandle(hRead);
		return false;
	}

	if (FALSE ==  ReadFile(hRead, m_pData, m_lFileSize.QuadPart, 0, 0))
	{
		SAFE_DELETE(m_pData);
		CloseHandle(hRead);
		return false;
	}
	CloseHandle(hRead);

	if (!CuttingFile()) return false;
	return true;
}
bool AseConvert::CuttingFile()
{
	if (m_pData == NULL) return false;
	string pData = m_pData;
	string strToken = "*";
	size_t start = pData.find_first_not_of(strToken);
	size_t end = pData.find_first_of(strToken, start);
	for (; start < pData.size();)
	{
		start = pData.find_first_not_of(strToken);
		end = pData.find_first_of(strToken, start);

		string Token = pData.substr(start, end - start);
		m_Tokenlist.push_back(Token);
	}
	return true;
}
AseConvert::AseConvert()
{

}
AseConvert::~AseConvert()
{

}