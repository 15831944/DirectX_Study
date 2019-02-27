#pragma once
#include "JDxObject.h"
#include "JFiniteStateMachine.h"
class JEnemy;

class JEnemyState
{
public:
	JEnemyState(JEnemy* parent) : m_pOwner(parent){}
	virtual ~JEnemyState() {}
public:
	virtual void Move() = 0;
	virtual void Attack() = 0;
	virtual void Process(JDxObject* ch) = 0;
protected:
	JEnemy * m_pOwner;
};
class JEnemy : public JDxObject
{
private:
	JEnemyState * m_pAction;
	JEnemyState* m_pActionList[STATE_COUNT];
	JFiniteStateMachine* m_pFSM;
	DWORD m_dwCurrentState;
public:
	virtual void Process(JDxObject* target);
	DWORD GetState();
	void SetTransition(DWORD Event);
	void Move(int x, int y);
	void FSM(int iIndex);
	bool Frame();
public:
	JEnemy();
	virtual ~JEnemy();
};