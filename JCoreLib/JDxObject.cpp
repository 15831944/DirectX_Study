#include "JDxObject.h"
#include "JState.h"
bool JDxObject::PreRender(ID3D11DeviceContext* context, UINT iVertexSize)
{
	UINT stride = iVertexSize;
	UINT offset = 0;
	if (iVertexSize == 0) stride = m_iVertexSize;
	context->PSSetSamplers(0, 1, &JState::g_pTexSS);
	context->IASetInputLayout(m_pIL);
	context->VSSetShader(m_pVS, NULL, 0);
	context->PSSetShader(m_pPS, NULL, 0);
	context->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	context->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	//context->GSSetShader(g_pGS.Get(), NULL, 0);
	//context->HSSetShader(g_pHS.Get(), NULL, 0);
	//context->DSSetShader(g_pDS.Get(), NULL, 0);
	//context->PSSetShaderResources(0, 1, g_pTextureSRV.GetAddressOf());
	if (m_pTexture != NULL && m_pTexture->m_pSRV != NULL)
	{
		context->PSSetShaderResources(0, 1, &m_pTexture->m_pSRV);
	}
	return true;
}
bool JDxObject::PostRender(ID3D11DeviceContext* context, UINT iCount)
{
	if (iCount == 0) iCount = m_iIndexNum;
	if (iCount != 0)
		context->DrawIndexed(iCount, 0, 0);
	else
		context->Draw(m_iVertexNum, 0);
	return true;
}
bool JDxObject::Render(ID3D11DeviceContext* context, UINT iVertexSize, UINT iCount)
{
	PreRender(context, iVertexSize);
	PostRender(context, iCount);
	return true;
}
bool JDxObject::Release()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVS);
	SAFE_RELEASE(m_pPS);
	SAFE_RELEASE(m_pIL);
	SAFE_RELEASE(m_BlobVS);
	SAFE_RELEASE(m_BlobPS);
	return true;
}
JDxObject::JDxObject()
{
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;
	m_pConstantBuffer = NULL;
	m_pVS = NULL;
	m_pPS = NULL;
	m_pIL = NULL;
	m_BlobVS = NULL;
	m_BlobPS = NULL;
	m_iVertexNum = 0;
	m_iIndexNum = 0;
	m_iVertexSize = 0;
	m_iIndexSize = 0;
}
JDxObject::~JDxObject()
{

}