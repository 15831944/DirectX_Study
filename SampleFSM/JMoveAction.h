#pragma once
#include "JEnemy.h"
class JMoveAction : JEnemyState
{
public:
	virtual void Move();
	virtual void Attack();
	virtual void Process(JDxObject* ch);
public:
	JMoveAction(JEnemy* parent);
	virtual ~JMoveAction();
private:
	POINT m_vTargetPos;
};

