#include "JCore.h"
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
	JMap map;
	LIGHT_CONSTANT_DATA cbLight;
	ID3D11Buffer* pBuffer;
public:
	bool Init()
	{
		pBuffer = DX::CreateConstantBuffer(GetDevice(), &cbLight, sizeof(LIGHT_CONSTANT_DATA), 1);

		map.Init();
		map.SetHeightTexture(GetContext(), L"../../Data/Map512.png");
		map.Create(GetDevice(), 512, 512, 1,L"../../Data/Shader/Default.hlsl","VS","PS_Diffuse");
		//map.SetTexture(L"../../Data/Map512Color.png");

		cbLight.vDirectionLight = D3DXVECTOR4(1000, 1000, 1000, 1);
		cbLight.vAmbientLight = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
		cbLight.vDiffuseLight = D3DXVECTOR4(1, 1, 1, 1);
		cbLight.vDiffusenColor = D3DXVECTOR4(1, 1, 1, 1);
		cbLight.vAmbientColor = D3DXVECTOR4(1, 1, 1, 1);
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		GetContext()->PSSetConstantBuffers(1, 1, &pBuffer);
		GetContext()->VSSetConstantBuffers(1, 1, &pBuffer);
		GetContext()->UpdateSubresource(pBuffer, 0, NULL, &cbLight, 0, 0);
		//GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//GetContext()->PSGetShaderResources(0, 1, &map.m_dxObj.m_pTexture->m_pSRV);
		map.m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
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