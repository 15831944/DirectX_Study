#include "JDevice.h"
#include "JTimer.h"
ID3D11Device* g_pd3dDevice;

HRESULT JDevice::CreateBlendState()
{
	HRESULT hr;
	D3D11_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.AlphaToCoverageEnable = TRUE;
	BlendState.RenderTarget->BlendEnable = TRUE;
	BlendState.RenderTarget->BlendOp = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget->SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendState.RenderTarget->DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendState.RenderTarget->BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget->SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendState.RenderTarget->DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendState.RenderTarget->RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	FAILED(hr = m_pd3dDevice->CreateBlendState(&BlendState, &m_pAlphaBlend));
	return hr;
}

HRESULT JDevice::ReziseDevice(UINT width, UINT height)
{
	HRESULT hr = S_OK;
	if (m_pSwapChain)
	{
		HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&m_pSurface);
		if (m_pSurface) m_pSurface->Release();
	}
	if (!m_pd3dDevice) return S_OK;
	hr = m_pd3dDevice->CreateRenderTargetView(0, NULL, NULL);
	m_pRTV->Release();

	m_pSwapChain->ResizeBuffers(m_SwapChainDesc.BufferCount, width, height, m_SwapChainDesc.BufferDesc.Format, m_SwapChainDesc.Flags);
	SetRenderTargetView();
	SetViewPort();
	return hr;
}
bool JDevice::PreRender()
{
	//color[0] = cosf(I_Timer.m_fGameTimer * 0.5f + 0.5f);
	//color[1] = sinf(I_Timer.m_fGameTimer * 0.5f + 0.5f);
	//color[2] = sinf(I_Timer.m_fGameTimer * 0.5f + 0.5f);
	m_pd3dContext->ClearRenderTargetView(m_pRTV, m_BKColor);
	return true;
}
bool JDevice::Render()
{
	PreRender();
	PostRender();
	return true;
}
bool JDevice::PostRender()
{
	m_pSwapChain->Present(0,0);
	return true;
}
bool JDevice::Release()
{
	Clear();
	return true;
}
ID3D11Device* JDevice::GetDevice()
{
	return m_pd3dDevice;
}
ID3D11DeviceContext* JDevice::GetContext()
{
	return m_pd3dContext;
}
HRESULT JDevice::CreateFactory()
{
	HRESULT hr;
	if (FAILED(hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_pFactory))))
	{
		return hr;
	}
	return hr;

}
HRESULT JDevice::CreateDevice()
{
	IDXGIAdapter* pAdapter = NULL;
	D3D_DRIVER_TYPE DriverType[] = 
	{ 
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP ,
		D3D_DRIVER_TYPE_REFERENCE
	};
	HMODULE Software = NULL;
	UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	D3D_FEATURE_LEVEL m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	UINT FeatureLevels = 1;
	UINT SDKVersion = D3D11_SDK_VERSION;
	D3D_FEATURE_LEVEL OutFeatureLevel;

	UINT DriverCnt = sizeof(DriverType) / sizeof(DriverType[0]);

	HRESULT hr;
	for (int iIndex = 0; iIndex < DriverCnt; iIndex++)
	{
		if (FAILED(hr = D3D11CreateDevice(pAdapter, DriverType[iIndex], Software, Flags,
			&m_FeatureLevel, FeatureLevels, SDKVersion, &m_pd3dDevice, &OutFeatureLevel, &m_pd3dContext)))
		{
			return hr;
		}
		if (FeatureLevels < D3D_FEATURE_LEVEL_11_0)
		{
			continue;
		}
		break;
	}
	g_pd3dDevice = m_pd3dDevice;
	return hr;
}
HRESULT JDevice::CreateSwapChain()
{
	HRESULT hr;
	ZeroMemory(&m_SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	m_SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	m_SwapChainDesc.BufferDesc.Width = g_rtWindow.right;
	m_SwapChainDesc.BufferDesc.Height = g_rtWindow.bottom;
	m_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	m_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60; 
	m_SwapChainDesc.SampleDesc.Count = 1;
	m_SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	m_SwapChainDesc.BufferCount = 1; 
	m_SwapChainDesc.OutputWindow = g_hWnd;
	m_SwapChainDesc.Windowed = true;
	m_SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	
	if (FAILED(hr = m_pFactory->CreateSwapChain(m_pd3dDevice, &m_SwapChainDesc, &m_pSwapChain)))
	{
		return hr;
	}
	return hr;
}
HRESULT JDevice::CreateSurface()
{
	HRESULT hr = S_OK;
	if (FAILED(m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (LPVOID*)&m_pSurface)))
	{
		return hr;
	}
	return hr;
}
HRESULT JDevice::SetRenderTargetView()
{
	HRESULT hr;
	if (FAILED(hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_pTexture2D)))
	{
		return hr;
	}
	if (FAILED(hr = m_pd3dDevice->CreateRenderTargetView(m_pTexture2D, NULL, &m_pRTV)))
	{
		return hr;
	}
	m_pd3dContext->OMSetRenderTargets(1, &m_pRTV, NULL); 
	m_pTexture2D->Release();
	return hr;
}
HRESULT JDevice::SetViewPort()
{
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.Width = g_rtWindow.right;
	m_ViewPort.Height = g_rtWindow.bottom;
	m_ViewPort.MinDepth = 0;
	m_ViewPort.MaxDepth = 1;
	m_pd3dContext->RSSetViewports(1, &m_ViewPort);
	return S_OK;
}
HRESULT JDevice::InitDevice()
{
	HRESULT hr = S_OK;
	if (FAILED(hr = CreateFactory()))
	{
		return hr;
	}
	if (FAILED(hr = CreateDevice()))
	{
		return hr;
	}
	if (FAILED(hr = CreateSwapChain()))
	{
		return hr;
	}
	if (FAILED(hr = SetRenderTargetView()))
	{
		return hr;
	}
	if (FAILED(hr = CreateSurface()))
	{
		return hr;
	}
	if (FAILED(hr = SetViewPort()))
	{
		return hr;
	}
	return hr;
}
void JDevice::Clear()
{
	m_pd3dDevice->Release();
	m_pd3dContext->Release();
	m_pRTV->Release();
	m_pFactory->Release();
	m_pSwapChain->Release();
}
JDevice::JDevice()
{
	m_BKColor[0] = 0.0f;
	m_BKColor[1] = 0.0f;
	m_BKColor[2] = 0.0f;
	m_BKColor[3] = 0.0f;
	m_pd3dDevice	= nullptr;
	m_pd3dContext	= nullptr;
	m_pFactory		= nullptr;
	m_pRTV			= nullptr;
	m_pSwapChain	= nullptr;
}


JDevice::~JDevice()
{
}
