#pragma once
#include "JDxSprite.h"
#include "JDxArrow.h"
enum PlayerState { IDLE = 0, MOVE, ATTACK };
class JDxPlayer : public JDxSprite
{
public:
	vector<JDxSprite> PlayerSpriteList;
	JDxArrow Arrow;
	int m_iPlayerState;
public:
	float m_fPower;
	float m_fHp;
	float m_fSpeed;
	float m_fDamage;
public:
	bool Init();
	bool Frame(ID3D11DeviceContext* context, fRECT EnemyRT);
	bool Render(ID3D11DeviceContext* context);
	bool Release();
public:
	bool SetPos(fRECT rt);
	bool Attack();
	void Up();
	void Down();
	void Left();
	void Right();
	bool DataLoad(const TCHAR* pszLoadFile);
public:
	JDxPlayer();
	virtual ~JDxPlayer();
};