#include "JDxRT.h"
namespace DX
{
	HRESULT JDxRT::Create(ID3D11Device* device, FLOAT Width, FLOAT Height, ID3D11Texture2D* pTexture2D)
	{
		HRESULT hr = S_OK;
		if (pTexture2D != nullptr)
		{
			if (FAILED(hr = device->CreateRenderTargetView(pTexture2D, NULL, g_pRTV.GetAddressOf())))
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

		ComPtr<ID3D11Texture2D> Tex2D = nullptr;
		if (hr = device->CreateTexture2D(&desc, NULL, Tex2D.GetAddressOf()))
		{
			return hr;
		}
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		dsvd.Format = desc.Format;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Texture2D.MipSlice = 0;
		if (hr = device->CreateDepthStencilView(Tex2D.Get(), &dsvd, g_pDSV.GetAddressOf()))
		{
			return hr;
		}
		return hr;
	}
	HRESULT JDxRT::Apply(ID3D11DeviceContext* context)
	{
		HRESULT hr = S_OK;
		context->OMSetRenderTargets(1, g_pRTV.GetAddressOf(), g_pDSV.Get());
		return hr;
	}
	HRESULT JDxRT::Begin(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget, bool bDepth, bool bStencil)
	{
		Apply(context);
		Clear(context, vColor, bTarget, bDepth, bStencil);
	}
	HRESULT JDxRT::End(ID3D11DeviceContext* context)
	{
		HRESULT hr = S_OK;
		return hr;
	}
	HRESULT JDxRT::Clear(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget, bool bDepth, bool bStencil)
	{
		HRESULT hr = S_OK;
		if (bTarget)
		{
			context->ClearRenderTargetView(g_pRTV.Get(), vColor);
		}
		if (bDepth)
		{
			if(g_pDSV != nullptr)
			context->ClearDepthStencilView(g_pDSV.Get(), D3D11_CLEAR_DEPTH,1.0f, 0.0f);
		}
		if (bStencil)
		{
			if (g_pDSV != nullptr)
			context->ClearDepthStencilView(g_pDSV.Get(), D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
		}

		return hr;
	}
	JDxRT::JDxRT()
	{
		g_pRTV		= nullptr;
		g_pDSV		= nullptr;
	}
	JDxRT::~JDxRT()
	{

	}
}