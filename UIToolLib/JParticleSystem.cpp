#include "JParticleSystem.h"
#include "JState.h"
namespace UI
{
	bool JParticleSystem::Create(ID3D11Device* pDevice, int iMaxParticle, float fAnimTime,
		D3DXVECTOR3 vSpriteSize, vector<T_STR> FileList, const char* PSName, const TCHAR* szShaderName)
	{
		m_iMaxParticle = iMaxParticle;
		for (int i = 0; i < iMaxParticle; i++)
		{
			JParticle* particle = new JParticle();
			m_pParticle.push_back(particle);
		}
		m_pSprite->Create(pDevice, fAnimTime, FileList, PSName, szShaderName);
		m_pSprite->Scale(vSpriteSize.x, vSpriteSize.y, vSpriteSize.z);
		return true;
	}

	bool JParticleSystem::Frame(const float& spf, const float& accTime)noexcept
	{
		m_pSprite->Frame(spf, accTime);
		for (int iParticle = 0; iParticle < m_iMaxParticle; iParticle++)
		{
			m_pParticle[iParticle]->Frame(spf, &m_pSprite->m_matScl);
			if (m_pParticle[iParticle]->fElapseTime >= m_pParticle[iParticle]->fLifeTime)
			{
				m_pParticle[iParticle]->bRender = false;
				m_pParticle[iParticle]->fElapseTime = 0.0f;
				m_pParticle[iParticle]->m_qRot = D3DXQUATERNION(0, 0, 0, 0);
				m_pParticle[iParticle]->SetColor(m_vMinColor, m_vMaxColor);
				m_pParticle[iParticle]->SetTurnDirection(m_bTurnX, m_bTurnY, m_bTurnZ);
				m_pParticle[iParticle]->SetStartPos(m_vMinStartPos, m_vMaxStartPos);
				m_pParticle[iParticle]->SetLifeTime(m_fMinLifeTime, m_fMaxLifeTime);
				m_pParticle[iParticle]->SetDirection(m_vMinDirection, m_vMaxDirection);
				m_pParticle[iParticle]->SetDirectionAngle(m_qMinDirAngle, m_qMaxDirAngle);
				m_pParticle[iParticle]->SetMoveSpeed(m_fMinMoveSpeed, m_fMaxMoveSpeed);
				m_pParticle[iParticle]->SetRotateSpeed(m_fMinRotateSpeed, m_fMaxRotateSpeed);
			}
		}
		return true;
	}
	bool JParticleSystem::Render(ID3D11DeviceContext* pContext)noexcept
	{
		for (int iParticle = 0; iParticle < m_pParticle.size(); iParticle++)
		{
			pContext->RSSetState(JState::g_pRSNoneCullSolid);
			pContext->OMSetBlendState(JState::g_pAlphaBlend, 0, (UINT)-1);
			//pContext->OMSetDepthStencilState(JState::g_pDisableDSS, 0x00);
			if (m_pParticle[iParticle]->bRender == false) continue;
			m_pSprite->m_pShape->m_cbData.vColor = m_pParticle[iParticle]->vColor;
			m_pSprite->SetMatrix(&m_pParticle[iParticle]->m_matWorld , &m_matView, &m_matProj);
			m_pSprite->Render(pContext);
		}
		return true;
	}
	bool JParticleSystem::Release()noexcept
	{
		return true;
	}
	void JParticleSystem::SetTurnDirection(const bool bX, const bool bY, const bool bZ)
	{
		m_bTurnX = bX;
		m_bTurnY = bY;
		m_bTurnZ = bZ;
	}
	void JParticleSystem::SetStartPos(const D3DXVECTOR3 vMin, const D3DXVECTOR3 vMax)
	{
		m_vMinStartPos = vMin;
		m_vMaxStartPos = vMax;
	}
	void JParticleSystem::SetLifeTime(float fMin, float fMax)
	{
		m_fMinLifeTime = fMin;
		m_fMaxLifeTime = fMax;
	}
	void JParticleSystem::SetDirection(const D3DXVECTOR3 vMin, const D3DXVECTOR3 vMax)
	{
		m_vMinDirection = vMin;
		m_vMaxDirection = vMax;
	}
	void JParticleSystem::SetDirectionAngle(const D3DXQUATERNION qMin, const D3DXQUATERNION qMax)
	{
		m_qMinDirAngle = qMin;
		m_qMaxDirAngle = qMax;
	}
	void JParticleSystem::SetMoveSpeed(const float fMin, const float fMax)
	{
		m_fMinMoveSpeed = fMin;
		m_fMaxMoveSpeed = fMax;
	}
	void JParticleSystem::SetRotateSpeed(const float fMin, const float fMax)
	{
		m_fMinRotateSpeed = fMin;
		m_fMaxRotateSpeed = fMax;
	}
	void JParticleSystem::SetColor(const D3DXVECTOR4 vMin, const D3DXVECTOR4 vMax)
	{
		m_vMinColor = vMin;
		m_vMaxColor = vMax;
	}
}