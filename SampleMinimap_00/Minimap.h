#pragma once
#include "JPlaneShape.h"
#include "DxRT.h"
class Minimap
{
public:
	ID3D11RenderTargetView*		m_pRTV;
	ID3D11DepthStencilView*		m_pDSV;
	ID3D11RenderTargetView*		m_pOldRTV;
	ID3D11DepthStencilView*		m_pOldDSV;
	D3D11_VIEWPORT				m_Vp;
	D3D11_VIEWPORT				m_OldVp;

public:
	bool Begin(ID3D11DeviceContext* context);
	bool Create(ID3D11Device* device, ID3D11DeviceContext* context, UINT iSize);
	bool End(ID3D11DeviceContext* context);
	bool RenderToTexture(ID3D11Device* device,
		ID3D11DeviceContext* context,
		ID3D11RenderTargetView* pRTV,
		ID3D11ShaderResourceView* pSRV,
		bool bClear,
		ID3D11InputLayout* pIL,
		ID3D11Buffer* pVB,
		UINT iStride,
		UINT iRTX,
		UINT iRTY);
public:
	Minimap();
	virtual ~Minimap();
};

