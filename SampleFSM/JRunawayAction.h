#pragma once
#include "JEnemy.h"
class JRunawayAction : public JEnemyState
{
public:
	virtual void Move();
	virtual void Attack();
	virtual void Process(JDxObject* ch);
public:
	JRunawayAction(JEnemy* parent);
	virtual ~JRunawayAction();
};

