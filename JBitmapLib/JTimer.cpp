#include "JTimer.h"
float g_fSecPerFrame;
DWORD g_dwFPS;
bool JTimer::Init()
{
	m_dwBeforeTick = timeGetTime();
	return true;
}
bool JTimer::Frame()
{
	DWORD m_dwCurrentTick = timeGetTime();
	DWORD m_dwElapseTick = m_dwCurrentTick - m_dwBeforeTick;
	g_fSecPerFrame = m_fSecPerFrame = m_dwElapseTick / 1000.0f;
	m_fGameTimer += m_fSecPerFrame;
	m_fFrameTime += m_fSecPerFrame;
	if (m_fFrameTime > 1.0f)
	{
		m_dwFPS = m_dwFrameCnt;
		m_dwFrameCnt = 0;
		m_fFrameTime = -1.0f;
	}
	m_dwFrameCnt++;
	m_dwBeforeTick = m_dwCurrentTick;
	g_dwFPS = m_dwFPS;
	return true;
}
bool JTimer::Render()
{
	_stprintf_s(m_szBuffer, L"FPS : %ld     GameTimer : %-10.5f     SecPerFrame : %-10.5f", g_dwFPS, m_fGameTimer, m_fSecPerFrame);
	return true;
}
bool JTimer::Release()
{
	return true;
}

JTimer::JTimer()
{
	m_dwFPS = 0;
	m_fSecPerFrame = 0.0f;
	m_fGameTimer = 0.0f;
	m_fFrameTime = 0.0f;
	m_dwFrameCnt = 0;
	m_dwBeforeTick = 0;
}


JTimer::~JTimer()
{
}
