#include "JStandAction.h"

void JStandAction::Move()
{

}
void JStandAction::Attack()
{

}
void JStandAction::Process(JPlayer ch)
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

	for (int SpriteCnt = 0; SpriteCnt < m_pOwner->EnemySpriteList.size(); SpriteCnt++)
	{
		m_pOwner->EnemySpriteList[SpriteCnt].m_pos = m_pOwner->m_pos;
		m_pOwner->EnemySpriteList[SpriteCnt].m_CenterPos = m_pOwner->m_CenterPos;
	}
	static float fTime = 0.0f;
	fTime += g_fSecPerFrame;
	if (fTime > 0.7f)
	{
		m_pOwner->SetTransition(EVENT_PATROL);
		fTime = 0.0f;
		return;
	}
}

JStandAction::JStandAction(JEnemy* parent) : JEnemyState(parent)
{
}


JStandAction::~JStandAction()
{
}
