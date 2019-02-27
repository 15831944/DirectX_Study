#include "JDxEventUI.h"

bool JDxEventUI::Init()
{
	m_EventUI.SetRect(50, 50, 910, 430);
	m_EventUI.Create(g_pd3dDevice);
	m_EventUI.CreateVertexBuffer(g_pd3dDevice);
	m_EventUI.Load(g_pd3dDevice, L"../../Data/bitmap/BackGround1.bmp");
	return true;
}
bool JDxEventUI::Frame()
{
	return true;
}
bool JDxEventUI::Render(ID3D11DeviceContext* context)
{
	if (m_bShowEvent)
	{
		m_EventUI.Render(context);
	}
	return true;
}
bool JDxEventUI::Release()
{
	m_EventUI.Release();
	return true;
}

JDxEventUI::JDxEventUI()
{
	m_bShowEvent = false;
}


JDxEventUI::~JDxEventUI()
{
}
