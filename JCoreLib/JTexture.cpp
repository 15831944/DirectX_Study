#include "JTexture.h"

HRESULT JTexture::SRVCreate(ID3D11Device* device, const TCHAR* szFileName)
{
	HRESULT hr = S_OK;
	if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(device, szFileName, NULL, NULL, &m_pSRV, NULL)))
	{
		return hr;
	}
	m_szName = NameDivide(szFileName);
	return hr;
}

bool JTexture::Release()
{
	SAFE_RELEASE(m_pSRV);
	return true;
}

JTexture::JTexture()
{
}


JTexture::~JTexture()
{
}
