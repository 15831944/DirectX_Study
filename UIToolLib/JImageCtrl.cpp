#include "JImageCtrl.h"
namespace UI
{
	void JImageCtrl::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
	{
		if (pWorld != NULL)
			m_matWorld = *pWorld;
		if (pView != NULL)
			m_matView = *pView;
		if (pProj != NULL)
			m_matProj = *pProj;

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

		D3DXMatrixTranspose(&m_pShape->m_cbData.matWorld, &m_matWorld);
		D3DXMatrixTranspose(&m_pShape->m_cbData.matView, &m_matView);
		D3DXMatrixTranspose(&m_pShape->m_cbData.matProj, &m_matProj);
	}
	bool JImageCtrl::Create(ID3D11Device* pDevice,const char* psName, const TCHAR* psShaderName)
	{
		m_pShape->Create(pDevice, psName, psShaderName);
		return true;
	}
	bool JImageCtrl::SetTexture(ID3D11Device* pDevice, const TCHAR* txName)
	{
		int iIndex = UI::I_TexMgr.Add(pDevice, txName);
		if (iIndex < 0) return false;
		m_pIndexList.push_back(iIndex);
		return true;
	}
	void JImageCtrl::Update()
	{
		JPanel::Update(); // world matrix update
	}
	bool JImageCtrl::Frame(const float& spf, const float& accTime) noexcept
	{
		this->Update();
		{

		}
		JPanel::Frame(spf, accTime); // child 순회
		return true;
	}
	bool JImageCtrl::Render(ID3D11DeviceContext* pContext) noexcept
	{
		SetMatrix(&m_matWorld, &m_matView, &m_matProj);
		m_pShape->Render(pContext, m_pTexture);
		JPanel::Render(pContext); // Child 순회
		return true;
	}
}