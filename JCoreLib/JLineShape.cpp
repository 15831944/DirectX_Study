#include "JLineShape.h"
//=======================================================================================
//======================================LineShape========================================
//=======================================================================================
bool JLineShape::Init()
{
	PC_VERTEX vertices[] =
	{
		{ D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f) },
	};

	m_dxObj.m_iVertexNum = sizeof(vertices) / sizeof(vertices[0]);
	m_dxObj.m_iVertexSize = sizeof(PC_VERTEX);

	DWORD indices[] =
	{
		0,1,
	};
	m_dxObj.m_iIndexNum = sizeof(indices) / sizeof(indices[0]);
	m_dxObj.m_iIndexSize = sizeof(DWORD);

	m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, vertices, m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
	m_dxObj.m_pIndexBuffer = CreateIndexBuffer(g_pd3dDevice, indices, m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum);
	m_dxObj.m_pConstantBuffer = CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1);
	m_dxObj.m_pVS = DX::LoadVertexShader(g_pd3dDevice, L"../../data/shader/Default.hlsl", &m_dxObj.m_BlobVS, "VSLine");
	m_dxObj.m_pPS = DX::LoadPixelShader(g_pd3dDevice,  L"../../data/shader/Default.hlsl", &m_dxObj.m_BlobPS, "PSLine");

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	int ElementCnt = sizeof(ied) / sizeof(ied[0]);
	m_dxObj.m_pIL = DX::CreateLayout(g_pd3dDevice, ied, ElementCnt, m_dxObj.m_BlobVS);
	D3DXMatrixIdentity(&m_matWorld);
	return true;
}
bool JLineShape::Frame()
{
	return true;
}
bool JLineShape::Render(ID3D11DeviceContext* context)
{
	context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
	context->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)m_iPrimitiveType);
	m_dxObj.Render(context);
	return true;
}
void JLineShape::Draw(ID3D11DeviceContext* context, D3DXVECTOR3 vPos, D3DXVECTOR3 vEnd, D3DXVECTOR4 vColor)
{
	PC_VERTEX vertex[2];
	vertex[0].p = vPos;
	vertex[1].p = vEnd;
	vertex[0].c = vColor;
	vertex[1].c = vColor;
	context->UpdateSubresource(m_dxObj.m_pVertexBuffer, 0, NULL, &vertex, 0, 0);
	Render(context);
}
JLineShape::JLineShape()
{
	m_iPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
}
JLineShape::~JLineShape()
{

}