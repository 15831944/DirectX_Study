#include "JCore.h"
#include "JBoxShape.h"
#include "JMap.h"
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
	JTexture* pNormal;
	JBoxShape box;
	JMap map;
public:
	bool Init()
	{
		pBuffer = DX::CreateConstantBuffer(GetDevice(), &cbLight, sizeof(LIGHT_CONSTANT_DATA), 1);
		map.Create(GetDevice(), 32,32,1,L"../../Data/Shader/Default.hlsl","VS_NORMAL_MAP", "PS_NORMAL_MAP");
		map.SetTexture(L"../../Data/stone_wall.bmp");

		pNormal = I_TexMgr.GetPtr(I_TexMgr.Add(GetDevice(), L"../../Data/stone_wall_normal_map.bmp"));

		cbLight.vDirectionLight = D3DXVECTOR4(1000, 1000, 1000, 1);
		cbLight.vAmbientLight = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
		cbLight.vDiffuseLight = D3DXVECTOR4(1, 1, 1, 1);
		cbLight.vDiffusenColor = D3DXVECTOR4(1, 1, 1, 1);
		cbLight.vAmbientColor = D3DXVECTOR4(1, 1, 1, 1);
		return true;
	}
	bool Frame()
	{
		float fTime = I_Timer.m_fGameTimer;

		//D3DXMATRIX matTrans;
		//D3DXMatrixTranslation(&matTrans, cos(fTime), sin(fTime), cos(fTime));

		//cbLight.vDirectionLight = D3DXVECTOR4(matTrans._41, matTrans._42, matTrans._43, 1.0f);
		return true;
	}
	bool Render()
	{
		GetContext()->PSSetConstantBuffers(1, 1, &pBuffer);
		GetContext()->VSSetConstantBuffers(1, 1, &pBuffer);
		GetContext()->UpdateSubresource(pBuffer, 0, NULL, &cbLight, 0, 0);

		GetContext()->PSSetShaderResources(1, 1, &pNormal->m_pSRV);
		map.SetMatrix(NULL, GetView(), GetProj());
		map.Render(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;