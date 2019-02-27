#include "JModel.h"
#include "JState.h"
namespace UI
{
	bool JModel::PreRender(ID3D11DeviceContext* context)
	{
		UINT stride = m_iVertexSize;
		UINT offset = 0;
		context->PSSetSamplers(0, 1, &JState::g_pTexSS);
		context->IASetInputLayout(m_pIL);
		context->VSSetShader(m_pVS, NULL, 0);
		context->PSSetShader(m_pPS, NULL, 0);
		context->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
		context->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		context->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		context->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		return true;
	}	
	bool JModel::Render(ID3D11DeviceContext* context)
	{
		PreRender(context);
		PostRender(context);
		return true;
	}
	bool JModel::PostRender(ID3D11DeviceContext* context)
	{
		context->DrawIndexed(m_iIndexNum, 0, 0);
		return true;
	}

	bool JModel::Release()
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
	JModel::JModel()
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
	JModel::~JModel()
	{

	}
}