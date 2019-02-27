#include "JBitmapMgr.h"

int JBitmapMgr::Add(const TCHAR* pszLoadName)
{
	for (ITOR itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		JBitmap* data = (*itor).second;
		if (!_tcsicmp(pszLoadName, data->m_szName.c_str()))
		{
			return (*itor).first;
		}
	}
	JBitmap* data = new JBitmap;
	data->Init();
	if (data->Load(pszLoadName))
	{
		m_List.insert(make_pair(m_iCounter++, data));
	}
	return m_iCounter - 1;
}
JBitmap* JBitmapMgr::GetPtr(int iKey)
{
	ITOR itor = m_List.find(iKey);
	if (itor == m_List.end()) return NULL;
	JBitmap* data = (*itor).second;
	return data;
}

bool JBitmapMgr::Init()
{
	return true;
}
bool JBitmapMgr::Frame()
{
	return true;
}
bool JBitmapMgr::Render()
{
	return true;
}
bool JBitmapMgr::Release()
{
	for (ITOR itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		JBitmap* data = (*itor).second;
		delete data;
	}
	m_List.clear();
	return true;
}
JBitmapMgr::JBitmapMgr()
{
	m_iCounter = 0;
}
JBitmapMgr::~JBitmapMgr()
{
}
