#include "JEnemy.h"
#include "JStandAction.h"
#include "JMoveAction.h"
#include "JAttackAction.h"

void JEnemy::FSM(int iIndex)
{
	m_pFSM = I_FSM.GetPtr(iIndex);
	m_pActionList[STATE_STAND] = (JEnemyState*)new JStandAction(this);
	m_pActionList[STATE_MOVE] = (JEnemyState*)new JMoveAction(this);
	m_pActionList[STATE_ATTACK] = (JEnemyState*)new JAttackAction(this);
	m_pAction = m_pActionList[STATE_MOVE];
	m_dwCurrentState = STATE_MOVE;
}
bool JEnemy::Frame()
{
	m_CenterPos.x = m_pos.x + (m_rt.right / 2);
	m_CenterPos.y = m_pos.y + (m_rt.bottom / 2);
	m_rtCollision.left = m_CenterPos.x;
	m_rtCollision.top = m_CenterPos.y;
	m_rtCollision.right = m_rt.right + m_CenterPos.x;
	m_rtCollision.bottom = m_rt.bottom + m_CenterPos.y;

	return true;
}
void JEnemy::Process(JPlayer target)
{
	m_pAction->Process(target);
}
DWORD JEnemy::GetState()
{
	if (m_pFSM == 0) return 0;
	return m_dwCurrentState;
}
void JEnemy::SetTransition(DWORD Event)
{
	m_dwCurrentState = m_pFSM->StateTransition(m_dwCurrentState, Event);
	m_pAction = m_pActionList[m_dwCurrentState];
}
void JEnemy::Move(int x, int y)
{
	m_pos.x -= g_fSecPerFrame * m_fSpeed;

}
//////////////////////
JEnemy::JEnemy()
{
	m_pos.x = 1000;
	m_pos.y = 350;
	m_bDie = false;
	m_bCreate = false;
	m_EnemyState = ENEMY_MOVE;
	m_fCreateTime = 0.0f;
	m_fRandTime = 2 + rand() % 8;
}


JEnemy::~JEnemy()
{
}
