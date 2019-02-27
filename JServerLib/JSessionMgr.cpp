#include "JSessionMgr.h"
bool JSessionMgr::AddUser(JUser* pUser)
{
	{
		JSynchronize sync(this);
		m_UserList.push_back(pUser);
	}
	return true;
}
bool  JSessionMgr::DelUser(JUser* pUser)
{
	{
		JSynchronize sync(this);
		list<JUser*>::iterator ITOR;
		list<JUser*>::iterator DelUserITOR;
		JUser* pDelUser = 0;
		for (ITOR = m_UserList.begin(); ITOR != m_UserList.end(); ITOR++)
		{
			pDelUser = (JUser*)*ITOR;
			if (pDelUser == pUser)
			{
				pDelUser->Release();
				DelUserITOR = ITOR;
				break;
			}
		}
		delete pDelUser;
		m_UserList.erase(DelUserITOR);
	}
	return true;
}

JSessionMgr::JSessionMgr()
{
}


JSessionMgr::~JSessionMgr()
{
}
