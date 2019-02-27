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
	JMap map;
	LIGHT_CONSTANT_DATA cbLight;
	ID3D11Buffer* pBuffer;

	JBoxShape box;
	JBoxShape Shadow;
	D3DXMATRIX matWorld;

	JCamera ShadowCam;
	D3DXVECTOR4 vDirLight;
	Minimap mini;
public:
	bool Init()
	{
		pBuffer = DX::CreateConstantBuffer(GetDevice(), &cbLight, sizeof(LIGHT_CONSTANT_DATA), 1);

		map.Init();
		map.SetHeightTexture(GetContext(), L"../../Data/Height_Castle.bmp");
		map.Create(GetDevice(), 64, 64, 1);
		map.SetTexture(L"../../Data/Castle.jpg");
		map.ChangedPixelShader("PS_ProjShadow");

		vDirLight = D3DXVECTOR4(-0.00001f, 40, -10.0f, 1);
		cbLight.vDirectionLight = vDirLight;
		cbLight.vAmbientLight = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
		cbLight.vDiffuseLight = D3DXVECTOR4(1, 1, 1, 1);
		cbLight.vDiffusenColor = D3DXVECTOR4(1, 1, 1, 1);
		cbLight.vAmbientColor = D3DXVECTOR4(1, 1, 1, 1);

		box.Init();
		box.ChangedPixelShader("PSMeshColor");
		Shadow.Init();

		// ShadowCamera
		D3DXVECTOR3 vPos = D3DXVECTOR3(vDirLight.x, vDirLight.y, vDirLight.z);
		D3DXVECTOR3 vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		ShadowCam.SetViewMatrix(vPos, vTarget, vUp);
		D3DXMatrixPerspectiveFovLH(&ShadowCam.m_matProj, D3DX_PI / 2, 1, 0.1f, 1000.0f);

		mini.Init();
		mini.Create(GetDevice(), 0, 400, 200,200 );
		return true;
	}
	bool Frame()
	{
		float fTime = I_Timer.m_fGameTimer * 3.141592f;
		D3DXMATRIX mattrans, matscl;
		D3DXMatrixScaling(&matscl, 3,3,3);
		D3DXMatrixTranslation(&mattrans, cos(fTime) * 5.0f, 25.0f, 0);

		matWorld = matscl * mattrans ;
		return true;
	}
	bool Render()
	{
		// ½¦µµ¿ì ¸Ê »ý¼º
		if (mini.BeginRender(GetContext(), D3DXVECTOR4(0, 0, 0, 1)))
		{

			box.m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
			box.SetMatrix(&matWorld, &ShadowCam.m_matView, &ShadowCam.m_matProj);
			box.Render(GetContext());

			mini.EndRender(GetContext());
		}

		// ¸Ê ·»´õ
		
		GetContext()->PSSetConstantBuffers(1, 1, &pBuffer);
		GetContext()->VSSetConstantBuffers(1, 1, &pBuffer);
		GetContext()->UpdateSubresource(pBuffer, 0, NULL, &cbLight, 0, 0);
		GetContext()->PSSetShaderResources(1, 1, &mini.m_RT.m_pRTV_SRV);
		map.m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
		map.SetMatrix(NULL, GetView(), GetProj());
		map.Render(GetContext());

		// ¹Ú½º ·»´õ
		box.m_cbData.vColor = D3DXVECTOR4(0.9f, 0.4f, 0.6f, 1);
		box.SetMatrix(&matWorld, GetView(), GetProj());
		box.Render(GetContext());

		// ¹Ì´Ï¸Ê ·»´õ
		mini.Render(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;