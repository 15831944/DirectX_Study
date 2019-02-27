#include "JCore.h"
D3DXMATRIX* JCore::GetView()
{
	return &m_MainCam->m_matView;
}
D3DXMATRIX* JCore::GetProj()
{
	return &m_MainCam->m_matProj;
}
void JCore::SwapCamera(JCamera* cam)
{
	m_MainCam = cam;
}
void JCore::InitCamera()
{
	m_MainCam = &m_Camera[0];
}
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
	JState::SetState(GetDevice());
	I_Timer.Init();
	I_Input.Init();
	I_InputDx.Init();
	I_InputDx.InitDirectInput(m_hInstance, m_hWnd, true, true);
	m_LineShape = new JLineShape();
	m_LineShape->Init();

	D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 50.0f, -50.0f);
	D3DXVECTOR3 vTarget = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Camera[0].SetViewMatrix(vPos, vTarget, vUp); // QuarterView
	swprintf_s(m_Camera[0].m_szCameraName, _T("QuarterView"));

	vPos = D3DXVECTOR3(0.0f, 10.0f, -1.0f);
	m_Camera[1].SetViewMatrix(vPos, vTarget, vUp); // TopView
	swprintf_s(m_Camera[1].m_szCameraName, _T("TopView"));

	vPos = D3DXVECTOR3(10.0f, 0.0f, -1.0f);
	m_Camera[2].SetViewMatrix(vPos, vTarget, vUp); // SideView
	swprintf_s(m_Camera[2].m_szCameraName, _T("SideView"));

	vPos = D3DXVECTOR3(0.0f, 0.0f, -10.0f);
	m_Camera[3].SetViewMatrix(vPos, vTarget, vUp); // FrontView
	swprintf_s(m_Camera[3].m_szCameraName, _T("FrontView"));

	vPos = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_Camera[4].SetViewMatrix(vPos, vTarget, vUp); // OrtorView
	swprintf_s(m_Camera[4].m_szCameraName, _T("OrtorView"));

	m_Camera[4].SetOrthoMatrix((float)g_rtClient.right, (float)g_rtClient.bottom, 0.1f, 1000.0f);// g_rtClient.right, g_rtClient.bottom, 0.1f, 1.0f);
	for (int iCam = 0; iCam < 4; iCam++)
	{
		m_Camera[iCam].SetProjMatrix(GetContext(), D3DX_PI* 0.25f,
			(float)g_rtClient.right / (float)g_rtClient.bottom,
			0.1f, 1000.0f);
	}
	InitCamera();


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
	if (m_MainCam->m_szCameraName != m_Camera[4].m_szCameraName)
	{
		m_MainCam->Frame();
	}
	m_LineShape->Frame();
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
	if (I_Input.KeyCheck('1') == KEY_UP)
	{
		SwapCamera(&m_Camera[0]);
	}
	if (I_Input.KeyCheck('2') == KEY_UP)
	{
		SwapCamera(&m_Camera[1]);
	}
	if (I_Input.KeyCheck('3') == KEY_UP)
	{
		SwapCamera(&m_Camera[2]);
	}
	if (I_Input.KeyCheck('4') == KEY_UP)
	{
		SwapCamera(&m_Camera[3]);
	}
	if (I_Input.KeyCheck('5') == KEY_UP)
	{
		SwapCamera(&m_Camera[4]);
	}
#if defined(DEBUG) || defined(_DEBUG)
	if (m_bShowDebug)
	{
		I_Timer.Render();
		I_Input.Render();
		I_InputDx.Render();
		//m_MainCam->Render(GetContext());

		I_Write.Draw(m_MainCam->m_szCameraName, 15, { 0,100,800,800 });

		if (I_Input.KeyCheck('V') == KEY_HOLD)
		{
			GetContext()->RSSetState(JState::g_pRSWireFrame);
			I_Write.RedDraw(L"WireFrame (V)", 15, { 0,30,800,800 });
		}
		else if (I_Input.KeyCheck('F') == KEY_HOLD)
		{
			GetContext()->RSSetState(JState::g_pRSFrontCullSolid);
			I_Write.RedDraw(L"FrontCullSolid (F)", 15, { 0,30,800,800 });
		}
		else
		{
			GetContext()->RSSetState(JState::g_pRSNoneCullSolid);
			I_Write.BlueDraw(L"WireFrame (V), FrontCullSolid (F)", 15, { 0,30,800,800 });
		}

		if (I_Input.KeyCheck('B') == KEY_HOLD)
		{
			GetContext()->OMSetBlendState(JState::g_pNoAlphaBlend, 0, -1);
			I_Write.RedDraw(L"NoAlphaBlend (B)", 15, { 0,45,800,800 });
		}
		else
		{
			GetContext()->OMSetBlendState(JState::g_pAlphaBlend, 0, -1);
			I_Write.BlueDraw(L"AlphaBlend (B)", 15, { 0,45,800,800 });
		}
		if (I_Input.KeyCheck('N') == KEY_HOLD)
		{
			GetContext()->OMSetDepthStencilState(JState::g_pDisableDSS, 0x00);
			I_Write.RedDraw(L"Depth Disable (N)", 15, { 0,60,800,800 });
		}
		else
		{
			GetContext()->OMSetDepthStencilState(JState::g_pEnableDSS, 0x00);
			I_Write.BlueDraw(L"Depth Enable (N)", 15, { 0,60,800,800 });
		}
		I_Write.RedDraw(L"X", 15, { 760,60,800,800 }); I_Write.GreenDraw(L"Y", 15, { 770,60,800,800 }); I_Write.BlueDraw(L"Z", 15, { 780,60,800,800 });

		//m_LineShape->SetMatrix(nullptr, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_LineShape->Draw(GetContext(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10000.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
		m_LineShape->Draw(GetContext(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10000.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f));
		m_LineShape->Draw(GetContext(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 10000.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f));
	}
#else
#endif
	PostRender();
	return true;
}
bool JCore::GameRelease()
{

	Release();
	I_Timer.Release();
	I_Input.Release();
	I_InputDx.Release();
	JState::Release();
	JDevice::Release();
	I_Write.Release();
	I_TexMgr.Release();
	m_pRT.Release();
	return true;
}
bool JCore::PreFrame()
{
	if (I_Input.KeyCheck('T') == KEY_PUSH)
		m_bShowDebug = !m_bShowDebug;
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
	GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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
