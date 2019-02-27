#pragma once
#include "JThread.h"
#include "JSession.h"
class JAcceptor : public JThread
{
public:
	SOCKET m_ListenSocket;
public:
	bool Run();
public:
	bool SetSockOpt();
	bool Init();
	bool Set(int port, const char* address = 0);
	bool Frame();
	bool Release();
	virtual void AddUser(SOCKET sock, SOCKADDR_IN addr) {}
public:
	JAcceptor();
	virtual ~JAcceptor();
};

