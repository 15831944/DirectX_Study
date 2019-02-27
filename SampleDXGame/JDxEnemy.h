#pragma once
#include "JDxSprite.h"
#include "JDxPlayer.h"
#include "JDxEffect.h"
enum EnemyState { ENEMY_MOVE = 0, ENEMY_ATTACK, ENEMY_DIE };
class JDxEnemy : public JDxSprite
{
public:
	vector<JDxSprite> EnemySpriteList;
	JDxEffect m_Effect;
	int m_iEnemyDieCnt;
	int m_iMiniStageCnt;
public:
	DWORD m_EnemyState;
	bool m_bDie;
	float m_fCreateTime;
	float m_fRandTime;
	bool m_bCreate;
	float m_fCurrentHp;
	float m_fNextHp;
public:
	void Move();
	void Attack();
	bool SetPos(fRECT rt);
	bool DataLoad(const TCHAR* pszLoadFile);
public:
	bool Init();
	bool Frame(ID3D11DeviceContext* context, JDxPlayer Player);
	bool Render(ID3D11DeviceContext* context);
	bool Release();
	//bool Render();
public:
	JDxEnemy();
	virtual ~JDxEnemy();
};