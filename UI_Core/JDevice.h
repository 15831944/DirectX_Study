#pragma once
#include "JWindow.h"
#include "DxRT.h"
class JDevice : public JWindow
{
public:
	ID3D11Device*			m_pd3dDevice;
	IDXGISwapChain*			m_pSwapChain;
	IDXGIFactory*			m_pFactory;
	ID3D11DeviceContext*	m_pd3dContext;
	DxRT					m_pRT;
	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;
	//D3D11_VIEWPORT			m_ViewPort;
public:
	float m_BKColor[4];
public:
	ID3D11Device*			GetDevice();
	ID3D11DeviceContext*	GetContext();
public:
	HRESULT					CreateFactory();
	HRESULT					CreateDevice();
	HRESULT					CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight);
	HRESULT					SetRenderTargetView();
	//HRESULT					SetViewPort();
	bool					InitDevice(HWND hWnd, UINT iWidth, UINT iHeight);
	bool					Reset(UINT iWidth, UINT iHeight);
public:
	bool					Init();
	bool					PreRender();
	bool					Render();
	bool					PostRender();
	bool					Release();
public:
	JDevice();
	virtual ~JDevice();
};

