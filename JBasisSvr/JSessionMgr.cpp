#include "JSessionMgr.h"
#include "JDebugLog.h"
bool JSessionMgr::BroadCast(UPACKET packet)
{
	list<JSession*>::iterator ITOR;
	for (ITOR = m_SessionList.begin(); ITOR != m_SessionList.end(); ITOR++)
	{
		JSession* pSession = *ITOR;
		send(pSession->m_Sock, (char*)&packet, packet.ph.len, 0);
	}
	C_STR msg = "BroadCast("; msg +=packet.msg; msg.pop_back();  msg += ")";
	I_Debug.PushError(msg);
	return true;
}
bool JSessionMgr::AddUser(JSession* pUser)
{
	{
		JSynchronize sync(this);
		m_SessionList.push_back(pUser);
	}
	return true;
}
bool  JSessionMgr::DelUser(JSession* pUser)
{
	{
		JSynchronize sync(this);
		list<JSession*>::iterator ITOR;
		list<JSession*>::iterator DelSessITOR;
		JSession* pDelSess = 0;
		for (ITOR = m_SessionList.begin(); ITOR != m_SessionList.end(); ITOR++)
		{
			pDelSess = (JSession*)*ITOR;
			if (pDelSess == pUser)
			{
				pDelSess->Release();
				DelSessITOR = ITOR;
				C_STR msg = "Session Leave(Port : "; msg += to_string(pUser->m_Addr.sin_port); msg += ")";
				break;
			}
		}
		delete pDelSess;
		m_SessionList.erase(DelSessITOR);
	}
	return true;
}

JSessionMgr::JSessionMgr()
{
}


JSessionMgr::~JSessionMgr()
{
}
