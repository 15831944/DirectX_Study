#include "JCore.h"
#include "JMap.h"
class JSkyBox : public JBoxShape
{
public:
	JTexture * m_Tex[6];
public:
	bool Render(ID3D11DeviceContext* context)
	{
		context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
		m_dxObj.PreRender(context,sizeof(PNCT_VERTEX));

		for (int iIndex = 0; iIndex < 6; iIndex++)
		{
			context->PSSetShaderResources(0, 1, &m_Tex[iIndex]->m_pSRV);
			context->DrawIndexed(6, iIndex * 6, 0);
		}
		return true;
	}
	bool Release()
	{
		for (int iTex = 0; iTex < 6; iTex++)
		{
			SAFE_RELEASE(m_Tex[iTex]);
		}
		m_dxObj.Release();
		return true;
	}
};

class Sample : public JCore
{
public:
	JSkyBox SkyBox;
	JMap	map;
	D3DXMATRIX matWorld;
	D3DXMATRIX SkyView;
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

		for (int iSky = 0; iSky < 6; iSky++)
		{
			int iTex = I_TexMgr.Add(GetDevice(), Sky[iSky]);
			SkyBox.m_Tex[iSky] = I_TexMgr.GetPtr(iTex);
		}
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matWorld, 2.0f, 2.0f, 2.0f);
		map.SetHeightTexture(GetContext(), L"../../Data/Height_Castle.bmp");
		map.Create(GetDevice(), map.m_iWidth, map.m_iHeight, 1);
		int iTex = I_TexMgr.Add(GetDevice(), L"../../Data/Castle.jpg");
		map.m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTex);
		return true;
	}
	bool Frame()
	{
		SkyView = m_MainCam->m_matView;
		SkyView._41 = 0.0f;
		SkyView._42 = 0.0f;
		SkyView._43 = 0.0f;
		return true;
	}
	bool Render()
	{
		SkyBox.SetMatrix(&matWorld, &SkyView, &m_MainCam->m_matProj);
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