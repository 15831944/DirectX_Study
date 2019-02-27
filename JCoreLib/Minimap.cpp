#include "Minimap.h"
#include "JDxInput.h"
bool Minimap::BeginRender(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget, bool bDepth, bool bStencil)
{
	m_RT.Begin(context, vColor, bTarget, bDepth, bStencil);
	return true;
}
bool Minimap::EndRender(ID3D11DeviceContext* context)
{
	m_RT.End(context);
	return true;
}
bool Minimap::Create(ID3D11Device* device, FLOAT fTopX, FLOAT fTopY, FLOAT fWidth, FLOAT fHeight, FLOAT fRTWidth, FLOAT fRTHeight,
	const char* szPSFunName, const char* szVSFunName, const TCHAR* szShaderName)
{
	m_Screen.Create(szPSFunName, szVSFunName, szShaderName);
	m_Minimap.Create(szPSFunName, szVSFunName, szShaderName);

	m_RT.Create(device, fRTWidth, fRTHeight);

	m_MinimapViewPort.TopLeftX = fTopX;
	m_MinimapViewPort.TopLeftY = fTopY;
	m_MinimapViewPort.Width = fWidth;
	m_MinimapViewPort.Height = fHeight;
	m_MinimapViewPort.MinDepth = 0;
	m_MinimapViewPort.MaxDepth = 1;

	//D3DXVECTOR3 vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 100.0f, -1.0f);

	//SetViewMatrix(vPos, vTarget, vUp);
	//SetProjMatrix(D3DX_PI * 0.25f, (float)fWidth / (float)fHeight, 0.1f, 10000.0f);
	return true;
}
bool Minimap::ScreenRender(ID3D11DeviceContext* context)
{
	m_Screen.m_pSRV = m_RT.m_pRTV_SRV;
	m_Screen.SetMatrix(NULL, NULL, NULL);
	m_Screen.PreRender(context);
	context->UpdateSubresource(m_Screen.m_dxObj.m_pConstantBuffer, 0, NULL, &m_Screen.m_cbData, 0, 0);
	context->PSSetShaderResources(0, 1, &m_Screen.m_pSRV);
	m_Screen.PostRender(context);

	context->RSSetViewports(1, &m_MinimapViewPort);
	return true;
}
bool Minimap::Render(ID3D11DeviceContext* context, ID3D11ShaderResourceView* pSRV)
{
	//m_Screen.m_pSRV = m_RT.m_pRTV_SRV;
	//m_Screen.SetMatrix(NULL, NULL, NULL);
	//m_Screen.Render(context);

	context->RSSetViewports(1, &m_MinimapViewPort);

	m_Minimap.ChangedPixelShader("PSTexture");
	/* RTV_SRV or DSV_SRV »ç¿ë */
	if(pSRV == NULL)
		m_Minimap.m_pSRV = m_RT.m_pRTV_SRV;
	else
		m_Minimap.m_pSRV = pSRV;
	/* ======================= */
	m_Minimap.SetMatrix(NULL, NULL, NULL);
	m_Minimap.PreRender(context);
	context->UpdateSubresource(m_Minimap.m_dxObj.m_pConstantBuffer, 0, NULL, &m_Minimap.m_cbData, 0, 0);
	context->PSSetShaderResources(0, 1, &m_Minimap.m_pSRV);
	m_Minimap.PostRender(context);
	return true;
}
Minimap::Minimap()
{
}


Minimap::~Minimap()
{
}
