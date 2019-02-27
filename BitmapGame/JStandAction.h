#pragma once
#include "JEnemy.h"
class JStandAction : public JEnemyState
{
public:
	void Move();
	void Attack();
	void Process(JPlayer ch);
public:
	JStandAction(JEnemy* parent);
	virtual ~JStandAction();
};

