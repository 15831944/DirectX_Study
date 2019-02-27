#pragma once
#include "JTexture.h"
class JTextureMgr : public JSingleton<JTextureMgr>
{
private:
	friend class JSingleton<JTextureMgr>;
public:
	map<int, JTexture*> m_List;
	map<int, JTexture*>::iterator ITOR;
	int m_iKey;
public:
	JTexture * GetPtr(int iKey);
	int  Add(ID3D11Device* device, const TCHAR* szFileName);
	bool DeleteData(int iKey);
	bool Release();
public:
	JTextureMgr();
	~JTextureMgr();
};
#define I_TexMgr JTextureMgr::GetInstance()