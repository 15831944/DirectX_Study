#include "JCore.h"
#include "JMap.h"

class Sample : public JCore
{
public:
	JMap map;
	LIGHT_CONSTANT cbData;
	ID3D11Buffer* pConstantBuffer;
public:
	bool Init()
	{
		pConstantBuffer = DX::CreateConstantBuffer(g_pd3dDevice, &cbData, sizeof(LIGHT_CONSTANT), 1);

		map.Init();
		map.SetHeightTexture(GetContext(), L"../../data/Map512.png");
		map.Create(GetDevice(), 512,512, 1);
		int iTexture = I_TexMgr.Add(g_pd3dDevice, L"../../data/Map512Color.png");
		map.m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTexture);

		cbData.vDirectionLight = D3DXVECTOR4(1, 1, 1, 1);
		cbData.vDirectionColor = D3DXVECTOR4(1, 0, 0, 1);
		return true;
	}
	bool Frame()
	{

		return true;
	}
	bool Render()
	{
		map.m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);

		GetContext()->UpdateSubresource(map.m_dxObj.m_pConstantBuffer, 0, NULL, &map.m_cbData, 0, 0);
		GetContext()->VSSetConstantBuffers(1, 1, &pConstantBuffer);
		GetContext()->UpdateSubresource(pConstantBuffer, 0, NULL, &cbData, 0, 0);
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