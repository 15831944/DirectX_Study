#include "JStandAction.h"

void JStandAction::Move()
{

}
void JStandAction::Attack()
{

}
void JStandAction::Process(JDxObject* ch)
{
	if (rand() % 100 < 5)
	{
		m_pOwner->SetTransition(EVENT_PATROL);
		return;
	}
}

JStandAction::JStandAction(JEnemy* parent) : JEnemyState(parent)
{
}


JStandAction::~JStandAction()
{
}
