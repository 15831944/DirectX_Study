#include "JAttackAction.h"

void JAttackAction::Process(JPlayer ch)
{
	for (int SpriteCnt = 0; SpriteCnt < m_pOwner->EnemySpriteList.size(); SpriteCnt++)
	{
		m_pOwner->EnemySpriteList[SpriteCnt].m_pos = m_pOwner->m_pos;
		m_pOwner->EnemySpriteList[SpriteCnt].m_CenterPos = m_pOwner->m_CenterPos;
		m_pOwner->EnemySpriteList[SpriteCnt].Frame();
	}

	fPOINT UserPos = ch.m_pos;
	fPOINT EnemyPos = m_pOwner->m_pos;

	Vector2 vDir;
	vDir.x = UserPos.x - EnemyPos.x;
	vDir.y = UserPos.y - EnemyPos.y;

	float fNormal = (float)sqrt((vDir.x * vDir.x) + (vDir.y * vDir.y));
	vDir.x = (float)(vDir.x / fNormal);
	vDir.y = (float)(vDir.y / fNormal);

	if (fNormal > 300.0f)
	{
		m_pOwner->SetTransition(EVENT_LOSTTARGET);
		return;
	}

	if (m_pOwner->m_pos.x < UserPos.x) m_pOwner->m_pos.x += m_pOwner->m_fSpeed * g_fSecPerFrame;
	if (m_pOwner->m_pos.x > UserPos.x) m_pOwner->m_pos.x -= m_pOwner->m_fSpeed * g_fSecPerFrame;
	if (m_pOwner->m_pos.y < UserPos.y) m_pOwner->m_pos.y += m_pOwner->m_fSpeed * g_fSecPerFrame;
	if (m_pOwner->m_pos.y > UserPos.y) m_pOwner->m_pos.y -= m_pOwner->m_fSpeed * g_fSecPerFrame;
}

JAttackAction::JAttackAction(JEnemy* parent) : JEnemyState(parent)
{
}


JAttackAction::~JAttackAction()
{
}
