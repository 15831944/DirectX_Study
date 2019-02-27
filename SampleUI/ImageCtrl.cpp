#include "stdafx.h"
#include "ImageCtrl.h"
bool ImageCtrl::Create()
{
	/* »ý¼º */
	m_pVertices.resize(4);
	m_pVertices =
	{
		{ D3DXVECTOR3(-1.0f, 1.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3(1.0f, 1.0f, 0.0f),   D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR3(1.0f, -1.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR3(-1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f) },
	};
	m_dxObj.m_iVertexNum = m_pVertices.size();
	m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);

	m_pIndices =
	{
		0,1,2,	0,2,3,
	};
	m_dxObj.m_iIndexNum = m_pIndices.size();
	m_dxObj.m_iIndexSize = sizeof(DWORD);

	int iTex = I_TexMgr.Add(g_pd3dDevice, L"NO_IMAGE.png");
	if (iTex < 0)
	{
		AfxMessageBox(L"Texture Loading Failed :: NO_IMAGE.png ");
	}
	m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTex);

	m_dxObj.m_pVertexBuffer = CreateVertexBuffer(g_pd3dDevice, &m_pVertices.at(0), m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
	m_dxObj.m_pIndexBuffer = CreateIndexBuffer(g_pd3dDevice, &m_pIndices.at(0), m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum);
	m_dxObj.m_pConstantBuffer = CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1);
	m_dxObj.m_pVS = LoadVertexShader(g_pd3dDevice, L"../../data/shader/shape.vsh", &m_dxObj.m_BlobVS);
	m_dxObj.m_pPS = LoadPixelShader(g_pd3dDevice, L"../../data/shader/shape.psh", &m_dxObj.m_BlobPS);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	int ElementCnt = sizeof(ied) / sizeof(ied[0]);
	m_dxObj.m_pIL = CreateLayout(g_pd3dDevice, ied, ElementCnt, m_dxObj.m_BlobVS);
	return true;
}
bool ImageCtrl::Render(ID3D11DeviceContext* context, UINT iVertexSize, UINT iCount)
{
	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);

	context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
	PreRender(context, iVertexSize);
	PostRender(context, iCount);
	return true;
}

ImageCtrl::ImageCtrl()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	D3DXMatrixIdentity(&m_matTrans);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRotate);
	m_iIndex = 0;
	m_fAngle = 0;
	m_vLook = { 0.0f, 0.0f, 0.0f };
	m_vUp = { 0.0f, 0.0f, 0.0f };
	m_vRight = { 0.0f, 0.0f, 0.0f };
	m_vPos = { 0.0f, 0.0f, 0.0f };
	m_rtPos = { 0.0f, 0.0f, 0.0f, 0.0f };
	Init();
}


ImageCtrl::~ImageCtrl()
{
}
