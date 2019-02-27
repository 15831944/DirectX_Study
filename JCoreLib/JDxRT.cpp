#include "JDxRT.h"
HRESULT JDxRT::Create(ID3D11Device* device, FLOAT Width, FLOAT Height, ID3D11Texture2D* pTexture2D)
{
	HRESULT hr = S_OK;
	if (pTexture2D != NULL)
	{
		if (FAILED(hr = device->CreateRenderTargetView(pTexture2D, NULL, &m_pRTV)))
		{
			return hr;
		}
	}

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = Width;
	desc.Height = Height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	ID3D11Texture2D* Tex2D = NULL;
	if (hr = device->CreateTexture2D(&desc, NULL, &Tex2D))
	{
		return hr;
	}
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvd.Format = desc.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0;

	if (hr = device->CreateDepthStencilView(Tex2D, &dsvd, &m_pDSV))
	{
		return hr;
	}

	return hr;
}
bool JDxRT::Apply(ID3D11DeviceContext* context)
{
	context->OMSetRenderTargets(1, &m_pRTV, m_pDSV);
	return true;
}
bool JDxRT::Begin(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget, bool bDepth, bool bStencil)
{
	Apply(context);
	Clear(context, vColor, bTarget, bDepth, bStencil);
	return true;
}
bool JDxRT::End(ID3D11DeviceContext* context)
{
	return true;
}
bool JDxRT::Clear(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget, bool bDepth, bool bStencil)
{
	if (bTarget)
	{
		context->ClearRenderTargetView(m_pRTV, vColor);
	}
	if (bDepth)
	{
		if(m_pDSV != NULL)
		context->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_DEPTH,1.0f, 0.0f);
	}
	if (bStencil)
	{
		if (m_pDSV != NULL)
		context->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
	}

	return true;
}
bool JDxRT::Release()
{
	SAFE_RELEASE(m_pRTV);
	SAFE_RELEASE(m_pDSV);
	SAFE_RELEASE(m_pRTV_SRV);
	SAFE_RELEASE(m_pDSV_SRV);
	return true;
}
JDxRT::JDxRT()
{
	m_pRTV		= NULL;
	m_pDSV		= NULL;
}
JDxRT::~JDxRT()
{

}