#include "Plane.h"

bool Plane::Init()
{
	PNCT_VERTEX vertices[] =
	{
		{ D3DXVECTOR3(-1.0f, 1.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
	{ D3DXVECTOR3(1.0f, 1.0f, 0.0f),   D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
	{ D3DXVECTOR3(1.0f, -1.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
	{ D3DXVECTOR3(-1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
	};
	for (int iVer = 0; iVer < sizeof(vertices) / sizeof(vertices[0]); iVer++)
	{
		m_pVertices.push_back(vertices[iVer]);
	}
	m_dxObj.m_iVertexNum = sizeof(vertices) / sizeof(vertices[0]);
	m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);

	DWORD indices[] =
	{
		0,1,2,	0,2,3,
	};
	m_dxObj.m_iIndexNum = sizeof(indices) / sizeof(indices[0]);
	m_dxObj.m_iIndexSize = sizeof(DWORD);

	m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, vertices, m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
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
	return true;
}
bool Plane::Frame()
{
	return true;
}
bool Plane::PreRender(ID3D11DeviceContext* context, UINT iVertexSize)
{
	UINT stride = iVertexSize;
	UINT offset = 0;
	if (iVertexSize == 0) stride = m_dxObj.m_iVertexSize;
	context->PSSetSamplers(0, 1, &JState::g_pTexSS);
	context->IASetInputLayout(m_dxObj.m_pIL);
	context->VSSetShader(m_dxObj.m_pVS, NULL, 0);
	context->PSSetShader(m_dxObj.m_pPS, NULL, 0);
	//context->GSSetShader(m_pGS, NULL, 0);
	context->IASetVertexBuffers(0, 1, &m_dxObj.m_pVertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(m_dxObj.m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	context->VSSetConstantBuffers(0, 1, &m_dxObj.m_pConstantBuffer);
	context->PSSetShaderResources(0, 1, &m_pSRV);
	return true;
}
bool Plane::PostRender(ID3D11DeviceContext* context, UINT iCount)
{
	if (iCount == 0) iCount = m_dxObj.m_iIndexNum;
	if (iCount != 0)
		context->DrawIndexed(iCount, 0, 0);
	else
		context->Draw(m_dxObj.m_iVertexNum, 0);
	return true;
}
bool Plane::Render(ID3D11DeviceContext* context, UINT iVertexSize, UINT iCount)
{
	context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
	PreRender(context, iVertexSize);
	PostRender(context, iCount);
	return true;
}
Plane::Plane()
{
}


Plane::~Plane()
{
}
