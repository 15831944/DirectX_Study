#include "PlaneShape.h"
bool PlaneShape::Create(ID3D11Device* pDevice, const char* szPSFunName, const char* szVSFunName, const TCHAR* szShaderName)
{
	m_pVertices.resize(4);
	m_pVertices[0] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f),  D3DXVECTOR4(0.3f, 0.4f, 0.5f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_pVertices[1] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f),   D3DXVECTOR4(0.3f, 0.4f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_pVertices[2] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f),  D3DXVECTOR4(0.3f, 0.4f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_pVertices[3] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.3f, 0.4f, 0.5f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	m_iVertexNum = m_pVertices.size();
	m_iVertexSize = sizeof(PNCT_VERTEX);

	m_pIndices.resize(6);
	m_pIndices[0] = 0; m_pIndices[1] = 1; m_pIndices[2] = 2; 
	m_pIndices[3] = 0; m_pIndices[4] = 2; m_pIndices[5] = 3;
	m_iIndexNum = m_pIndices.size();
	m_iIndexSize = sizeof(DWORD);

	m_pVertexBuffer = DX::CreateVertexBuffer(pDevice, &m_pVertices.at(0), m_iVertexSize, m_iVertexNum);
	m_pIndexBuffer = DX::CreateIndexBuffer(pDevice, &m_pIndices.at(0), m_iIndexSize, m_iIndexNum);
	m_pConstantBuffer = CreateConstantBuffer(pDevice, &m_cbData, sizeof(VSCB), 1);
	m_pVS = DX::LoadVertexShader(pDevice, szShaderName, &m_BlobVS, szVSFunName);
	m_pPS = DX::LoadPixelShader(pDevice, szShaderName, &m_BlobPS, szPSFunName);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	int ElementCnt = sizeof(ied) / sizeof(ied[0]);
	m_pIL = DX::CreateLayout(pDevice, ied, ElementCnt, m_BlobVS);
	D3DXMatrixIdentity(&m_matWorld);
	return true;
}
PlaneShape::PlaneShape()
{

}
PlaneShape::~PlaneShape()
{

}