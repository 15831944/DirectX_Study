#include "JCore.h"
void JCore::MsgEvent(MSG msg)
{
	I_Input.MsgEvent(msg);
}
bool JCore::GameRun()
{
	GameFrame();
	GameRender();
	return true;
}
bool JCore::GameInit()
{
	JDevice::InitDevice(m_hWnd, g_rtClient.right, g_rtClient.bottom);
	I_Timer.Init();
	I_Input.Init();
	I_InputDx.Init();
	I_InputDx.InitDirectInput(m_hInstance, m_hWnd, true, true);
	IDXGISurface1 *pResource = 0;
	if (SUCCEEDED(m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (LPVOID*)&pResource)))
	{
		if (false == I_Write.Set(pResource))
		{
			return false;
		}
	}
	SAFE_RELEASE(pResource);
	Init();
	return true;
}
bool JCore::GameFrame()
{
	I_Timer.Frame();
	I_Input.Frame();
	I_InputDx.Frame();
	if (I_Input.KeyCheck('T') == KEY_PUSH)
	{
		m_bShowDebug = !m_bShowDebug;
	}
	PreFrame();
	Frame();
	PostFrame();
	return true;
}
bool JCore::GameRender()
{
	PreRender();
	GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Render();
	if (m_bShowDebug)
	{
		I_Timer.Render();
		I_Input.Render();
	}
	PostRender();
	return true;
}
bool JCore::GameRelease()
{

	Release();
	I_Timer.Release();
	I_Input.Release();
	I_InputDx.Release();
	JDevice::Release();
	I_Write.Release();
	m_pRT.Release();
	return true;
}
bool JCore::PreFrame()
{

	return true;
}
bool JCore::PreRender()
{
	JDevice::PreRender();
	return true;
}
bool JCore::PostFrame()
{
	return true;
}
bool JCore::PostRender()
{
	JDevice::PostRender();
	return true;
}
bool JCore::Init()
{
	return true;
}
bool JCore::Frame()
{
	return true;
}
bool JCore::Render()
{
	return true;
}
bool JCore::Release()
{
	return true;
}

bool JCore::ResizeClient(UINT iWidth, UINT iHeight)
{
	if (m_pSwapChain == NULL || m_pd3dDevice == NULL) return true;
	I_Write.Release();

	JDevice::Reset(iWidth, iHeight);

	IDXGISurface1 *pResource = 0;
	if (SUCCEEDED(m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (LPVOID*)&pResource)))
	{
		if (false == I_Write.Set(pResource))
		{
			return false;
		}
	}
	SAFE_RELEASE(pResource);

	JWindow::ResizeClient(iWidth, iHeight);
	return true;
}

JCore::JCore()
{
	m_bShowDebug = false;
}


JCore::~JCore()
{
}
