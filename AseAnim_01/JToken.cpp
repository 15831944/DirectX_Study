#include "JToken.h"

INT JToken::FindToken(string szToken)
{
	int EndLine = m_dwMaxTokenLine;
	INT retIndex = -1;
	while (EndLine > m_dwTokenIndex)
	{
		GetNextToken();
		if (NULL != strstr(m_CurrentToken.c_str(), szToken.c_str()))
		{
			retIndex = m_dwTokenIndex - 1;
			break;
		}
	}
	if (EndLine < m_dwTokenIndex) return -1;
	return retIndex;
}
INT JToken::GetLine(string szToken)
{
	char szTemp[256] = { 0, };
	INT retIndex = -1;
	strcpy(szTemp, szToken.c_str());
	if (m_dwTokenIndex + 1 < m_Tokenlist.size())
	{
		m_CurrentToken = m_Tokenlist[m_dwTokenIndex++];
	}
	if (NULL != strstr(m_CurrentToken.c_str(), szToken.c_str()))
	{
		retIndex = m_dwTokenIndex - 1;
		return retIndex;
	}
	--m_dwTokenIndex;
	return retIndex;
}
bool JToken::LoadAseFile(const TCHAR* AseFileName)
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

	if (FALSE == ReadFile(hRead, m_pData, m_lFileSize.QuadPart, 0, 0))
	{
		SAFE_DELETE(m_pData);
		CloseHandle(hRead);
		return false;
	}
	CloseHandle(hRead);

	if (m_pData == NULL) return false;
	string pData = m_pData;
	string strToken = "*";
	size_t start = pData.find_first_not_of(strToken);
	size_t end = pData.find_first_of(strToken, start);
	for (; start < pData.size(); start = pData.find_first_not_of(strToken, end))
	{
		end = pData.find_first_of(strToken, start);

		string Token = pData.substr(start, end - start);
		m_Tokenlist.push_back(Token);
	}
	m_dwMaxTokenLine = m_Tokenlist.size();
	return true;
}
const char* JToken::GetNextToken()
{
	m_CurrentToken = m_Tokenlist[m_dwTokenIndex++];
	return m_CurrentToken.c_str();
}
string JToken::DestroyToken(const char* szName, const char* szToken)
{
	string pData = szName;
	string strToken = szToken;
	size_t start = pData.find_first_not_of(strToken);
	size_t end = pData.find_first_of(strToken, start);
	string retData = pData.substr(start, end - 1);
	return retData;
}
string JToken::DestroyTokenName(const char* szName, const char* szToken)
{
	string pData = szName;
	string strToken = szToken;
	size_t start = pData.find_first_of(strToken);
	size_t end = pData.find_last_of(strToken);
	string retData = pData.substr(start, end - 1);
	return DestroyToken(retData.c_str(), szToken);
}
string JToken::DividePath(const char* pszFileName)
{
	char RetData[MAX_PATH] = { 0, };
	char Drive[MAX_PATH] = { 0, };
	char Dir[MAX_PATH] = { 0, };
	char FileName[MAX_PATH] = { 0, };
	char Ext[MAX_PATH] = { 0, };
	string Ret;
	if (pszFileName != NULL)
	{
		_splitpath_s(pszFileName, Drive, Dir, FileName, Ext);
		sprintf_s(RetData, "%s%s", FileName, Ext);
		Ret = RetData;
		return Ret;
	}
	return NULL;
}

JToken::JToken()
{
}


JToken::~JToken()
{
}
