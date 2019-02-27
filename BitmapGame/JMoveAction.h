#pragma once
#include "JEnemy.h"
class JMoveAction : public JEnemyState
{
public:
	float m_fTime;
public:
	void Move();
	void Attack();
	void Process(JPlayer ch);
public:
	JMoveAction(JEnemy* parent);
	virtual ~JMoveAction();
private:
	POINT m_vTargetPos;
};

