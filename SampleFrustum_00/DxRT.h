#pragma once
#include "JStd.h"
class DxRT
{
public:
	ID3D11RenderTargetView * m_pRTV;
	ID3D11DepthStencilView* m_pDSV;
	ID3D11RenderTargetView * m_pOldRTV;
	ID3D11DepthStencilView* m_pOldDSV;
	ID3D11ShaderResourceView* m_pRTV_SRV;
	ID3D11ShaderResourceView* m_pDSV_SRV;
	D3D11_DEPTH_STENCIL_VIEW_DESC m_DepthStencilDesc;
	D3D11_VIEWPORT m_Vp;
	D3D11_VIEWPORT m_OldVp;
	UINT m_iVp;
public:
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
public:
	HRESULT	Create(ID3D11Device* device, FLOAT fWidth = 1024, FLOAT fHeight = 1024);
	HRESULT CreateCubeMap(ID3D11Device*	device, FLOAT fWidth = 1024, FLOAT fHeight = 1024);
	void	ViewPortSet(ID3D11Device* device, FLOAT TopLeftX, FLOAT TopLeftY, FLOAT fWidth, FLOAT fHeight);
	HRESULT UpdateDepthStencilView(ID3D11Device* pDevice, UINT dwWidth, UINT dwHeight);
	void	Apply(ID3D11DeviceContext* context, ID3D11RenderTargetView* pRTV, ID3D11DepthStencilView* pDepthStencilView, bool bDepth = true, bool bStencil = true);
	bool	Begin(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget = true, bool bDepth = true, bool bStencil = true);
	bool	Clear(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget = true, bool bDepth = true, bool bStencil = true);
	bool	End(ID3D11DeviceContext* context);
public:
	DxRT();
	virtual ~DxRT();
};

