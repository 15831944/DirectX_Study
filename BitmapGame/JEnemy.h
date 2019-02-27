#pragma once
#include "JFiniteStateMachine.h"
#include "JSprite.h"
#include "JPlayer.h"

enum EnemyState  {ENEMY_ATTACK = 0, ENEMY_MOVE, ENEMY_DIE};
class JEnemy;
class JEnemyState
{
public:
	JEnemyState(JEnemy* parent) : m_pOwner(parent) {}
	virtual ~JEnemyState() {}
public:
	virtual void Move() = 0;
	virtual void Attack() = 0;
	virtual void Process(JPlayer ch) = 0;
protected:
	JEnemy * m_pOwner;
};

class JEnemy : public JSprite
{
private:
	JEnemyState* m_pAction;
	JEnemyState* m_pActionList[STATE_COUNT];
	JFiniteStateMachine* m_pFSM;
	DWORD m_dwCurrentState;
public:
	vector<JSprite> EnemySpriteList;
public:
	DWORD m_EnemyState;
	bool m_bDie;
	float m_fCreateTime;
	float m_fRandTime;
	bool m_bCreate;
public:
	void Process(JPlayer target);
	DWORD GetState();
	void SetTransition(DWORD Event);
	void Move(int x, int y);
	void FSM(int iIndex);
	bool Frame();
public:
	JEnemy();
	virtual ~JEnemy();
};