#include "JPlayer.h"
#include "JInput.h"
bool JPlayer::Frame()
{
	m_CenterPos.x = m_pos.x + (m_rt.right / 2);
	m_CenterPos.y = m_pos.y + (m_rt.bottom / 2);
	m_rtCollision.left = m_CenterPos.x;
	m_rtCollision.top = m_CenterPos.y;
	m_rtCollision.right = m_rt.right + m_CenterPos.x;
	m_rtCollision.bottom = m_rt.bottom + m_CenterPos.y;
	if (PlayerSpriteList[MOVE].m_bPlay != true && PlayerSpriteList[ATTACK].m_bPlay != true)
	{
		PlayerSpriteList[IDLE].m_bPlay = true;
		PlayerSpriteList[MOVE].m_bPlay = false;
		PlayerSpriteList[ATTACK].m_bPlay = false;
	}
	if(I_Input.KeyCheck('W') == KEY_PUSH || I_Input.KeyCheck('W') == KEY_HOLD)
	{
		Up();
		PlayerSpriteList[MOVE].m_bPlay = true;
		PlayerSpriteList[IDLE].m_bPlay = false;
		PlayerSpriteList[ATTACK].m_bPlay = false;
	}
	if (I_Input.KeyCheck('S') == KEY_PUSH || I_Input.KeyCheck('S') == KEY_HOLD)
	{
		Down();
		PlayerSpriteList[MOVE].m_bPlay = true;
		PlayerSpriteList[IDLE].m_bPlay = false;
		PlayerSpriteList[ATTACK].m_bPlay = false;
	}
	if (I_Input.KeyCheck('A') == KEY_PUSH || I_Input.KeyCheck('A') == KEY_HOLD)
	{
		Left();
		PlayerSpriteList[MOVE].m_bPlay = true;
		PlayerSpriteList[IDLE].m_bPlay = false;
		PlayerSpriteList[ATTACK].m_bPlay = false;
	}
	if (I_Input.KeyCheck('D') == KEY_PUSH || I_Input.KeyCheck('D') == KEY_HOLD)
	{
		Right();
		PlayerSpriteList[MOVE].m_bPlay = true;
		PlayerSpriteList[IDLE].m_bPlay = false;
		PlayerSpriteList[ATTACK].m_bPlay = false;
	}
	if (I_Input.m_dwMouseState[0] == KEY_PUSH)
	{
		Attack();
		PlayerSpriteList[ATTACK].m_bPlay = true;
		PlayerSpriteList[MOVE].m_bPlay = false;
		PlayerSpriteList[IDLE].m_bPlay = false;
	}
	return true;
}
void JPlayer::Left()
{
	if (m_pos.x >= g_rtWindow.left)
		m_pos.x -= g_fSecPerFrame * m_fSpeed;
}
void JPlayer::Right()
{
	if (m_pos.x <= g_rtWindow.right - 50)
		m_pos.x += g_fSecPerFrame * m_fSpeed;
}
void JPlayer::Up()
{
	if (m_pos.y >= 220)//g_rtWindow.top)
		m_pos.y -= g_fSecPerFrame * m_fSpeed;
}
void JPlayer::Down()
{
	if (m_pos.y <= g_rtWindow.bottom - 50)
		m_pos.y += g_fSecPerFrame * m_fSpeed;
}
bool JPlayer::Attack()
{
	return true;
}

JPlayer::JPlayer()
{
	m_iPlayerState = IDLE;
	m_fPower = 100.0f;
	m_fSpeed = 300.0f;
	m_fHp = 100.0f;
}


JPlayer::~JPlayer()
{
}
