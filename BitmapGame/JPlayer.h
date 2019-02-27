#pragma once
#include "JSprite.h"
enum PlayerState { IDLE = 0, MOVE, ATTACK };
class JPlayer : public JSprite
{
public:
	vector<JSprite> PlayerSpriteList;
	int m_iPlayerState;
public:
	float m_fPower;
	float m_fHp;
public:
	bool Frame();
public:
	bool Attack();
	void Up();
	void Down();
	void Left();
	void Right();
public:
	JPlayer();
	virtual ~JPlayer();
};

