#pragma once
#include "JEnemy.h"
class JStandAction : public JEnemyState
{
public:
	virtual void Move();
	virtual void Attack();
	virtual void Process(JDxObject* ch);
public:
	JStandAction(JEnemy* parent);
	virtual ~JStandAction();
};

