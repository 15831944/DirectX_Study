#include "JButtonCtrl.h"
#include "JEvent.h"
#include "JState.h"
namespace UI
{
	bool JButtonCtrl::Create(ID3D11Device* pDevice, const TCHAR* szNORMAL, const TCHAR* szHOVER, const TCHAR* szPRESS,
		const char* PSName, const TCHAR* szShaderName)
	{
		JImageCtrl::Create(pDevice, PSName, szShaderName);
		/* ====================  Texture Setting ====================*/
		if (!SetTexture(pDevice, szNORMAL)) return false;
		if (!SetTexture(pDevice, szHOVER))  return false;
		if (!SetTexture(pDevice, szPRESS))  return false;
		m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txNORMAL]);
		/* =========================================================== */
		return true;
	}
	void JButtonCtrl::Update()
	{
		if(m_pShape->CheckPicking(&m_matWorld, &m_matView, &m_matProj))
		{
			if (m_pShape->m_bHovered)
			{
				m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txHOVER]);
			}
			if (m_pShape->m_bPressed)
			{
				m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txPRESS]);
			}
			if (m_pShape->m_bClicked)
			{
				if (m_pEvent != nullptr)
					m_pEvent->bEventPlay = true;
			}
		}
		if(m_pEvent != nullptr)
			m_pEvent->Frame();
	}
	bool JButtonCtrl::Frame(const float& spf, const float& accTime) noexcept
	{
		JImageCtrl::Frame(spf, accTime);
		this->Update();
		return true;
	}
	bool JButtonCtrl::Render(ID3D11DeviceContext* pContext) noexcept
	{
		pContext->OMSetBlendState(JState::g_pAlphaBlend, 0, 0xffffffff);
		pContext->OMSetDepthStencilState(JState::g_pDisableDSS, 0x00);
		JImageCtrl::Render(pContext);
		m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txNORMAL]); // Hover, Press 체크가 끝나면 Normal로 돌려놓기
		return true;
	}
}