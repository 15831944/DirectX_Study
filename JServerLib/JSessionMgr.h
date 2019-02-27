#pragma once
#include "JServer.h"
class JSessionMgr : public JServer, public JSingleton<JSessionMgr>
{
private:
	friend class JSingleton<JSessionMgr>;
public:
	list<JUser*> m_UserList; // = m_SessionList :: Server와 Server -> Server가 유저가됨
public:
	virtual bool AddUser(JUser* pUser);
	virtual bool DelUser(JUser* pUser);
public:
	JSessionMgr();
	virtual ~JSessionMgr();
};
#define I_Session JSessionMgr::GetInstance()