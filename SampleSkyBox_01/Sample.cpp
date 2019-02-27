#include "JCore.h"
#include "JMap.h"
#include "JSkyBox.h"
//class JSkyBox : public JBoxShape
//{
//public:
//	JTexture * m_Tex[6];
//	D3DXMATRIX m_matSkyView;
//	//D3DXMATRIX m_matWorld;
//public:
//	bool Create(ID3D11Device* device, const TCHAR* szSkyName[])
//	{
//		for (int iSky = 0; iSky < 6; iSky++)
//		{
//			int iTex = I_TexMgr.Add(device, szSkyName[iSky]);
//			m_Tex[iSky] = I_TexMgr.GetPtr(iTex);
//		}
//		D3DXMatrixIdentity(&m_matView);
//		D3DXMatrixScaling(&m_matWorld, 100.0f, 100.0f, 100.0f);
//		return true;
//	}
//	bool Render(ID3D11DeviceContext* context)
//	{
//		m_matSkyView = m_matView;
//		m_matSkyView._41 = 0.0f;
//		m_matSkyView._42 = 0.0f;
//		m_matSkyView._43 = 0.0f;
//
//		SetMatrix(&m_matWorld, &m_matSkyView, &m_matProj);
//
//		context->OMSetDepthStencilState(JState::g_pDisableDSS, 0x00);
//		context->OMSetBlendState(JState::g_pAlphaBlend, 0, -1);
//
//		context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
//		m_dxObj.PreRender(context, sizeof(PNCT_VERTEX));
//
//		for (int iIndex = 0; iIndex < 6; iIndex++)
//		{
//			context->PSSetShaderResources(0, 1, &m_Tex[iIndex]->m_pSRV);
//			context->DrawIndexed(6, iIndex * 6, 0);
//		}
//		context->OMSetDepthStencilState(JState::g_pEnableDSS, 0x00);
//		return true;
//	}
//	bool Release()
//	{
//		for (int iTex = 0; iTex < 6; iTex++)
//		{
//			SAFE_RELEASE(m_Tex[iTex]);
//		}
//		m_dxObj.Release();
//		return true;
//	}
//};

class Sample : public JCore
{
public:
	JSkyBox SkyBox;
	JMap	map;
public:
	bool Init()
	{
		SkyBox.Init();
		const TCHAR* Sky[] =
		{
			{ L"../../Data/SkyBox/Sky/st00_cm_front.bmp" },
			{ L"../../Data/SkyBox/Sky/st00_cm_back.bmp" },
			{ L"../../Data/SkyBox/Sky/st00_cm_right.bmp" },
			{ L"../../Data/SkyBox/Sky/st00_cm_left.bmp" },
			{ L"../../Data/SkyBox/Sky/st00_cm_up.bmp" },
			{ L"../../Data/SkyBox/Sky/st00_cm_down.bmp" },
		};
		SkyBox.Create(GetDevice(), Sky);
		
		map.SetHeightTexture(GetContext(), L"../../Data/Height_Castle.bmp");
		map.Create(GetDevice(), map.m_iWidth, map.m_iHeight, 1);
		int iTex = I_TexMgr.Add(GetDevice(), L"../../Data/Castle.jpg");
		map.m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTex);
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		SkyBox.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		SkyBox.Render(GetContext());

		map.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		map.Render(GetContext());
		return true;
	}
	bool Release()
	{
		SkyBox.Release();
		map.Release();
		return true;
	}
};
RUN;