#include "JModel.h"

bool JModel::Init()
{
	return true;
}
bool JModel::Frame()
{
	return true;
}
bool JModel::Render()
{
	return true;
}
bool JModel::Release()
{
	return true;
}
void JModel::SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
{
	if (matWorld != NULL)
		m_matWorld = *matWorld;
	if (matView != NULL)
		m_matView = *matView;
	if (matProj != NULL)
		m_matProj = *matProj;

	m_vRight.x = m_matWorld._11;
	m_vRight.y = m_matWorld._12;
	m_vRight.z = m_matWorld._13;

	m_vUp.x = m_matWorld._21;
	m_vUp.y = m_matWorld._22;
	m_vUp.z = m_matWorld._23;

	m_vLook.x = m_matWorld._31;
	m_vLook.y = m_matWorld._32;
	m_vLook.z = m_matWorld._33;

	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;

	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
}
JModel::JModel()
{
}


JModel::~JModel()
{
}
