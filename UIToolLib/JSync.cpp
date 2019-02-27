#include "JSync.h"

namespace UI
{
	JSync::JSync(JCS* pObj) : m_pCS(pObj)
	{
		if (pObj != NULL)
		{
			EnterCriticalSection(&pObj->m_cs);
		}
	}


	JSync::~JSync()
	{
		if (m_pCS != NULL)
		{
			LeaveCriticalSection(&m_pCS->m_cs);
		}
	}
}