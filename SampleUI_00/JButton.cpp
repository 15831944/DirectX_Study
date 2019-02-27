#include "JButton.h"
void JButton::Create(fRECT rt, float u0, float v0, float u1, float v1)
{
	m_pVertices.resize(2);
	m_pVertices[0] =
	{
		// left top
		{ D3DXVECTOR3(rt.left, rt.top, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
		// right top
		{ D3DXVECTOR3(rt.right * u0, rt.top, 0.0f),   D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(u0, 0.0f) },
		// right bottom
		{ D3DXVECTOR3(rt.right * u0, rt.bottom * v0, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(u0, v0) },
		// left bottom
		{ D3DXVECTOR3(rt.left, rt.bottom * v0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(0.0f, v0) },
	};
	m_pVertices[1] =
	{
		// left top
		{ m_pVertices[0][1].p + D3DXVECTOR3(rt.left, rt.top, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), m_pVertices[0][1].t + D3DXVECTOR2(0.0f, 0.0f) },
		// right top
		{ m_pVertices[0][1].p + D3DXVECTOR3(rt.right * u1, rt.top, 0.0f),   D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f),  m_pVertices[0][1].t + D3DXVECTOR2(u1, 0.0f) },
		// right bottom
		{ D3DXVECTOR3(m_pVertices[0][2].p.x + rt.right * u1, rt.bottom * v0, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), m_pVertices[0][2].t + D3DXVECTOR2(u1, v0) },
		// left bottom
		{ m_pVertices[0][2].p + D3DXVECTOR3(rt.left, rt.bottom * v0, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), m_pVertices[0][2].t + D3DXVECTOR2(0.0f, v0) },
	};
	for (int iPlane = 0; iPlane < m_pVertices.size(); iPlane++)
	{
		for (int iVer = 0; iVer < m_pVertices[iPlane].size(); iVer++)
		{
			m_pRenderVertices.push_back(m_pVertices[iPlane][iVer]);
		}
	}
	m_dxObj.m_iVertexNum = m_pRenderVertices.size();
	m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);

	DWORD indices[] =
	{
		0,1,2,	0,2,3,
		4,5,6,  4,6,7,
	};
	m_dxObj.m_iIndexNum = sizeof(indices) / sizeof(indices[0]);
	m_dxObj.m_iIndexSize = sizeof(DWORD);

	m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, &m_pRenderVertices.at(0), m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
	m_dxObj.m_pIndexBuffer = CreateIndexBuffer(g_pd3dDevice, indices, m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum);
	m_dxObj.m_pConstantBuffer = CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1);
	m_dxObj.m_pVS = DX::LoadVertexShader(g_pd3dDevice, L"../../data/shader/shape.vsh", &m_dxObj.m_BlobVS);
	m_dxObj.m_pPS = DX::LoadPixelShader(g_pd3dDevice, L"../../data/shader/shape.psh", &m_dxObj.m_BlobPS);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	int ElementCnt = sizeof(ied) / sizeof(ied[0]);
	m_dxObj.m_pIL = DX::CreateLayout(g_pd3dDevice, ied, ElementCnt, m_dxObj.m_BlobVS);
	D3DXMatrixIdentity(&m_matWorld);
}
bool JButton::Init()
{
	return true;
}
bool JButton::Frame()
{
	return true;
}
bool JButton::PreRender(ID3D11DeviceContext* context, UINT iVertexSize)
{
	UINT stride = iVertexSize;
	UINT offset = 0;
	if (iVertexSize == 0) stride = m_dxObj.m_iVertexSize;
	context->PSSetSamplers(0, 1, &JState::g_pTexSS);
	context->IASetInputLayout(m_dxObj.m_pIL);
	context->VSSetShader(m_dxObj.m_pVS, NULL, 0);
	context->PSSetShader(m_dxObj.m_pPS, NULL, 0);
	context->IASetVertexBuffers(0, 1, &m_dxObj.m_pVertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(m_dxObj.m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->VSSetConstantBuffers(0, 1, &m_dxObj.m_pConstantBuffer);
	context->PSSetShaderResources(0, 1, &m_dxObj.m_pTexture->m_pSRV);
	return true;
}
bool JButton::PostRender(ID3D11DeviceContext* context, UINT iCount)
{
	if (iCount == 0) iCount = m_dxObj.m_iIndexNum;
	if (iCount != 0)
		context->DrawIndexed(iCount, 0, 0);
	else
		context->Draw(m_dxObj.m_iVertexNum, 0);
	return true;
}
bool JButton::Render(ID3D11DeviceContext* context, UINT iVertexSize, UINT iCount)
{
	context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
	PreRender(context, iVertexSize);
	PostRender(context, iCount);
	return true;
}
bool JButton::Release()
{
	return true;
}

JButton::JButton()
{
}


JButton::~JButton()
{
}
