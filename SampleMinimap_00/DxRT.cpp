#include "DxRT.h"

HRESULT	DxRT2::Create(ID3D11Device* device, FLOAT Width, FLOAT Height)
{
	HRESULT hr = S_OK;
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	ViewPortSet(device, 0, 0, Width, Height);

	desc.Width = (UINT)Width;
	desc.Height = (UINT)Height;
	desc.MipLevels = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.ArraySize = 1;

	ID3D11Texture2D* pTexture = NULL;

	if (FAILED(hr = device->CreateTexture2D(&desc, NULL, &pTexture)))
	{
		return hr;
	}
	if (FAILED(hr = device->CreateShaderResourceView(pTexture, NULL, &m_pRTV_SRV)))
	{
		return hr;
	}
	if (FAILED(hr = device->CreateRenderTargetView(pTexture, NULL, &m_pRTV)))
	{
		return hr;
	}
	if (FAILED(hr = UpdateDepthStencilView(device, (UINT)Width, (UINT)Height)))
	{
		return hr;
	}
	return hr;
}
HRESULT DxRT2::CreateCubeMap(ID3D11Device*	device, FLOAT fWidth, FLOAT fHeight)
{
	return S_OK;
}
void DxRT2::ViewPortSet(ID3D11Device* device, FLOAT TopLeftX, FLOAT TopLeftY, FLOAT Width, FLOAT Height)
{
	m_Vp.TopLeftX = TopLeftX;
	m_Vp.TopLeftY = TopLeftY;
	m_Vp.Width = Width;
	m_Vp.Height = Height;
	m_Vp.MinDepth = 0;
	m_Vp.MaxDepth = 1;
}
HRESULT DxRT2::UpdateDepthStencilView(ID3D11Device* pDevice, UINT iWidth, UINT iHeight)
{
	HRESULT hr;
	if (m_pDSV != NULL)
	{
		SAFE_RELEASE(m_pDSV);
	}

	m_Vp.Width = iWidth;
	m_Vp.Height = iHeight;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_TEXTURE2D_DESC DescDepth;
	DescDepth.Width = iWidth;
	DescDepth.Height = iHeight;
	DescDepth.MipLevels = 1;
	DescDepth.ArraySize = 1;
	DescDepth.Format = DXGI_FORMAT_R32_TYPELESS;
	DescDepth.SampleDesc.Count = 1;
	DescDepth.SampleDesc.Quality = 0;
	DescDepth.Usage = D3D11_USAGE_DEFAULT;

	if (DescDepth.Format == DXGI_FORMAT_D24_UNORM_S8_UINT)
		DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	else 
		DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	DescDepth.CPUAccessFlags = 0;
	DescDepth.MiscFlags = 0;
	if (FAILED(hr = pDevice->CreateTexture2D(&DescDepth, NULL, &pTexture)))
	{
		return hr;
	}

	///// ½¦ÀÌ´õ ¸®¼Ò½º »ý¼º : ±íÀÌ ¸Ê ½¦µµ¿ì¿¡¼­ »ç¿ëÇÑ´Ù. ///
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

	switch (DescDepth.Format)
	{
	case DXGI_FORMAT_R32_TYPELESS:
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		srvDesc.Format = DXGI_FORMAT_R32_FLOAT;
		break;
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		break;
	}
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;
	//pDevice->CreateDepthStencilView(m_pTexture, &dsvDesc, &m_pDSV);
	//D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	//ZeroMemory(&dsvd, sizeof(dsvd));
	//dsvd.Format = DescDepth.Format;
	//dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//dsvd.Texture2D.MipSlice = 0;

	if (FAILED(hr = pDevice->CreateDepthStencilView(pTexture, &dsvDesc, &m_pDSV)))
	{
		return hr;
	}

	// ±íÀÌ¸Ê ÀÏ °æ¿ì¸¸ »ý¼ºÇÑ´Ù.
	if (DescDepth.Format == DXGI_FORMAT_R32_TYPELESS)
	{
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;
		pDevice->CreateShaderResourceView(pTexture, &srvDesc, &m_pDSV_SRV);
	}
	m_pDSV->GetDesc(&m_DepthStencilDesc);
	return hr;
}
void	DxRT2::Apply(ID3D11DeviceContext* context, ID3D11RenderTargetView* pRTV, ID3D11DepthStencilView* pDSV, bool bDepth, bool bStencil)
{
	ID3D11RenderTargetView* pNullRTV = NULL;
	context->OMSetRenderTargets(1, &pNullRTV, NULL);

	if (pRTV != NULL)
	{
		if (pDSV != NULL)
			context->OMSetRenderTargets(1, &pRTV, pDSV);
		else
			context->OMSetRenderTargets(1, &pRTV, m_pDSV);
	}
	else
	{
		if (pDSV != NULL)
			context->OMSetRenderTargets(1, &m_pRTV, pDSV);
		else
			context->OMSetRenderTargets(1, &m_pRTV, m_pDSV);
	}
	if (bDepth)
	{
		if (pDSV != NULL)
			context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0, 0);
		else
			context->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_DEPTH, 1.0, 0);

	}
	if (bStencil)
	{
		if (pDSV != NULL)
			context->ClearDepthStencilView(pDSV, D3D11_CLEAR_STENCIL, 1.0, 0);
		else
			context->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_STENCIL, 1.0, 0);
	}
	context->RSSetViewports(1, &m_Vp);

}
bool	DxRT2::Begin(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget, bool bDepth, bool bStencil)
{
	m_iVp = 1;
	context->RSGetViewports(&m_iVp, &m_OldVp);
	context->OMGetRenderTargets(1, &m_pOldRTV, &m_pOldDSV);

	ID3D11RenderTargetView* pNullRTV = NULL;
	context->OMSetRenderTargets(1, &pNullRTV, NULL);
	context->OMSetRenderTargets(1, &m_pRTV, m_pDSV);

	Clear(context, vColor, bTarget, bDepth, bStencil);
	context->RSSetViewports(1, &m_Vp);
	return true;
}
bool	DxRT2::Clear(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget, bool bDepth, bool bStencil)
{
	if (bTarget)
	{
		context->ClearRenderTargetView(m_pRTV, vColor);
	}
	if (bDepth)
	{
		context->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_DEPTH, 1.0, 0);
	}
	if (bStencil)
	{
		context->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_STENCIL, 1.0, 0);
	}
	context->RSSetViewports(1, &m_Vp);
	return true;
}
bool	DxRT2::End(ID3D11DeviceContext* context)
{
	context->RSSetViewports(m_iVp, &m_OldVp);
	context->OMSetRenderTargets(1, &m_pOldRTV, m_pOldDSV);
	SAFE_RELEASE(m_pOldRTV);
	SAFE_RELEASE(m_pOldDSV);
	return true;
}

DxRT2::DxRT2()
{
}


DxRT2::~DxRT2()
{
}
