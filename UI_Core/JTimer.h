#pragma once
#include "JStd.h"
class JTimer : public JSingleton<JTimer>
{
public:
	friend class JSingleton<JTimer>;
public:
	TCHAR m_szBuffer[256];
public:
	DWORD m_dwFPS;
	float m_fSecPerFrame;
	float m_fGameTimer;
	float m_fFrameTime;
	LARGE_INTEGER m_Frequency;
	DWORD m_Hour, m_Minute, m_Second;
public:
	DWORD m_dwFrameCnt;
	LARGE_INTEGER m_dwBeforeTick;
	LARGE_INTEGER m_dwCurrentTick;
	LONGLONG m_dwElapseTick;
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	JTimer();
	virtual ~JTimer();
};
#define I_Timer JTimer::GetInstance()
