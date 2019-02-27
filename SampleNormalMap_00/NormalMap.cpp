#include "NormalMap.h"
bool NormalMap::Create(ID3D11Device* device, int iWidth, int iHeight, int iCellSize)
{
	m_iNumCols = iWidth;
	m_iNumRows = iHeight;
	VerticeSize = iWidth * iHeight;
	m_fCellSize = iCellSize;
	m_iFaceCnt = (iWidth - 1) * (iHeight - 1) * 2;
	m_iCellCols = iWidth - 1;
	m_iCellRows = iHeight - 1;


	float fHalfRow = ((iWidth - 1) * m_fCellSize) / 2.0f;
	float fHalfCol = ((iHeight - 1) * m_fCellSize) / 2.0f;
	float fOffsetX = 1.0f / (iWidth - 1);
	float fOffsetZ = 1.0f / (iHeight - 1);

	m_pVertices.resize(VerticeSize);

	for (int iCol = 0; iCol < iHeight; iCol++)
	{
		for (int iRow = 0; iRow < iWidth; iRow++)
		{
			int iIndex = (iCol * iWidth) + iRow;

			float fHeight = 0.0f;
			if (m_fHeightMap != NULL)
			{
				fHeight = m_fHeightMap[iCol * iWidth + iRow];// *0.1f;
			}
			m_pVertices[iIndex].p = D3DXVECTOR3((iRow * iCellSize) - fHalfRow, fHeight, -iCol * iCellSize + fHalfCol);
			m_pVertices[iIndex].n = GetNormalOfVertex(iIndex); // 0,1,0
			m_pVertices[iIndex].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			m_pVertices[iIndex].t = D3DXVECTOR2(fOffsetX*iRow, fOffsetZ*iCol);
		}
	}

	m_dxObj.m_iVertexNum = m_pVertices.size();
	m_dxObj.m_iVertexSize = sizeof(PNCT_VERTEX);

	int iIndexCnt = m_iFaceCnt * 3;
	m_pIndices.resize(iIndexCnt);

	int iCount = 0;
	for (int iCol = 0; iCol < iHeight - 1; iCol++)
	{
		for (int iRow = 0; iRow < iWidth - 1; iRow++)
		{
			m_pIndices[iCount++] = (iCol*iWidth) + iRow;
			m_pIndices[iCount++] = (iCol*iWidth) + iRow + 1;
			m_pIndices[iCount++] = ((iCol + 1) * iWidth) + iRow;

			m_pIndices[iCount++] = ((iCol + 1) * iWidth) + iRow;
			m_pIndices[iCount++] = (iCol*iWidth) + iRow + 1;
			m_pIndices[iCount++] = ((iCol + 1) * iWidth) + iRow + 1;
		}
	}
	m_dxObj.m_iIndexNum = m_pIndices.size();
	m_dxObj.m_iIndexSize = sizeof(DWORD);

	/* Normal Create */
	CreateNormalVertex();

	m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, &m_pVertices.at(0), m_dxObj.m_iVertexSize, m_dxObj.m_iVertexNum);
	m_dxObj.m_pIndexBuffer = CreateIndexBuffer(g_pd3dDevice, &m_pIndices.at(0), m_dxObj.m_iIndexSize, m_dxObj.m_iIndexNum);
	m_dxObj.m_pConstantBuffer = CreateConstantBuffer(g_pd3dDevice, &m_cbData, sizeof(VSCB), 1);
	m_dxObj.m_pVS = DX::LoadVertexShader(g_pd3dDevice, L"map.hlsl", &m_dxObj.m_BlobVS);
	m_dxObj.m_pPS = DX::LoadPixelShader(g_pd3dDevice, L"map.hlsl", &m_dxObj.m_BlobPS);

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
void CreateTangentSpaceVectors(D3DXVECTOR3 *v0,
	D3DXVECTOR3 *v1, D3DXVECTOR3 *v2, D3DXVECTOR2 uv0,
	D3DXVECTOR2 uv1, D3DXVECTOR2 uv2,
	D3DXVECTOR3 *vTangent, D3DXVECTOR3 *vBiNormal, D3DXVECTOR3 *vNormal)
{
	D3DXVECTOR3 vEdge1 = *v1 - *v0;
	D3DXVECTOR3 vEdge2 = *v2 - *v0;
	D3DXVec3Normalize(&vEdge1, &vEdge1);
	D3DXVec3Normalize(&vEdge2, &vEdge2);
	// UV delta
	D3DXVECTOR2 deltaUV1 = uv1 - uv0;
	D3DXVECTOR2 deltaUV2 = uv2 - uv0;
	D3DXVec2Normalize(&deltaUV1, &deltaUV1);
	D3DXVec2Normalize(&deltaUV2, &deltaUV2);


	D3DXVECTOR3 biNormal;
	float fDet = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
	if (fabsf(fDet) < 1e-6f)
	{
		*vTangent = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		biNormal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}
	else
	{
		*vTangent = (vEdge1 * deltaUV2.y - vEdge2 * deltaUV1.y)*fDet;
		biNormal = (vEdge2 * deltaUV1.x - vEdge1 * deltaUV2.x)*fDet;
	}
	D3DXVec3Normalize(vTangent, vTangent);
	D3DXVec3Normalize(&biNormal, &biNormal);

	D3DXVec3Cross(vBiNormal, vNormal, vTangent);
	float crossinv = (D3DXVec3Dot(vBiNormal, &biNormal) < 0.0f) ? -1.0f : 1.0f;
	*vBiNormal *= crossinv;
}

bool NormalMap::Render(ID3D11DeviceContext* context)
{
	PreRender(context);
	PostRender(context);
	return true;
}
bool NormalMap::UpdateBuffer()
{
	//--------------------------------------------------------------------------------------
	// 접선벡터 계산
	//--------------------------------------------------------------------------------------	
	D3DXVECTOR3 vTangent, vBiNormal, vNormal;
	int iIndex = 0;
	int i0, i1, i2, i3, i4, i5;

	m_vTangentList.resize(m_dxObj.m_iVertexNum);

	for (int iIndex = 0; iIndex < m_dxObj.m_iIndexNum; iIndex += 3)
	{
		
		i0 = m_pIndices[iIndex + 0];
		i1 = m_pIndices[iIndex + 1];
		i2 = m_pIndices[iIndex + 2];

		CreateTangentSpaceVectors(&m_pVertices[i0].p, &m_pVertices[i1].p, &m_pVertices[i2].p,
			m_pVertices[i0].t, m_pVertices[i1].t, m_pVertices[i2].t,
			&vTangent, &vBiNormal, &m_pVertices[i0].n);

		m_vTangentList[i0] += vTangent;

		i0 = m_pIndices[iIndex + 1];
		i1 = m_pIndices[iIndex + 2];
		i2 = m_pIndices[iIndex + 0];

		CreateTangentSpaceVectors(&m_pVertices[i0].p, &m_pVertices[i1].p, &m_pVertices[i2].p,
			m_pVertices[i0].t, m_pVertices[i1].t, m_pVertices[i2].t,
			&vTangent, &vBiNormal, &m_pVertices[i0].n);

		m_vTangentList[i0] += vTangent;

		i0 = m_pIndices[iIndex + 2];
		i1 = m_pIndices[iIndex + 0];
		i2 = m_pIndices[iIndex + 1];

		CreateTangentSpaceVectors(&m_pVertices[i0].p, &m_pVertices[i1].p, &m_pVertices[i2].p,
			m_pVertices[i0].t, m_pVertices[i1].t, m_pVertices[i2].t,
			&vTangent, &vBiNormal, &m_pVertices[i0].n);

		m_vTangentList[i0] += vTangent;

	}
	for (int i = 0; i < m_iNumRows*m_iNumCols; i++)
	{
		D3DXVec3Normalize(&m_vTangentList[i], &m_vTangentList[i]);
	}

	m_dxObj.m_pVertexBuffer = DX::CreateVertexBuffer(g_pd3dDevice, &m_pVertices.at(0),
		m_dxObj.m_iVertexNum, m_dxObj.m_iVertexSize);

	UINT iNumVertex = m_vTangentList.size();
	m_pTangentVB = DX::CreateVertexBuffer(
		g_pd3dDevice,
		&m_vTangentList.at(0),
		iNumVertex,
		sizeof(D3DXVECTOR3));

	return true;
}
HRESULT NormalMap::LoadTextures(ID3D11Device* device, const TCHAR* pLoadTextureString)
{
	HRESULT hr = S_OK;
	m_itxNormalMap = I_TexMgr.Add(device, const_cast<TCHAR*>(m_strNormalMapName.c_str()));
	m_pNormalTexture = I_TexMgr.GetPtr(m_itxNormalMap);

	return hr;
}
void NormalMap::SetMatrix(const D3DXMATRIX* pWorld, const D3DXMATRIX* pView, const D3DXMATRIX* pProj)
{
	if (pWorld != NULL)
	{
		m_matWorld = *pWorld;
	}
	D3DXMatrixInverse(&m_matNormal, 0, &m_matWorld);
	if (pView)
	{
		m_matView = *pView;
	}
	if (pProj)
	{
		m_matProj = *pProj;
	}
	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
}

NormalMap::NormalMap()
{
}


NormalMap::~NormalMap()
{
}
