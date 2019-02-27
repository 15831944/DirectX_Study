#pragma once
#include "JServer.h"
class JSessionMgr : public JServer, public JSingleton<JSessionMgr>
{
private:
	friend class JSingleton<JSessionMgr>;
public:
	list<JUser*> m_UserList; // = m_SessionList :: Server�� Server -> Server�� ��������
public:
	virtual bool AddUser(JUser* pUser);
	virtual bool DelUser(JUser* pUser);
public:
	JSessionMgr();
	virtual ~JSessionMgr();
};
#define I_Session JSessionMgr::GetInstance()