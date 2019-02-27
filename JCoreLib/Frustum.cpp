#include "Frustum.h"
bool Frustum::SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
{
	if (matWorld != NULL)
	{
		m_mWorld = *matWorld;
	}
	else
	{
		D3DXMatrixIdentity(&m_mWorld);
	}
	if (matView != NULL)
	{
		m_mView = *matView;
	}
	if (matProj != NULL)
	{
		m_mProj = *matProj;
	}
	return true;
}
bool Frustum::CreateFrustum(ID3D11DeviceContext* context, D3DXMATRIX matView, D3DXMATRIX matProj)
{
	m_pBox = new JBoxShape();
	m_pBox->Init();
	m_VertexList.resize(24);
	D3DXMatrixMultiply(&m_matViewProj, &matView, &matProj);

	D3DXMatrixInverse(&m_matViewProj, NULL, &m_matViewProj);

	//m_vFrustum[0] = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	//m_vFrustum[1] = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	//m_vFrustum[2] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	//m_vFrustum[3] = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

	//m_vFrustum[4] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	//m_vFrustum[5] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	//m_vFrustum[6] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//m_vFrustum[7] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	//for (int iVertex = 0; iVertex < 8; iVertex++)
	//{
	//	D3DXVec3TransformCoord(&m_vFrustum[iVertex], &m_vFrustum[iVertex], &m_matViewProj);
	//}
	for (int iVertex = 0; iVertex < m_pBox->m_pVertices.size(); iVertex++)
	{
		D3DXVec3TransformCoord(&m_pBox->m_pVertices[iVertex].p, &m_pBox->m_pVertices[iVertex].p, &m_matViewProj);
	}
	context->UpdateSubresource(m_pBox->m_dxObj.m_pVertexBuffer, 0, NULL, &m_pBox->m_pVertices.at(0), 0, 0);
	return true;
}
bool Frustum::Init()
{
	return true;
}
bool Frustum::PreRender(ID3D11DeviceContext* context)
{
	//m_VertexList[0] = PNCT_VERTEX(m_vFrustum[1], D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	//m_VertexList[1] = PNCT_VERTEX(m_vFrustum[2], D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	//m_VertexList[2] = PNCT_VERTEX(m_vFrustum[3], D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	//m_VertexList[3] = PNCT_VERTEX(m_vFrustum[0], D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));
	//// µÞ¸é
	//m_VertexList[4] = PNCT_VERTEX(m_vFrustum[6], D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	//m_VertexList[5] = PNCT_VERTEX(m_vFrustum[5], D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	//m_VertexList[6] = PNCT_VERTEX(m_vFrustum[4], D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	//m_VertexList[7] = PNCT_VERTEX(m_vFrustum[7], D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));

	//// ¿ÞÂÊ
	//m_VertexList[8] = PNCT_VERTEX(m_vFrustum[5], D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	//m_VertexList[9] = PNCT_VERTEX(m_vFrustum[1], D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	//m_VertexList[10] = PNCT_VERTEX(m_vFrustum[0], D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	//m_VertexList[11] = PNCT_VERTEX(m_vFrustum[4], D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));

	//// ¿À´ÃÂÊ¸é
	//m_VertexList[12] = PNCT_VERTEX(m_vFrustum[2], D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	//m_VertexList[13] = PNCT_VERTEX(m_vFrustum[6], D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	//m_VertexList[14] = PNCT_VERTEX(m_vFrustum[7], D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	//m_VertexList[15] = PNCT_VERTEX(m_vFrustum[3], D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));

	//// À­¸é
	//m_VertexList[16] = PNCT_VERTEX(m_vFrustum[5], D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	//m_VertexList[17] = PNCT_VERTEX(m_vFrustum[6], D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	//m_VertexList[18] = PNCT_VERTEX(m_vFrustum[2], D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	//m_VertexList[19] = PNCT_VERTEX(m_vFrustum[1], D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));

	//// ¾Æ·§¸é
	//m_VertexList[20] = PNCT_VERTEX(m_vFrustum[0], D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	//m_VertexList[21] = PNCT_VERTEX(m_vFrustum[3], D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	//m_VertexList[22] = PNCT_VERTEX(m_vFrustum[7], D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	//m_VertexList[23] = PNCT_VERTEX(m_vFrustum[4], D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));

	//context->UpdateSubresource(m_pBox->m_dxObj.m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
	m_pBox->SetMatrix(&m_mWorld, &m_mView, &m_mProj);
	m_pBox->m_dxObj.PreRender(context, 0);
	return true;
}
bool Frustum::Render(ID3D11DeviceContext* context)
{
	if (m_pBox == NULL) return true;
	PreRender(context);
	PostRender(context);
	return true;
}
bool Frustum::PostRender(ID3D11DeviceContext* context)
{
	context->UpdateSubresource(m_pBox->m_dxObj.m_pConstantBuffer, 0, NULL, &m_pBox->m_cbData, 0, 0);
	m_pBox->m_dxObj.PostRender(context,0);
	return true;
}

Frustum::Frustum()
{
}


Frustum::~Frustum()
{
}
