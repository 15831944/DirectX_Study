#include "JMoveAction.h"

void JMoveAction::Move()
{

}
void JMoveAction::Attack()
{

}
void JMoveAction::Process(JPlayer ch)
{
	fPOINT UserPos = ch.m_CenterPos;
	fPOINT EnemyPos = m_pOwner->m_CenterPos;

	Vector2 vDir;
	vDir.x = UserPos.x - EnemyPos.x;
	vDir.y = UserPos.y - EnemyPos.y;

	float fNormal = (float)sqrt((vDir.x * vDir.x) + (vDir.y * vDir.y));
	vDir.x = (float)(vDir.x / fNormal);
	vDir.y = (float)(vDir.y / fNormal);

	if (fNormal < 300.0f)
	{
		m_pOwner->SetTransition(EVENT_FINDTARGET);
		return;
	}

	m_pOwner->m_pos.x -= g_fSecPerFrame * m_pOwner->m_fSpeed;
	for (int SpriteCnt = 0; SpriteCnt < m_pOwner->EnemySpriteList.size(); SpriteCnt++)
	{
		m_pOwner->EnemySpriteList[SpriteCnt].m_pos = m_pOwner->m_pos;
		m_pOwner->EnemySpriteList[SpriteCnt].m_CenterPos = m_pOwner->m_CenterPos;
		m_pOwner->EnemySpriteList[SpriteCnt].Frame();
	}

	static float fTime = 0.0f;
	fTime += g_fSecPerFrame;
	if (fTime > 1.0f)
	{
		m_pOwner->SetTransition(EVENT_STOPWALK);
		fTime = 0.0f;
		return;
	}
}

JMoveAction::JMoveAction(JEnemy* parent) : JEnemyState(parent)
{
	m_vTargetPos.x = rand() % g_rtWindow.right;
	m_vTargetPos.y = rand() % g_rtWindow.bottom;
	m_fTime = 1.0f;
}


JMoveAction::~JMoveAction()
{
}
