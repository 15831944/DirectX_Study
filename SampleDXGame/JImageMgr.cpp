#include "JImageMgr.h"

int JImageMgr::Add(ID3D11Device* device, const TCHAR* pszLoadName)
{
	TCHAR* Temp = NameDivide(pszLoadName);
	for (ITOR itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		JImage* data = (*itor).second;
		if (!_tcsicmp(Temp, data->m_szName.c_str()))
		{
			return (*itor).first;
		}
	}
	JImage* data = new JImage;
	if (SUCCEEDED(data->TextureLoad(device, pszLoadName)))
	{
		m_List.insert(make_pair(m_iCount++, data));
	}
	return m_iCount - 1;
}
JImage* JImageMgr::GetPtr(int iKey)
{
	ITOR itor = m_List.find(iKey);
	if (itor == m_List.end()) return NULL;
	JImage* data = (*itor).second;
	return data;
}
bool JImageMgr::Release()
{
	for (ITOR itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		JImage* data = (*itor).second;
		delete data;
	}
	m_List.clear();
	return true;
}
JImageMgr::JImageMgr()
{
}


JImageMgr::~JImageMgr()
{
}
