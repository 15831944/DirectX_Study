#pragma once
#include "JStd.h"
namespace DX
{
	class JDxRT
	{
	public:
		ComPtr<ID3D11RenderTargetView>		g_pRTV;
		ComPtr<ID3D11DepthStencilView>		g_pDSV;
	public:
		HRESULT Create(ID3D11Device* device, FLOAT Width, FLOAT Height, ID3D11Texture2D* pTexture2D);
		HRESULT Apply(ID3D11DeviceContext* context);
		HRESULT Begin(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget, bool bDepth, bool bStencil);
		HRESULT End(ID3D11DeviceContext* context);
		HRESULT Clear(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget, bool bDepth, bool bStencil);
	public:
		JDxRT();
		virtual ~JDxRT();
	};
}