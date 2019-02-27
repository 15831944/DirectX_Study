#pragma once
#include "JStd.h"
class JDevice
{
private:
	ID3D11BlendState*       m_pAlphaBlend;
	ID3D11Device*			m_pd3dDevice;
	IDXGISwapChain*			m_pSwapChain;
	D3D_FEATURE_LEVEL		m_FeatureLevel;
	IDXGIFactory*			m_pFactory;
	ID3D11DeviceContext*	m_pd3dContext;
	ID3D11Texture2D*		m_pTexture2D;
	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;
	ID3D11RenderTargetView* m_pRTV;
	D3D11_VIEWPORT			m_ViewPort;
public:
	float m_BKColor[4];
public:
	IDXGISurface1*			m_pSurface;
public:
	ID3D11Device*			GetDevice();
	ID3D11DeviceContext*	GetContext();
public:
	HRESULT					CreateFactory();
	HRESULT					CreateDevice();
	HRESULT					CreateSwapChain();
	HRESULT					CreateSurface();
	HRESULT					SetRenderTargetView();
	HRESULT					SetViewPort();
	HRESULT					InitDevice();
	HRESULT					ReziseDevice(UINT width, UINT height);
	HRESULT					CreateBlendState();
	void					Clear();
public:
	bool					PreRender();
	bool					Render();
	bool					PostRender();
	bool					Release();
public:
	JDevice();
	virtual ~JDevice();
};

