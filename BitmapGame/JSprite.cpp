#include "JSprite.h"

bool JSprite::Frame()
{
	SetUp(0.5f);
	Update();
	return true;
}
bool JSprite::Render()
{
	if (!m_bPlay) return false;
	if (m_bBitmapMask == false)
	{
		m_pBitmap->Draw(g_hOffScreenDC, m_pos, m_rtEffect[m_iStart], SRCCOPY);
	}
	if (m_bBitmapMask == true)
	{

		m_pBitmapMask->Draw(g_hOffScreenDC, m_pos, m_rtEffect[m_iStart], SRCAND);
		m_pBitmap->Draw(g_hOffScreenDC, m_pos, m_rtEffect[m_iStart], SRCINVERT);
		m_pBitmapMask->Draw(g_hOffScreenDC, m_pos, m_rtEffect[m_iStart], SRCINVERT);
	}
	return true;
}
void JSprite::SetUp(float fSec)
{
	m_fFrameUpdateSec = fSec / m_iMax;
}
void JSprite::Update()
{
	if (!m_bPlay) return;
	m_fFrameElapseSec += g_fSecPerFrame;
	if (m_fFrameElapseSec >= m_fFrameUpdateSec)
	{
		if (m_iStart++ >= m_iMax - 1)
		{
			m_iStart = 0;
			m_bPlay = false;
		}
		m_fFrameElapseSec = 0.0f;
	}
}
JSprite::JSprite()
{
	m_iStart = 0;
	m_iMax = 0;
	m_fFrameUpdateSec = 1.0f;
	m_fFrameElapseSec = 0.0f;
	m_bPlay = false;
	m_bLoop = true;
}

JSprite::~JSprite()
{

}
