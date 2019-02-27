#include "Texture.h"

HRESULT Texture::SRVCreate(ID3D11Device* device, const TCHAR* szFileName)
{
	HRESULT hr = S_OK;
	if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(device, szFileName, NULL, NULL, &m_pSRV, NULL)))
	{
		return hr;
	}
	m_szName = NameDivide(szFileName);
	return hr;
}

bool Texture::Release()
{
	SAFE_RELEASE(m_pSRV);
	return true;
}

Texture::Texture()
{
}


Texture::~Texture()
{
}
