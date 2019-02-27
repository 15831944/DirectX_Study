#pragma once
#include "Texture.h"
class TextureMgr : public JSingleton<TextureMgr>
{
private:
	friend class JSingleton<TextureMgr>;
public:
	map<int, Texture*> m_List;
	map<int, Texture*>::iterator ITOR;
	int m_iKey;
public:
	Texture * GetPtr(int iKey);
	int  Add(ID3D11Device* device, const TCHAR* szFileName);
	bool DeleteData(int iKey);
	bool Release();
public:
	TextureMgr();
	~TextureMgr();
};
#define I_Texture TextureMgr::GetInstance()