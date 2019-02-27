#include "JCore.h"
#include "Quad.h"
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

	JMap map;
	Quad quad;
public :
	bool Init()
	{
		pBuffer = DX::CreateConstantBuffer(GetDevice(), &cbLight, sizeof(LIGHT_CONSTANT_DATA), 1);
		cbLight.vDirectionLight = D3DXVECTOR4(1000, 1000, 1000, 1);
		cbLight.vAmbientLight = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
		cbLight.vDiffuseLight = D3DXVECTOR4(1, 1, 1, 1);
		cbLight.vDiffusenColor = D3DXVECTOR4(1, 1, 1, 1);
		cbLight.vAmbientColor = D3DXVECTOR4(1, 1, 1, 1);


		map.SetHeightTexture(GetContext(), L"../../Data/Map512.png");
		map.Create(GetDevice(), 512, 512, 1, L"Map.hlsl", "VS", "PS");// "VS_NORMAL_MAP", "PS_NORMAL_MAP");
		map.SetTexture(L"../../Data/Map512Color.png");
		pNormal = I_TexMgr.GetPtr(I_TexMgr.Add(GetDevice(), L"../../Dasta/test_normal_map.bmp"));

		quad.Create("PS", "VS", L"PostEffect.hlsl");
		quad.CreateTextures(GetDevice(), m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height);
		quad.SetBuffer(GetDevice());
		quad.ComputeKernel(3);
		return true;
	}
	bool Frame()
	{
		return true;
	}
	bool Render()
	{
		//GetContext()->OMSetBlendState(JState::g_pNoAlphaBlend, 0, -1);
		GetContext()->OMSetDepthStencilState(JState::g_pEnableDSS, 0x00);
		GetContext()->PSSetSamplers(1, 1, &JState::g_pClampLinear);
		RenderIntoBuffer(GetContext());


		quad.SetMatrix(NULL, GetView(),GetProj());
		quad.Render(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}
	void RenderIntoBuffer(ID3D11DeviceContext*    pContext);
	void RenderMRT(ID3D11DeviceContext*    pContext);
};
RUN;
void Sample::RenderIntoBuffer(ID3D11DeviceContext*    pContext)
{
	// Clear the new render target
	float color[4] =
	{
		0, 0, 0, 0
	};
	pContext->ClearRenderTargetView(quad.m_pColorRTV, color);
	pContext->ClearRenderTargetView(quad.m_pNormalDepthRTV, color);


	// get the old render targets
	ID3D11RenderTargetView* pOldRTV;
	ID3D11DepthStencilView* pOldDSV;
	pContext->OMGetRenderTargets(1, &pOldRTV, &pOldDSV);

	pContext->ClearDepthStencilView(pOldDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);


	// Set the new render targets
	ID3D11RenderTargetView* pViews[2];
	pViews[0] = quad.m_pColorRTV;
	pViews[1] = quad.m_pNormalDepthRTV;
	pContext->OMSetRenderTargets(2, pViews, pOldDSV);

	// Render the particles
	RenderMRT(pContext);

	// restore the original render targets
	pViews[0] = pOldRTV;
	pViews[1] = NULL;
	pContext->OMSetRenderTargets(2, pViews, pOldDSV);
	SAFE_RELEASE(pOldRTV);
	SAFE_RELEASE(pOldDSV);
}
void Sample::RenderMRT(ID3D11DeviceContext*    pContext)
{
	map.SetMatrix(NULL, GetView(), GetProj());
	map.PreRender(GetContext());

	GetContext()->PSSetConstantBuffers(1, 1, &pBuffer);
	GetContext()->VSSetConstantBuffers(1, 1, &pBuffer);
	GetContext()->UpdateSubresource(pBuffer, 0, NULL, &cbLight, 0, 0);

	GetContext()->PSSetShaderResources(1, 1, &pNormal->m_pSRV);

	map.PostRender(GetContext());

	//ClearD3D11DeviceContext(pContext);
}