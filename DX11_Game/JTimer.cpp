#include "JTimer.h"
#include "JWrite.h"
float g_fSecPerFrame;
DWORD g_dwFPS;
bool JTimer::Init()
{
	QueryPerformanceFrequency(&m_Frequency);
	QueryPerformanceCounter(&m_dwBeforeTick);
	return true;
}
bool JTimer::Frame()
{
	QueryPerformanceCounter(&m_dwCurrentTick);
	m_dwElapseTick = m_dwCurrentTick.QuadPart - m_dwBeforeTick.QuadPart;
	g_fSecPerFrame = m_fSecPerFrame = (float)m_dwElapseTick / (float)m_Frequency.QuadPart;
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
	_stprintf_s(m_szBuffer, L"FPS : %ld     GameTimer : %-10.5f     SecPerFrame : %-10.10f", g_dwFPS, m_fGameTimer, m_fSecPerFrame);
	I_Write.Draw(m_szBuffer, 10);
	return true;
}
bool JTimer::Release()
{
	return true;
}

JTimer::JTimer()
{
	m_dwFPS = 0;
	m_fFrameTime = 0.0f;
	m_dwFrameCnt = 0;
}


JTimer::~JTimer()
{
}
