#pragma once
#include "JBitmap.h"
class JBitmapMgr : public JSingleton<JBitmapMgr>
{
public:
	friend class JSingleton<JBitmapMgr>;
public:
	map<int, JBitmap*> m_List;
	typedef map<int, JBitmap*>::iterator ITOR;
	int m_iCounter;
public:
	int Add(const TCHAR* pszLoadName);
	JBitmap* GetPtr(int iKey);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	JBitmapMgr();
	virtual ~JBitmapMgr();
};
#define I_BitMgr JBitmapMgr::GetInstance()

