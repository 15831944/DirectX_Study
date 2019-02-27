#include "JCore.h"
#include "JPlaneShape.h"
class Sample : public JCore
{
public:
	JPlaneShape m_Plane0;
	JPlaneShape m_Plane1;
	D3D11_VIEWPORT view[2];
public:
	bool Init()
	{
		m_Plane0.Init();
		int iTex = I_TexMgr.Add(GetDevice(), L"hud.dds");
		JTexture* tex = I_TexMgr.GetPtr(iTex);
		m_Plane0.m_pSRV = tex->m_pSRV;

		m_Plane1.Init();
		iTex = I_TexMgr.Add(GetDevice(), L"Dirt_Diff.dds");
		JTexture* tex1 = I_TexMgr.GetPtr(iTex);
		m_Plane1.m_pSRV = tex1->m_pSRV;

		view[0].Width = g_rtClient.right / 2.0f;
		view[0].Height = g_rtClient.bottom;
		view[0].MaxDepth = 1;
		view[0].MinDepth = 0;
		view[0].TopLeftX = 0;
		view[0].TopLeftY = 0;

		view[1].Width = g_rtClient.right / 2.0f;
		view[1].Height = g_rtClient.bottom;
		view[1].MaxDepth = 1;
		view[1].MinDepth = 0;
		view[1].TopLeftX = g_rtClient.right / 2.0f;
		view[1].TopLeftY = 0;
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		GetContext()->RSSetViewports(1, &view[0]);
		m_Plane0.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_Plane0.Render(GetContext());

		GetContext()->RSSetState(JState::g_pRSFrontCullSolid);
		GetContext()->RSSetViewports(1, &view[1]);
		m_Plane1.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_Plane1.Render(GetContext());

		GetContext()->RSSetState(JState::g_pRSBackCullSolid);
		GetContext()->RSSetViewports(1, &view[1]);
		m_Plane0.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_Plane0.Render(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;