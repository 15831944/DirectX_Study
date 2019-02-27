#pragma once
#include "JEnemy.h"
class JAttackAction : public JEnemyState
{
public:
	virtual void Move() {}
	virtual void Attack() {}
	virtual void Process(JDxObject* ch)
	{

	}
public:
	JAttackAction(JEnemy* parent);
	virtual ~JAttackAction();
};

