#include "JTextureMgr.h"
namespace UI
{
	JTexture* JTextureMgr::GetPtr(int iKey)
	{
		map<int, JTexture*>::iterator ITOR = m_List.find(iKey);
		if (ITOR == m_List.end()) return NULL;
		JTexture* data = (*ITOR).second;
		return data;
	}
	bool JTextureMgr::DeleteData(int iKey)
	{
		map<int, JTexture*>::iterator ITOR = m_List.find(iKey);
		if (ITOR == m_List.end()) return false;
		JTexture* DelData = (*ITOR).second;
		SAFE_RELEASE(DelData);
		delete DelData;
		return true;
	}
	int JTextureMgr::Add(ID3D11Device* device, const TCHAR* szFileName)
	{
		TCHAR* TempName = UI::JDxHelper::NameDivide(szFileName);
		map<int, JTexture*>::iterator ITOR;
		for (ITOR = m_List.begin(); ITOR != m_List.end(); ITOR++)
		{
			JTexture* data = (*ITOR).second;
			if (!_tcsicmp(TempName, data->m_szName.c_str()))
			{
				return (*ITOR).first;
			}
		}
		JTexture* Texture = new JTexture;
		if (SUCCEEDED(Texture->SRVCreate(device, szFileName)))
		{
			m_List.insert(make_pair(m_iKey++, Texture));
		}
		return m_iKey - 1;
	}
	bool JTextureMgr::Release()
	{
		map<int, JTexture*>::iterator ITOR;
		for (ITOR = m_List.begin(); ITOR != m_List.end(); ITOR++)
		{
			JTexture* ReleaseData = (*ITOR).second;
			SAFE_RELEASE(ReleaseData);
			delete ReleaseData;
		}
		m_List.clear();
		return true;
	}

	JTextureMgr::JTextureMgr()
	{
	}


	JTextureMgr::~JTextureMgr()
	{
	}
}