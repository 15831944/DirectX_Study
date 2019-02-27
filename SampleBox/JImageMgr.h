#pragma once
#include "JImage.h"
class JImageMgr : public JSingleton<JImageMgr>
{
public:
	friend class JSingleton<JImageMgr>;
public:
	map<int, JImage*> m_List;
	typedef map<int, JImage*>::iterator ITOR;
	int m_iCount;
public:
	int Add(ID3D11Device* device, const TCHAR* pszLoadName);
	JImage* GetPtr(int iKey);
	virtual bool Release();
public:
	JImageMgr();
	virtual ~JImageMgr();
};
#define I_ImgMgr JImageMgr::GetInstance()