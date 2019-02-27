#include "JDevice.h"
#include "JTimer.h"
#include "JInput.h"
ID3D11Device*   g_pd3dDevice;
bool JDevice::Reset(UINT iWidth, UINT iHeight)
{
	if (m_pd3dDevice == NULL) return true;
	HRESULT hr = S_OK;
	m_pd3dContext->OMSetRenderTargets(0, NULL, NULL);
	if (m_pRT.m_pRTV != NULL) m_pRT.m_pRTV->Release();

	//DXGI_SWAP_CHAIN_DESC CurrentSD;
	//m_pSwapChain->GetDesc(&CurrentSD);
	//m_pSwapChain->ResizeBuffers(CurrentSD.BufferCount, iWidth, iHeight, CurrentSD.BufferDesc.Format, CurrentSD.Flags);

	SAFE_RELEASE(m_pSwapChain);
	CreateSwapChain(m_hWnd, iWidth, iHeight);

	if (FAILED(hr = SetRenderTargetView())) 
		return false;
	//if (FAILED(hr = SetViewPort())) 
	//	return false;

	JWindow::ResizeClient(iWidth, iHeight);
	return true;
}
bool JDevice::InitDevice(HWND hWnd, UINT iWidth, UINT iHeight)
{
	HRESULT hr;
	if (FAILED(CreateDevice())) { return false; }
	if (FAILED(CreateSwapChain(hWnd, iWidth, iHeight))) { return false; }
	if (FAILED(SetRenderTargetView())) { return false; }
	//if (FAILED(SetViewPort())) { return false; }

	if (FAILED(hr = m_pFactory->MakeWindowAssociation(m_hWnd,
		DXGI_MWA_NO_WINDOW_CHANGES |
		DXGI_MWA_NO_ALT_ENTER)))
	{
		return false;
	}
	return true;
}
bool JDevice::Init()
{
	return true;
}
bool JDevice::PreRender()
{
	m_pRT.Begin(GetContext(), m_BKColor, true, true, true);
	return true;
}
bool JDevice::Render()
{
	PreRender();
	m_pRT.End(GetContext());
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
	SAFE_RELEASE(m_pd3dDevice);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pFactory);
	SAFE_RELEASE(m_pd3dContext);
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
	if (m_pd3dDevice == NULL) return E_FAIL;
	HRESULT hr;
	IDXGIDevice * pDXGIDevice;
	hr = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);

	IDXGIAdapter * pDXGIAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&pDXGIAdapter);

	IDXGIFactory * pIDXGIFactory = NULL;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&m_pFactory);

	pDXGIDevice->Release();
	pDXGIAdapter->Release();
	return S_OK;

}
HRESULT JDevice::CreateDevice()
{
	IDXGIAdapter* pAdapter = NULL;
	UINT   createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
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
		if (FAILED(hr = D3D11CreateDevice(pAdapter, DriverType[iIndex], Software, createDeviceFlags,
			&m_FeatureLevel, FeatureLevels, SDKVersion, &m_pd3dDevice, &OutFeatureLevel, &m_pd3dContext)))
		{
			return hr;
		}
		if (OutFeatureLevel < D3D_FEATURE_LEVEL_11_0)
		{
			continue;
		}
		break;
	}
	g_pd3dDevice = m_pd3dDevice;
	return CreateFactory();
}
HRESULT JDevice::CreateSwapChain(HWND hWnd, UINT iWidth, UINT iHeight)
{
	HRESULT hr;
	ZeroMemory(&m_SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	m_SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_SwapChainDesc.BufferDesc.Width = iWidth;
	m_SwapChainDesc.BufferDesc.Height = iHeight;
	m_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	m_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	m_SwapChainDesc.SampleDesc.Count = 1;
	m_SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	m_SwapChainDesc.BufferCount = 1;
	m_SwapChainDesc.OutputWindow = hWnd;
	m_SwapChainDesc.Windowed = TRUE;
	m_SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	if (FAILED(hr = m_pFactory->CreateSwapChain(m_pd3dDevice, &m_SwapChainDesc, &m_pSwapChain)))
	{
		return hr;
	}
	return hr;
}
HRESULT JDevice::SetRenderTargetView()
{
	HRESULT hr = S_OK;
	DXGI_SWAP_CHAIN_DESC SwapDesc;
	hr = m_pSwapChain->GetDesc(&SwapDesc);

	ID3D11Texture2D* pResource = NULL;
	if(FAILED(hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pResource)))
	{
		return hr;
	}
	if (FAILED(hr = m_pRT.Create(GetDevice(), SwapDesc.BufferDesc.Width, SwapDesc.BufferDesc.Height, pResource)))
	{
		return hr;
	}
	return hr;
}
JDevice::JDevice()
{
	m_BKColor[0] = 0.3f;
	m_BKColor[1] = 0.4f;
	m_BKColor[2] = 0.5f;
	m_BKColor[3] = 0.0f;
}


JDevice::~JDevice()
{
}
