#include "JCheckCtrl.h"
namespace UI
{
	bool JCheckCtrl::Create(ID3D11Device* pDevice, const TCHAR* szENABLE, const TCHAR* szDISABLE,
		const char* PSName, const TCHAR* szShaderName)
	{
		JImageCtrl::Create(pDevice, PSName, szShaderName);
		/* ====================  Texture Setting ====================*/
		if (!SetTexture(pDevice, szENABLE)) return false;
		if (!SetTexture(pDevice, szDISABLE))  return false;
		m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txDISABLE]);
		/* =========================================================== */
		return true;
	}
	void JCheckCtrl::Update()
	{
		if (m_pShape->CheckPicking(&m_matWorld, &m_matView, &m_matProj))
		{
			if (m_pShape->m_bClicked)
			{
				m_bCheck = !m_bCheck;
			}
		}
		if (m_bCheck)
		{
			m_pTexture = I_TexMgr.GetPtr(JImageCtrl::m_pIndexList[txENABLE]);
		}
		else
		{
			m_pTexture = I_TexMgr.GetPtr(JImageCtrl::m_pIndexList[txDISABLE]);
		}
	}
	bool JCheckCtrl::Frame(const float& spf, const float& accTime) noexcept
	{
		JImageCtrl::Frame(spf, accTime);
		this->Update();
		return true;
	}

	JCheckCtrl::JCheckCtrl(wstring NodeName) : JImageCtrl(NodeName)
	{
	}


	JCheckCtrl::~JCheckCtrl()
	{
	}
}