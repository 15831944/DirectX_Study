#pragma once
#include "JStd.h"
class JImage
{
public:
	ID3D11ShaderResourceView * m_pTexSRV;
	wstring m_szName;
public:
	HRESULT TextureLoad(ID3D11Device* device, const TCHAR* szLoadFileName);
public:
	virtual bool Init();
	virtual bool Frame(ID3D11DeviceContext* context);
	virtual bool Render(ID3D11DeviceContext* context);
	virtual bool Release();
public:
	JImage();
	virtual ~JImage();
};