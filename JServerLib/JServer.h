#pragma once
#include "JAcceptor.h"
class JServer : public JThread
{
public:
	JAcceptor m_Acceptor;
	HANDLE m_hKillEvent;
public:
	virtual bool Init();
	virtual bool Release();
	virtual bool Set(int iPort, const char* strAddr = 0);
	virtual void Finish();
public:
	JServer();
	virtual ~JServer();
};
