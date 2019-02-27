#include "JCore.h"
#include "JMap.h"
#include "Minimap.h"
struct LIGHT_CONSTANT_DATA
{
	D3DXVECTOR4 vDirectionLight;
	D3DXVECTOR4 vDiffuseLight;
	D3DXVECTOR4 vAmbientLight;
	D3DXVECTOR4 vSpecularLight;
	D3DXVECTOR4 vDiffusenColor;
	D3DXVECTOR4 vAmbientColor;
	D3DXVECTOR4 vSpecularColor;
};
class Sample : public JCore
{
public:
	ID3D11Buffer* pBuffer;
	LIGHT_CONSTANT_DATA cbLight;
	JMap map;
	Minimap Mini;
	JTexture* pTexture;
	JCamera ShadowCam;
	D3DXVECTOR3 vLight;
public:
	bool Init()
	{
		map.SetHeightTexture(GetContext(), L"../../Data/Map512.png");
		map.Create(GetDevice(), 64,64, 1.0f);// , L"../../Data/Shader/Default.hlsl", "VS_NORMAL_MAP", "PS_NORMAL_MAP");
		map.SetTexture(L"../../Data/HR.bmp");

		float fX = map.m_iNumCols * 1.0f * map.m_iNumCols * 1.0f;
		float fY = map.m_iNumRows * 1.0f * map.m_iNumRows * 1.0f;
		float fD = sqrt(fX + fY);

		vLight = D3DXVECTOR3(15, 40, -35);
		D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 10.0f, -10.0f);
		D3DXVECTOR3 vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		ShadowCam.SetViewMatrix(vLight, vTarget, vUp);
		D3DXMatrixOrthoOffCenterLH(&ShadowCam.m_matProj, -fD / 2.0f, fD / 2.0f, -fD / 2.0f, fD / 2.0f, 0, 50.0f);
		pBuffer = DX::CreateConstantBuffer(GetDevice(), &cbLight, sizeof(LIGHT_CONSTANT_DATA), 1);

		cbLight.vDirectionLight = D3DXVECTOR4(1000, 1000, 1000, 1);
		cbLight.vAmbientLight = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
		cbLight.vDiffuseLight = D3DXVECTOR4(1, 1, 1, 1);
		cbLight.vDiffusenColor = D3DXVECTOR4(1, 1, 1, 1);
		cbLight.vAmbientColor = D3DXVECTOR4(1, 1, 1, 1);

		Mini.Create(GetDevice(), 0, 0, 200, 200, 800, 600, "PS", "VS", L"PostEffect.hlsl");

		pTexture = I_TexMgr.GetPtr(I_TexMgr.Add(GetDevice(), L"../../Data/HR_N.bmp"));
		return true;
	}
	bool Frame()
	{
		ShadowCam.Frame();
		return true;
	}
	bool Render()
	{
		GetContext()->PSSetSamplers(0, 1, &JState::g_pClampLinear);
		map.SetMatrix(NULL, GetView(), GetProj());
		map.Render(GetContext());

		if (Mini.BeginRender(GetContext(), D3DXVECTOR4(1,1,1, 1)))
		{

			GetContext()->PSSetConstantBuffers(1, 1, &pBuffer);
			GetContext()->VSSetConstantBuffers(1, 1, &pBuffer);
			GetContext()->UpdateSubresource(pBuffer, 0, NULL, &cbLight, 0, 0);
			GetContext()->PSSetShaderResources(1, 1, &pTexture->m_pSRV);

			map.SetMatrix(NULL, &ShadowCam.m_matView, &ShadowCam.m_matProj);
			map.Render(GetContext());
			Mini.EndRender(GetContext());
		}
		GetContext()->PSSetShaderResources(1, 1, &Mini.m_RT.m_pDSV_SRV);
		//map.SetMatrix(NULL, GetView(), GetProj());
		//map.Render(GetContext());
		//GetContext()->PSSetShaderResources(1, 1, &pTexture->m_pSRV);
		Mini.ScreenRender(GetContext());
		Mini.Render(GetContext(), Mini.m_RT.m_pDSV_SRV);// Mini.m_RT.m_pDSV_SRV);
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;