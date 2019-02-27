#pragma once
#include "JSynchronize.h"
class JThread : public JServerObject
{
public:
	unsigned int m_hThread;
	unsigned int m_dwThreadID;
	bool		 m_bStarted;
public:
	void CreateThread();
	virtual bool Run();
	static unsigned int WINAPI HandleRunner(LPVOID parameter);
public:
	JThread();
	virtual ~JThread();
};