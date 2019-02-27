#include "JParticle.h"
#include "Timer.h"
namespace UI
{
	JParticle::JParticle()
	{	
		fMoveSpeed = 0;
		fRotateSpeed = 0;
		vDir = {0,0,0};
		qDirAngle = { 0 ,0,0,0};
		vColor = {0,0,0,0};
		fElapseTime = 0;
		fLifeTime = 0;
		fStartTime = JDxHelper::fRand(0.0f, 20.0f);
		bRender = false;
		fRandom = JDxHelper::fRand(1.0f, 1000.f);
		bTurnX = false;
		bTurnY = false;
		bTurnZ = false;
	}
	void JParticle::Update(const D3DXMATRIX* matSpriteScl)
	{
		D3DXMatrixIdentity(&m_matWorld);
		D3DXMatrixIdentity(&m_matRot);
		D3DXMatrixIdentity(&m_matScl);
		m_matScl = *matSpriteScl;
		D3DXMatrixRotationYawPitchRoll(&m_matRot, m_qRot.y, m_qRot.x, m_qRot.z);
		//D3DXMatrixRotationQuaternion(&m_matRot, &m_qRot);
		m_matWorld = m_matScl * m_matRot;
		m_matWorld._41 = m_vPos.x;
		m_matWorld._42 = m_vPos.y;
		m_matWorld._43 = m_vPos.z;
	}
	bool JParticle::Frame(const float& spf, const D3DXMATRIX* matSpriteScl)
	{
		fElapseTime += spf;
		fTimer += spf;
		if (fStartTime > fElapseTime) return false;
		bRender = true;
		m_vPos += vDir * (spf * fMoveSpeed);
		m_qRot += qDirAngle * (spf * fRotateSpeed);

		if (bTurnX)
			vDir.x = cos(fRandom + fTimer);
		if (bTurnY)
			vDir.y = cos(fRandom + fTimer);
		if (bTurnZ)
			vDir.z = cos(fRandom + fTimer);

		Update(matSpriteScl);
		return true;
	}
	void JParticle::SetTurnDirection(const bool bX, const bool bY, const bool bZ)
	{
		bTurnX = bX;
		bTurnY = bY;
		bTurnZ = bZ;
	}
	void JParticle::SetColor(const D3DXVECTOR4 vMin, const D3DXVECTOR4 vMax)
	{
		vColor = UI::JDxHelper::vRand(vMin, vMax);
	}
	void JParticle::SetStartPos(const D3DXVECTOR3 vMin, D3DXVECTOR3 vMax)
	{
		m_vPos = UI::JDxHelper::vRand(vMin, vMax);
	}
	void JParticle::SetMoveSpeed(const float fMinSpeed, const float fMaxSpeed)
	{
		fMoveSpeed = UI::JDxHelper::fRand(fMinSpeed, fMaxSpeed);
	}
	void JParticle::SetRotateSpeed(const float fMinSpeed, const float fMaxSpeed)
	{
		fRotateSpeed = UI::JDxHelper::fRand(fMinSpeed, fMaxSpeed);
	}
	void JParticle::SetLifeTime(const float MinTime, const float MaxTime)
	{
		/* Ω√¿€time + */
		fLifeTime = fStartTime + UI::JDxHelper::fRand(MinTime, MaxTime);
	}
	void JParticle::SetDirection(const D3DXVECTOR3 vMin, const D3DXVECTOR3 vMax)
	{
		vDir = JDxHelper::vRand(vMin, vMax);
		D3DXVec3Normalize(&vDir, &vDir);
	}
	void JParticle::SetDirectionAngle(const D3DXQUATERNION qMin, const D3DXQUATERNION qMax)
	{
		qDirAngle = JDxHelper::qRand(qMin, qMax);
		D3DXQuaternionNormalize(&qDirAngle, &qDirAngle);
	}
}