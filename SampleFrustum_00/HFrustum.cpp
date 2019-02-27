#include "HFrustum.h"

bool HFrustum::SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	if (matWorld != NULL)
	{
		m_matWorld = *matWorld;
	}
	if (matView != NULL)
	{
		m_matView = *matView;
	}
	if (matProj != NULL)
	{
		m_matProj = *matProj;
	}
	return true;
}
bool HFrustum::CreateFrustum(ID3D11DeviceContext* context, D3DXMATRIX matView, D3DXMATRIX matProj)
{
	//m_pBox = new JBoxShape();
	//m_pBox->Init();
	///* 절두체 정점 -> World */
	//D3DXMatrixMultiply(&m_matViewProj, &m_matView, &m_matProj);

	//D3DXMatrixInverse(&m_matViewProj, NULL, &m_matViewProj);

	//for (int iVer = 0; iVer < m_pBox->m_pVertices.size(); iVer++)
	//{
	//	D3DXVec3TransformCoord(&m_pBox->m_pVertices[iVer].p, &m_pBox->m_pVertices[iVer].p, &m_matViewProj);
	//}
	//context->UpdateSubresource(m_pBox->m_dxObj.m_pVertexBuffer, 0, 0, &m_pBox->m_pVertices.at(0), 0, 0);
	m_box.Init();
	D3DXMATRIX viewproj;
	viewproj = matView * matProj;
	D3DXMatrixInverse(&viewproj, NULL, &viewproj);
	for (int iVer = 0; iVer < m_box.m_pVertices.size(); iVer++)
	{
		D3DXVec3TransformCoord(&m_box.m_pVertices[iVer].p, &m_box.m_pVertices[iVer].p, &viewproj);
	}
	context->UpdateSubresource(m_box.m_dxObj.m_pVertexBuffer, 0, 0, &m_box.m_pVertices.at(0), 0, 0);
	//m_vFrustum[0] = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	//m_vFrustum[1] = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	//m_vFrustum[2] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	//m_vFrustum[3] = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	//m_vFrustum[4] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	//m_vFrustum[5] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	//m_vFrustum[6] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//m_vFrustum[7] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	//for (int iVer = 0; iVer < 8; iVer++)
	//{
	//	D3DXVec3TransformCoord(&m_vFrustum[iVer], &m_vFrustum[iVer], &m_matViewProj);
	//}
	//// 좌
	//m_Plane[0].CreatePlane(m_vFrustum[5], m_vFrustum[0], m_vFrustum[1]);
	//// 우
	//m_Plane[1].CreatePlane(m_vFrustum[3], m_vFrustum[6], m_vFrustum[2]);
	//// 상
	//m_Plane[2].CreatePlane(m_vFrustum[5], m_vFrustum[2], m_vFrustum[6]);
	//// 하
	//m_Plane[3].CreatePlane(m_vFrustum[0], m_vFrustum[7], m_vFrustum[3]);
	//// 정면
	//m_Plane[4].CreatePlane(m_vFrustum[0], m_vFrustum[2], m_vFrustum[1]);
	//// 후면
	//m_Plane[5].CreatePlane(m_vFrustum[6], m_vFrustum[4], m_vFrustum[5]);
	return true;
}
bool HFrustum::Init()
{
	//m_pBox = new JBoxShape();
	//m_pBox->Init();
	////m_pBox->m_pVertices = 
	////
	//m_pVertices.resize(24);
	return true;
}
bool HFrustum::PreRender(ID3D11DeviceContext* context)
{
	//context->UpdateSubresource(m_pBox->m_dxObj.m_pVertexBuffer, 0, 0, &m_pBox->m_pVertices.at(0), 0, 0);
	//m_pBox->SetMatrix(NULL, &m_matView, &m_matProj);
	//m_pBox->m_dxObj.PreRender(context, 0);
	
	return true;
}
bool HFrustum::Render(ID3D11DeviceContext* context)
{
	//PreRender(context);
	//context->PSSetShader(m_pPixelShader, NULL, 0);
	//PostRender(context);
	m_box.SetMatrix(&m_matWorld, &m_matView, &m_matProj);
	m_box.Render(context);
	return true;
}
bool HFrustum::PostRender(ID3D11DeviceContext* context)
{
	//context->UpdateSubresource(m_pBox->m_dxObj.m_pConstantBuffer, 0, 0, &m_pBox->m_cbData, 0, 0);
	//m_pBox->m_dxObj.PostRender(context, 0);
	return true;
}
HFrustum::HFrustum()
{

}


HFrustum::~HFrustum()
{
}
