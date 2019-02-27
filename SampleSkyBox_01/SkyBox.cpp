#include "SkyBox.h"
bool SkyBox::Create(ID3D11Device* device, const TCHAR* szSkyName[])
{
	for (int iSky = 0; iSky < 6; iSky++)
	{
		int iTex = I_TexMgr.Add(device, szSkyName[iSky]);
		m_Tex[iSky] = I_TexMgr.GetPtr(iTex);
	}
	D3DXMatrixScaling(&m_matWorld, 100.0f, 100.0f, 100.0f);
	return true;
}
bool SkyBox::Frame()
{
	return true;
}
bool SkyBox::Render(ID3D11DeviceContext* context)
{
	m_matSkyView = m_matView;
	m_matSkyView._41 = 0.0f;
	m_matSkyView._42 = 0.0f;
	m_matSkyView._43 = 0.0f;

	SetMatrix(&m_matWorld, &m_matSkyView, &m_matProj);

	context->OMSetDepthStencilState(JState::g_pDisableDSS, 0x00);
	context->OMSetBlendState(JState::g_pAlphaBlend, 0, -1);

	context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
	m_dxObj.PreRender(context, sizeof(PNCT_VERTEX));

	for (int iIndex = 0; iIndex < 6; iIndex++)
	{
		context->PSSetShaderResources(0, 1, &m_Tex[iIndex]->m_pSRV);
		context->DrawIndexed(6, iIndex * 6, 0);
	}
	context->OMSetDepthStencilState(JState::g_pEnableDSS, 0x00);
	return true;
}
bool SkyBox::Release()
{
	for (int iTex = 0; iTex < 6; iTex++)
	{
		SAFE_RELEASE(m_Tex[iTex]);
	}
	m_dxObj.Release();
	return true;
}

SkyBox::SkyBox()
{
	
}
SkyBox::~SkyBox()
{

}