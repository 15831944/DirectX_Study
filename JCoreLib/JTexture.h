#pragma once
#include "JStd.h"
class JTexture
{
public:
	ID3D11ShaderResourceView * m_pSRV;
	wstring m_szName;
public:
	HRESULT SRVCreate(ID3D11Device* device, const TCHAR* szFileName);
	bool Release();
public:
	JTexture();
	virtual ~JTexture();
};