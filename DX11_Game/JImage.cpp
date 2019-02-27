#include "JImage.h"

HRESULT JImage::TextureLoad(ID3D11Device* device, const TCHAR* szLoadFileName)
{
	HRESULT hr;
	//ID3D11ShaderResourceView* Temp;
	if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(device, szLoadFileName, NULL, NULL, &m_pTexSRV, NULL)))
	{
		return hr;
	}
	m_szName = NameDivide(szLoadFileName);
	return hr;
}
bool JImage::Init()
{
	return true;
}
bool JImage::Frame(ID3D11DeviceContext* context)
{
	return true;
}
bool JImage::Render(ID3D11DeviceContext* context)
{
	return true;
}
bool JImage::Release()
{
	return true;
}
JImage::JImage()
{
}


JImage::~JImage()
{
}