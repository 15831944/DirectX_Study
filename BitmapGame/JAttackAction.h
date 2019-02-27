#pragma once
#include "JEnemy.h"
class JAttackAction : public JEnemyState
{
public:
	void Move() {}
	void Attack() {}
	void Process(JPlayer ch);
public:
	JAttackAction(JEnemy* parent);
	virtual ~JAttackAction();
};

