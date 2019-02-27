#pragma once
#include "JServer.h"
class JSessionMgr : public JServer, public JSingleton<JSessionMgr>
{
private:
	friend class JSingleton<JSessionMgr>;
public:
	list<JSession*> m_SessionList;
public:
	virtual bool AddUser(JSession* pUser);
	virtual bool DelUser(JSession* pUser);
	bool BroadCast(UPACKET packet);
public:
	JSessionMgr();
	virtual ~JSessionMgr();
};
#define I_Session JSessionMgr::GetInstance()