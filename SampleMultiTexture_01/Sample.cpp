#include "JCore.h"
#include "JBoxShape.h"
#include "JDxHelper.h"
class Sample : public JCore
{
public:
	JBoxShape m_Box;
	JTexture* m_pTex[6];
	D3D11_VIEWPORT m_View[4];
	float fTime;
public:
	bool Init()
	{
		int iTex;
		m_Box.Create();
		iTex = I_TexMgr.Add(GetDevice(), L"leaf_v3_dark_tex.dds");
		m_pTex[0] = I_TexMgr.GetPtr(iTex);
		iTex = I_TexMgr.Add(GetDevice(), L"leaf_v3_olive_tex.dds");
		m_pTex[1] = I_TexMgr.GetPtr(iTex);
		iTex = I_TexMgr.Add(GetDevice(), L"leaf_v3_green_tex.dds");
		m_pTex[2] = I_TexMgr.GetPtr(iTex);
		iTex = I_TexMgr.Add(GetDevice(), L"dry_flowers_v1_tex.dds");
		m_pTex[3] = I_TexMgr.GetPtr(iTex);
		iTex = I_TexMgr.Add(GetDevice(), L"leaf2.dds");
		m_pTex[4] = I_TexMgr.GetPtr(iTex);
		iTex = I_TexMgr.Add(GetDevice(), L"tree02S.dds");
		m_pTex[5] = I_TexMgr.GetPtr(iTex);


		m_View[0].Width = g_rtClient.right / 2.0f;
		m_View[0].Height = g_rtClient.bottom / 2.0f;
		m_View[0].MaxDepth = 1;
		m_View[0].MinDepth = 0;
		m_View[0].TopLeftX = 0;
		m_View[0].TopLeftY = 0;

		m_View[1].Width = g_rtClient.right / 2.0f;
		m_View[1].Height = g_rtClient.bottom / 2.0f;
		m_View[1].MaxDepth = 1;
		m_View[1].MinDepth = 0;
		m_View[1].TopLeftX = g_rtClient.right / 2.0f;
		m_View[1].TopLeftY = 0;

		m_View[2].Width = g_rtClient.right / 2.0f;
		m_View[2].Height = g_rtClient.bottom / 2.0f;
		m_View[2].MaxDepth = 1;
		m_View[2].MinDepth = 0;
		m_View[2].TopLeftX = 0;
		m_View[2].TopLeftY = g_rtClient.bottom / 2.0f;;

		m_View[3].Width = g_rtClient.right / 2.0f;
		m_View[3].Height = g_rtClient.bottom / 2.0f;
		m_View[3].MaxDepth = 1;
		m_View[3].MinDepth = 0;
		m_View[3].TopLeftX = g_rtClient.right / 2.0f;
		m_View[3].TopLeftY = g_rtClient.bottom / 2.0f;

		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		fTime = (int)I_Timer.m_fGameTimer % 6;
		GetContext()->RSSetViewports(1, &m_View[0]);
		GetContext()->PSSetShaderResources(1, 1, &m_pTex[0]->m_pSRV);
		m_Box.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_Box.Render(GetContext());

		GetContext()->RSSetViewports(1, &m_View[1]);
		m_Box.m_dxObj.m_pTexture = m_pTex[(int)fTime];
		m_Box.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_Box.Render(GetContext());

		GetContext()->RSSetViewports(1, &m_View[2]);
		m_Box.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_Box.Render(GetContext());

		GetContext()->RSSetViewports(1, &m_View[3]);
		m_Box.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		m_Box.Render(GetContext());

		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;