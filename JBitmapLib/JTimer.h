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
public:
	DWORD m_dwFrameCnt;
	DWORD m_dwBeforeTick;
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
