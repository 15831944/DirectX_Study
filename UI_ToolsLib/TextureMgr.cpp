#include "TextureMgr.h"

Texture* TextureMgr::GetPtr(int iKey)
{
	map<int, Texture*>::iterator ITOR = m_List.find(iKey);
	if (ITOR == m_List.end()) return NULL;
	Texture* data = (*ITOR).second;
	return data;
}
bool TextureMgr::DeleteData(int iKey)
{
	map<int, Texture*>::iterator ITOR = m_List.find(iKey);
	if (ITOR == m_List.end()) return false;
	Texture* DelData = (*ITOR).second;
	SAFE_RELEASE(DelData);
	delete DelData;
	return true;
}
int TextureMgr::Add(ID3D11Device* device, const TCHAR* szFileName)
{
	TCHAR* TempName = NameDivide(szFileName);

	for (ITOR = m_List.begin(); ITOR != m_List.end(); ITOR++)
	{
		Texture* data = (*ITOR).second;
		if (!_tcsicmp(TempName, data->m_szName.c_str()))
		{
			return (*ITOR).first;
		}
	}
	Texture* Tex = new Texture;
	if (SUCCEEDED(Tex->SRVCreate(device, szFileName)))
	{
		m_List.insert(make_pair(m_iKey++, Tex));
	}
	return m_iKey - 1;
}
bool TextureMgr::Release()
{
	map<int, Texture*>::iterator ITOR;
	for (ITOR = m_List.begin(); ITOR != m_List.end(); ITOR++)
	{
		Texture* ReleaseData = (*ITOR).second;
		SAFE_RELEASE(ReleaseData);
		delete ReleaseData;
	}
	m_List.clear();
	return true;
}

TextureMgr::TextureMgr()
{
}


TextureMgr::~TextureMgr()
{
}
