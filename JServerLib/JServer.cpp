#include "JServer.h"
bool JServer::Init()
{
	m_hKillEvent = CreateEvent(NULL, FALSE, FALSE, _T("JServer"));
	m_Acceptor.Init();
	CreateThread();
	return true;
}
void JServer::Finish()
{
	WaitForSingleObject(m_hKillEvent, INFINITE);
}
bool JServer::Release()
{
	m_Acceptor.Release();
	SetEvent(m_hKillEvent);
	return true;
}
bool JServer::Set(int iPort, const char* strAddr)
{
	Init();
	return m_Acceptor.Set(iPort, strAddr);
}

JServer::JServer()
{
}


JServer::~JServer()
{
}
