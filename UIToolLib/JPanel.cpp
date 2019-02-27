#include "JPanel.h"
#include "JEvent.h"
#include "ObjectManager.h"
namespace UI
{
	bool JPanel::BindEvent(JEvent* pEvent)
	{
		m_pEvent = pEvent;
		return true;
	}
	void JPanel::Update()
	{
		// matWorld 갱신
		D3DXMatrixScaling(&m_matScl, m_vScl.x, m_vScl.y, m_vScl.z);
		D3DXMatrixRotationYawPitchRoll(&m_matRot, m_vRot.x, m_vRot.y, m_vRot.z);
		m_matWorld = m_matScl * m_matRot;
		m_matWorld._41 = m_vPos.x;
		m_matWorld._42 = m_vPos.y;
		m_matWorld._43 = m_vPos.z;

		// 부모 행렬 곱
		D3DXMATRIX matParent;
		D3DXMatrixIdentity(&matParent);
		if (m_pParent != nullptr)
		{
			matParent = m_pParent->m_matWorld;
		}
		m_matWorld = matParent * m_matWorld;
	}
	bool JPanel::SetParent(JPanel* pParent)
	{
		if (pParent == nullptr) return false;

		m_pParent = pParent;
		m_ParentName = pParent->m_NodeName;
		pParent->m_pChildList.push_back(this);
		return true;
	}
	void JPanel::push_child(JPanel* pChild)
	{
		if (pChild == nullptr) return;

		pChild->m_pParent = this;
		pChild->m_ParentName = this->m_NodeName;

		m_pChildList.push_back(pChild);
	}

	bool JPanel::Init() noexcept
	{
		GameObject::Init();
		return true;
	}
	bool JPanel::Frame(const float& spf, const float& accTime) noexcept
	{
		if (!m_bRender) return false;
		GameObject::Frame(spf, accTime);
		for (int iC = 0; iC < m_pChildList.size(); iC++)
		{
			m_pChildList[iC]->Frame(spf, accTime);
		}
		return true;
	}
	bool JPanel::Render(ID3D11DeviceContext* pContext)noexcept
	{
		if (!m_bRender) return false;
		GameObject::Render(pContext);
		for (int iC = 0; iC < m_pChildList.size(); iC++)
		{
			m_pChildList[iC]->Render(pContext);
		}
		return true;
	}
	bool JPanel::Release() noexcept
	{
		for (int iC = 0; iC < m_pChildList.size(); iC++)
		{
			m_pChildList[iC]->Release();
		}
		return true;
	}
	JPanel::JPanel(wstring NodeName)
	{
		m_NodeName = NodeName;
		UI::JTransform::m_pCurTransform = new JTransform();
		D3DXMatrixIdentity(&m_matScl);
		D3DXMatrixIdentity(&m_matRot);
		D3DXMatrixIdentity(&m_matTrans);
		D3DXMatrixIdentity(&m_matWorld);
		D3DXMatrixIdentity(&m_matView);
		D3DXMatrixIdentity(&m_matProj);

		/* UI 전용 view proj create */
		D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		D3DXVECTOR3 vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		float fWidth = Window::getClientRect().right / 2.0f;
		float fHeight = Window::getClientRect().right / 2.0f;
		D3DXMatrixLookAtLH(&m_matView, &vPos, &vTarget, &vUp);
		D3DXMatrixOrthoOffCenterLH(&m_matProj, -fWidth, fWidth, -fHeight, fHeight, 0, 1000);
	}
	JPanel::~JPanel()
	{
	}
}