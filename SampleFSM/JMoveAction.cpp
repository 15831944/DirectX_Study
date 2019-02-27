#include "JMoveAction.h"

void JMoveAction::Move()
{

}
void JMoveAction::Attack()
{

}
void JMoveAction::Process(JDxObject* ch)
{
	fPOINT pTarget = ch->m_Pos;
	fPOINT pPos = m_pOwner->m_Pos;

	pTarget.y *= -1.0f;
	pPos.y *= -1.0f;

	Vector2 vDir;
	vDir.x = pTarget.x - pPos.x;
	vDir.y = pTarget.y - pPos.y;
	float fNormal = (float)sqrt((vDir.x * vDir.x) + (vDir.y * vDir.y));
	vDir.x = (float)(vDir.x / fNormal);
	vDir.y = (float)(vDir.y / fNormal);
	m_pOwner->SetTransition(EVENT_FINDTARGET);
}

JMoveAction::JMoveAction(JEnemy* parent) : JEnemyState(parent)
{
	m_vTargetPos.x = rand() % g_rtWindow.right;
	m_vTargetPos.y = rand() % g_rtWindow.bottom;
}


JMoveAction::~JMoveAction()
{
}
