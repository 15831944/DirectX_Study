#include "JMesh.h"
bool AseMesh::Create(ID3D11Device* device)
{
	//Vertex
	m_dxObj.m_iVertexNum = m_pVertexList.size();
	m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);

	//Index
	m_dxObj.m_iIndexNum = m_pIndexList.size();
	m_dxObj.m_iIndexSize = sizeof(DWORD);

	m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, &m_pVertexList.at(0), m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
	m_dxObj.m_pIndexBuffer = DX::CreateIndexBuffer(g_pd3dDevice, &m_pIndexList.at(0), m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum);

	m_dxObj.m_pConstantBuffer = DX::CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1);
	m_dxObj.m_pVS = DX::LoadVertexShader(g_pd3dDevice, L"../../data/shader/shape.vsh", &m_dxObj.m_BlobVS);
	m_dxObj.m_pPS = DX::LoadPixelShader(g_pd3dDevice, L"../../data/shader/shape.psh", &m_dxObj.m_BlobPS);

	//tex
	LoadTexFile(device, m_pTexName);

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
bool AseMesh::LoadTexFile(ID3D11Device* device, string szTexName)
{
	TCHAR Ret[256] = { 0, };
	wstring strTemp = mtow(szTexName);
	wsprintf(Ret, _T("%s"), strTemp.data());

	int iTex = I_TexMgr.Add(device, Ret);
	m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTex);
	return true;
}
bool AseMesh::Render(ID3D11DeviceContext* context)
{
	context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
	m_dxObj.Render(context);
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool JMesh::Draw(ID3D11DeviceContext* context, D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
{
	for (int iSubMesh = 0; iSubMesh < m_pSubMeshList.size(); iSubMesh++)
	{
		if (m_pSubMeshList[iSubMesh].m_pTriangleList.size() <= 0) continue;
		D3DXMATRIX mat = (m_matLocalScale * m_matLocalRotate * m_matLocalTrans) 
						* (m_pParent->m_matLocalScale * m_pParent->m_matLocalRotate * m_pParent->m_matLocalTrans);
		//m_matCalc = m_matLocalScale * m_matLocalRotate * m_matLocalTrans;
		m_pSubMeshList[iSubMesh].SetMatrix(&m_matCalc, matView, matProj);
		m_pSubMeshList[iSubMesh].Render(context);
	}
	return true;
}
bool JMesh::Frame()
{
	return true;
}
bool JMesh::Render(ID3D11DeviceContext* context)
{
	return true;
}
AseMesh::AseMesh()
{
}


AseMesh::~AseMesh()
{
}
