#include "JEnemy.h"
#include "JStandAction.h"
#include "JMoveAction.h"
#include "JAttackAction.h"
#include "JRunAwayAction.h"

void JEnemy::FSM(int iIndex)
{
	m_pFSM = I_FSM.GetPtr(iIndex);
	m_pActionList[STATE_STAND] = (JEnemyState*)new JStandAction(this);
	m_pActionList[STATE_MOVE] = (JEnemyState*)new JMoveAction(this);
	m_pActionList[STATE_ATTACK] = (JEnemyState*)new JAttackAction(this);
	m_pActionList[STATE_RUNAWAY] = (JEnemyState*)new JRunawayAction(this);
	m_pAction = m_pActionList[STATE_MOVE];
	m_dwCurrentState = STATE_MOVE;
}
bool JEnemy::Frame()
{
	return true;
}
void JEnemy::Process(JDxObject* target)
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

}
JEnemy::JEnemy()
{

}
JEnemy::~JEnemy()
{

}