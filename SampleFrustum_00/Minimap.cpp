#include "Minimap.h"
#include "JDxInput.h"
//bool Minimap::Frame()
//{
//	if (I_InputDx.m_MouseState.rgbButtons[0])
//	{
//		m_fYaw += D3DXToRadian(I_InputDx.m_MouseState.lX * 0.1f);
//		m_fPitch += D3DXToRadian(I_InputDx.m_MouseState.lY * 0.1f);
//	}
//	m_fRadius = 0.0f;
//	if (I_InputDx.m_MouseState.lZ != 0)
//	{
//		m_fRadius = I_InputDx.m_MouseState.lZ * g_fSecPerFrame;
//	}
//	return Update(m_fPitch, m_fYaw, 0.0f, m_fRadius);
//}
bool Minimap::BeginRender(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget, bool bDepth, bool bStencil)
{
	m_RT.Begin(context, vColor, bTarget, bDepth, bStencil);
	return true;
}
bool Minimap::EndRender(ID3D11DeviceContext* context)
{
	m_RT.End(context);
	return true;
}
bool Minimap::Create(ID3D11Device* device, FLOAT fTopX, FLOAT fTopY, FLOAT fWidth, FLOAT fHeight)
{
	m_Screen.Init();
	m_Minimap.Init();

	m_RT.Create(device, g_rtClient.right, g_rtClient.bottom);

	m_MinimapViewPort.TopLeftX = fTopX;
	m_MinimapViewPort.TopLeftY = fTopY;
	m_MinimapViewPort.Width = fWidth;
	m_MinimapViewPort.Height = fHeight;
	m_MinimapViewPort.MinDepth = 0;
	m_MinimapViewPort.MaxDepth = 1;

	D3DXVECTOR3 vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 100.0f, -1.0f);

	SetViewMatrix(vPos, vTarget, vUp);
	SetProjMatrix(D3DX_PI * 0.25f, (float)fWidth / (float)fHeight, 0.1f, 10000.0f);
	return true;
}
bool Minimap::Render(ID3D11DeviceContext* context)
{
	//m_Screen.m_pSRV = m_RT.m_pRTV_SRV;
	//m_Screen.SetMatrix(NULL, NULL, NULL);
	//m_Screen.Render(context);

	context->RSSetViewports(1, &m_MinimapViewPort);

	m_Minimap.m_pSRV = m_RT.m_pRTV_SRV;
	m_Minimap.SetMatrix(NULL, NULL, NULL);
	m_Minimap.Render(context);
	return true;
}
Minimap::Minimap()
{
}


Minimap::~Minimap()
{
}
