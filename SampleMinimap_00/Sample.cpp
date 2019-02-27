#include "JCore.h"
#include "JBoxShape.h"
#include "Plane.h"
#include "DxRT.h"
class Sample : public JCore
{
public:
	JBoxShape m_Box2;
	JBoxShape m_Box;
	DxRT m_RT;
	Plane Screen;
	Plane Minimap;
	D3D11_VIEWPORT m_MinimapViewPort;
public:
	bool Init()
	{
		m_Box.Init();
		m_Box2.Init();
		Screen.Init();
		Minimap.Init();

		m_RT.Create(GetDevice(), 800, 600);
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		if (m_RT.Begin(GetContext(), D3DXVECTOR4(0.3f, 0.4f, 0.5f, 1)))
		{
			m_Box.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
			m_Box.Render(GetContext());

			D3DXMATRIX matWorld;
			D3DXMatrixTranslation(&matWorld, 3, 0, 0);
			m_Box2.SetMatrix(&matWorld, &m_MainCam->m_matView, &m_MainCam->m_matProj);
			m_Box2.Render(GetContext());

			m_RT.End(GetContext());
		}

		Screen.m_pSRV = m_RT.m_pRTV_SRV;
		Screen.SetMatrix(NULL, NULL, NULL);
		Screen.Render(GetContext());

		m_MinimapViewPort.TopLeftX = 0;
		m_MinimapViewPort.TopLeftY = g_rtClient.bottom - 200;
		m_MinimapViewPort.Width = 200;
		m_MinimapViewPort.Height = 200;
		m_MinimapViewPort.MinDepth = 0;
		m_MinimapViewPort.MaxDepth = 1;
		GetContext()->RSSetViewports(1, &m_MinimapViewPort);

		Minimap.m_pSRV = m_RT.m_pRTV_SRV;
		Minimap.SetMatrix(NULL, NULL, NULL);
		Minimap.Render(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;