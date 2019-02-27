#include "JSliderCtrl.h"
#include "JEvent.h"
namespace UI
{
	bool JSliderCtrl::Create(ID3D11Device* pDevice, const char* PSName, const TCHAR* szShaderName)
	{
		if (!m_pSliderBar->Create(pDevice, PSName, szShaderName)) return false;
		if (!m_pSliderHandle->Create(pDevice, PSName, szShaderName)) return false;
		return true;
	}
	bool JSliderCtrl::SetTexture(ID3D11Device* pDevice, const TCHAR* szBar, const TCHAR* szHandle)
	{
		if (!m_pSliderBar->SetTexture(pDevice, szBar)) return false;
		if (!m_pSliderHandle->SetTexture(pDevice, szHandle)) return false;
		//m_pSliderHandle->m_vPos.x = m_pSliderBar->m_vPos.x + m_pSliderBar->m_vScl.x;
		return true;
	}
	const float* JSliderCtrl::GetValue()
	{
		return &m_fValue;
	}
	void JSliderCtrl::Update()
	{
		if (m_pSliderHandle->m_pShape->CheckPicking(
			&m_pSliderHandle->m_matWorld, 
			&m_pSliderHandle->m_matView, 
			&m_pSliderHandle->m_matProj))
		{
			if (m_pSliderHandle->m_pShape->m_bHovered)
			{
			}
			if (m_pSliderHandle->m_pShape->m_bPressed)
			{
				m_pSliderHandle->m_vPos.x = Input::GetCursor().x - Window::getClientRect().right / 2.0f;
				if (m_pEvent != nullptr)
					m_pEvent->bEventPlay = true;
			}
			if (m_pSliderHandle->m_pShape->m_bClicked)
			{
			}
		}
		if (m_pEvent != nullptr)
			m_pEvent->Frame();

		/*  */
		m_pSliderHandle->m_vPos.y = m_pSliderBar->m_vPos.y;
		if (m_pSliderHandle->m_vPos.x <= m_pSliderBar->m_vPos.x - m_pSliderBar->m_vScl.x)
		{
			m_pSliderHandle->m_vPos.x = m_pSliderBar->m_vPos.x - m_pSliderBar->m_vScl.x;
		}

		if (m_pSliderHandle->m_vPos.x >= m_pSliderBar->m_vPos.x + m_pSliderBar->m_vScl.x)
		{
			m_pSliderHandle->m_vPos.x = m_pSliderBar->m_vPos.x + m_pSliderBar->m_vScl.x;
		}

		m_fValue = ((m_pSliderHandle->m_vPos.x - m_pSliderBar->m_vPos.x) / m_pSliderBar->m_vScl.x) * 0.5f + 0.5f;
	}
	bool JSliderCtrl::Frame(const float& spf, const float& accTime) noexcept
	{
		this->Update();
		m_pSliderBar->Frame(spf, accTime);
		m_pSliderHandle->Frame(spf, accTime);
		return true;
	}
	bool JSliderCtrl::Render(ID3D11DeviceContext* pContext) noexcept
	{
		//pContext->OMSetBlendState(JState::g_pAlphaBlend, 0, 0xffffffff);
		//pContext->OMSetDepthStencilState(JState::g_pDisableDSS, 0x00);
		m_pSliderBar->Render(pContext);
		m_pSliderHandle->Render(pContext);
		return true;
	}

	JSliderCtrl::JSliderCtrl(wstring NodeName) : JPanel(NodeName)
	{
		wstring temp = NodeName + L"_Bar";
		m_pSliderBar = new JImageCtrl(temp);
		wstring temp2 = NodeName + L"_Handle";
		m_pSliderHandle = new JImageCtrl(temp2);
	}


	JSliderCtrl::~JSliderCtrl()
	{
	}
}