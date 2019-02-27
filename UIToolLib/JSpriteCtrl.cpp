#include "JSpriteCtrl.h"
#include "Timer.h"
namespace UI
{
	bool JSpriteCtrl::Create(ID3D11Device* pDevice, float fAnimTime, vector<T_STR> FileList, const char* PSName, const TCHAR* szShaderName)
	{
		JImageCtrl::Create(pDevice, PSName, szShaderName);
		/* ====================  Texture Setting ====================*/
		for (int iList = 0; iList < FileList.size(); iList++)
		{
			// Texture index�� �迭�� �������ִ´ٸ�
			INT iIndex = I_TexMgr.Add(pDevice, FileList[iList].c_str());
			if (iIndex < 0)	return false;
			if (!SetTexture(pDevice, FileList[iList].c_str()))
				return false;
		}
		m_iNumTexture = (int)m_pIndexList.size();
		m_fAnimTime = fAnimTime;
		m_fChangeTime = fAnimTime / m_iNumTexture;
		/* =========================================================== */
		return true;
	}
	void JSpriteCtrl::Update()
	{
		// �ִϸ��̼� ��ü �ֱ� ���� �ð�
		m_fTime += Timer::SPF;

		if (m_fTime >= m_fChangeTime)
		{
			if (++m_iCurrentIndex >= m_iNumTexture)
				m_iCurrentIndex = 0;

			m_fTime = 0.0f;
		}
		// �ؽ�ó �ִϸ��̼� ��ü
		if (m_pIndexList.size())
		{
			m_pTexture = I_TexMgr.GetPtr(m_pIndexList[m_iCurrentIndex]);
		}
	}
	bool JSpriteCtrl::Frame(const float& spf, const float& accTime)noexcept
	{
		JImageCtrl::Frame(spf, accTime);
		this->Update();
		return true;
	}
	bool JSpriteCtrl::Render(ID3D11DeviceContext* pContext)noexcept
	{
		return JImageCtrl::Render(pContext);
	}
	JSpriteCtrl::JSpriteCtrl(wstring NodeName) : JImageCtrl(NodeName)
	{
	}

	JSpriteCtrl::~JSpriteCtrl()
	{
	}
}