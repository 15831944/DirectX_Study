#pragma once
#include "UI_Std.h"
class Texture
{
public:
	ID3D11ShaderResourceView * m_pSRV;
	wstring m_szName;
public:
	HRESULT SRVCreate(ID3D11Device* device, const TCHAR* szFileName);
	bool Release();
public:
	Texture();
	virtual ~Texture();
};