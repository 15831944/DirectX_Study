#pragma once
#include "JStd.h"
class JDxRT
{
public:
	ID3D11RenderTargetView*		m_pRTV;
	ID3D11DepthStencilView*		m_pDSV;
	ID3D11ShaderResourceView*	m_pRTV_SRV;
	ID3D11ShaderResourceView*	m_pDSV_SRV;
public:
	HRESULT Create(ID3D11Device* device, FLOAT Width, FLOAT Height, ID3D11Texture2D* pTexture2D);
	bool Apply(ID3D11DeviceContext* context);
	bool Begin(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget, bool bDepth, bool bStencil);
	bool End(ID3D11DeviceContext* context);
	bool Clear(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget, bool bDepth, bool bStencil);
	bool Release();
public:
	JDxRT();
	virtual ~JDxRT();
};