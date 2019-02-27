#include "JCore.h"
#include "JMap.h"
#include "Quad.h"
class Sample : public JCore
{
public:
	JTexture* pNormal;
	JMap map;
	Quad quad;
	D3DXMATRIX m_matWorld, m_matInitWorld;
	D3DXVECTOR3 m_vInitLightPos;
	D3DXMATRIX m_mLightWorld;
	JPlaneShape plane;
	DxRT rt;
public:
	bool Init()
	{
		rt.Create(GetDevice());
		map.Init();
		map.SetHeightTexture(GetContext(), L"../../Data/heightMap513.bmp");
		map.Create(GetDevice(), 513,513, 1.0f);
		map.m_dxObj.m_pTexture = I_TexMgr.GetPtr(I_TexMgr.Add(GetDevice(), L"../../Data/HR.BMP"));
		pNormal = I_TexMgr.GetPtr(I_TexMgr.Add(GetDevice(), L"../../Data/HR_N.bmp"));
		quad.Create("PS", "VS", L"quad.hlsl");
		quad.CreateTextures(GetDevice(), 800, 600);
		quad.SetBuffer(GetDevice());
		quad.ComputeKernel(3);
		plane.Init();
		return true;
	}
	bool Frame()
	{
		quad.Frame();
		return true;
	}
	bool Render()
	{
		GetContext()->PSSetSamplers(0, 1, &JState::g_pClampLinear);
		//GetContext()->OMSetDepthStencilState(JState::g_pEnableDSS, 0x00);
		//GetContext()->RSSetState(JState::g_pRSNoneCullSolid);

		//if(rt.Begin(GetContext(), D3DXVECTOR4(1, 1, 1, 1)))
		//{
		//map.m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
		//map.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		//map.Render(GetContext());

		//rt.End(GetContext());
		//}
		//GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		RenderIntoBuffer(GetContext());
		//quad.m_pColorSRV = rt.m_pRTV_SRV;
		//quad.m_pNormalDepthSRV = rt.m_pDSV_SRV;
		quad.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		quad.Render(GetContext());
		//quad.PreRender(GetContext());
		//GetContext()->UpdateSubresource(quad.m_dxObj.m_pConstantBuffer, 0, NULL, &quad.m_cbData, 0, 0);
		//quad.PostRender(GetContext());

		//D3DXMATRIX a;
		//
		//D3DXMatrixTranslation(&a, 10, 20, 0);
		//plane.SetMatrix(&a, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		//GetContext()->PSSetShaderResources(0, 1, &rt.m_pRTV_SRV);
		//plane.Render(GetContext());
		return true;
	}
	bool Release()
	{
		return true;
	}

	void RenderIntoBuffer(ID3D11DeviceContext*    pContext)
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
		pContext->OMSetRenderTargets(1, pViews, pOldDSV);
		SAFE_RELEASE(pOldRTV);
		SAFE_RELEASE(pOldDSV);
	}
	void RenderMRT(ID3D11DeviceContext*    pContext)
	{
		map.m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
		map.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
		map.PreRender(pContext);
		map.PostRender(pContext);

		//map.PreRender(GetContext());

		/*ID3D11Buffer* Buffer[2] = { map.m_dxObj.m_pVertexBuffer, NULL };
		UINT stride[2] = { sizeof(PNCT_VERTEX), sizeof(D3DXVECTOR3) };
		UINT offset[2] = { 0, 0 };
		pContext->IASetVertexBuffers(0, 2, Buffer, stride, offset);

		pContext->PSSetShaderResources(1, 1, &map.m_pNormalTexture->m_pTextureRV);
		pContext->VSSetConstantBuffers(1, 1, &m_pConstantBuffer);
		pContext->VSSetConstantBuffers(2, 1, &m_pCBNeverChanges);
		pContext->PSSetConstantBuffers(1, 1, &m_pConstantBuffer);
		pContext->PSSetConstantBuffers(2, 1, &m_pCBNeverChanges);
*/
		//map.PostRender(pContext);
	}
};
RUN;