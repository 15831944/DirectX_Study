#include "Minimap.h"
bool Minimap::Create(ID3D11Device* device, ID3D11DeviceContext* context, UINT iSize)
{
	HRESULT hr;
	m_Vp.Width = iSize;
	m_Vp.Height = iSize;
	m_Vp.MinDepth = 0;
	m_Vp.MaxDepth = 1;
	m_Vp.TopLeftX = 0;
	m_Vp.TopLeftY = 0;

	D3D11_TEXTURE2D_DESC rtvdesc;
	ZeroMemory(&rtvdesc, sizeof(D3D11_TEXTURE2D_DESC));
	rtvdesc.Width = (UINT)iSize;
	rtvdesc.Height = (UINT)iSize;
	rtvdesc.MipLevels = 1;
	rtvdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvdesc.SampleDesc.Count = 1;
	rtvdesc.SampleDesc.Quality = 0;
	rtvdesc.Usage = D3D11_USAGE_DEFAULT;
	rtvdesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	rtvdesc.CPUAccessFlags = 0;
	rtvdesc.MiscFlags = 0;
	rtvdesc.ArraySize = 1;

	ID3D11Texture2D* RTVTex2D = NULL;
	if (hr = device->CreateTexture2D(&rtvdesc, NULL, &RTVTex2D))
	{
		return hr;
	}
	D3D11_DEPTH_STENCIL_VIEW_DESC srvdsvd;
	ZeroMemory(&srvdsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	srvdsvd.Format = rtvdesc.Format;
	srvdsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	srvdsvd.Texture2D.MipSlice = 0;
	if (FAILED(hr = device->CreateRenderTargetView(RTVTex2D, NULL, &m_pRTV)))
	{
		return hr;
	}

	ID3D11Texture2D* DSVTex2D = NULL;
	D3D11_TEXTURE2D_DESC dsvdesc;
	ZeroMemory(&dsvdesc, sizeof(D3D11_TEXTURE2D_DESC));
	dsvdesc.Width = (UINT)iSize;
	dsvdesc.Height = (UINT)iSize;
	dsvdesc.MipLevels = 1;
	dsvdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dsvdesc.SampleDesc.Count = 1;
	dsvdesc.SampleDesc.Quality = 0;
	dsvdesc.Usage = D3D11_USAGE_DEFAULT;
	dsvdesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	dsvdesc.CPUAccessFlags = 0;
	dsvdesc.MiscFlags = 0;
	dsvdesc.ArraySize = 1;
	if (hr = device->CreateTexture2D(&dsvdesc, NULL, &DSVTex2D))
	{
		return hr;
	}
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvdsvd;
	ZeroMemory(&srvdsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	srvdsvd.Format = rtvdesc.Format;
	srvdsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	srvdsvd.Texture2D.MipSlice = 0;

	if (hr = device->CreateDepthStencilView(DSVTex2D, &dsvdsvd, &m_pDSV))
	{
		return hr;
	}
	return true;
}

bool Minimap::Begin(ID3D11DeviceContext* context)
{
	if(context == NULL) return false;
	UINT cRT = 1;
	context->RSGetViewports(&cRT, &m_OldVp);
	context->OMGetRenderTargets(1, &m_pOldRTV, &m_pOldDSV);

	context->RSSetViewports(1, &m_Vp);
	context->OMSetRenderTargets(1, &m_pRTV, m_pDSV);

	float vColor[4] = { 0.0f,0.125f, 0.3f,1.0f };
	context->ClearRenderTargetView(m_pRTV, vColor);
	//context->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_DEPTH, 1.0f, 1);
	return true;
}
bool Minimap::End(ID3D11DeviceContext* context)
{
	ID3D11ShaderResourceView* ppSRVNULL[1] = { NULL, };
	context->PSSetShaderResources(0, 1, ppSRVNULL);
	context->RSSetState(NULL);

	ID3D11RenderTargetView* pNULLRTV = NULL;
	context->OMSetRenderTargets(1, &pNULLRTV, NULL);
	context->RSSetViewports(1, &m_OldVp);
	context->OMSetRenderTargets(1, &m_pOldRTV, m_pOldDSV);

	SAFE_RELEASE(m_pOldRTV);
	SAFE_RELEASE(m_pOldDSV);

	return true;
}
bool Minimap::RenderToTexture(ID3D11Device* device,
	ID3D11DeviceContext* context,
	ID3D11RenderTargetView* pRTV,
	ID3D11ShaderResourceView* pSRV,
	bool bClear,
	ID3D11InputLayout* pIL,
	ID3D11Buffer* pVB,
	UINT iStride,
	UINT iRTX,
	UINT iRTY)
{
	D3D11_VIEWPORT OldVp;
	UINT cRT = 1;
	context->RSGetViewports(&cRT, &OldVp);

	if (pRTV)
	{
		D3D11_VIEWPORT pVp;
		pVp.Width = iRTX;
		pVp.Height = iRTY;


	}
	return true;
}
Minimap::Minimap()
{
}


Minimap::~Minimap()
{
}
