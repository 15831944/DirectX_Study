#include "JSynchronize.h"



JSynchronize::JSynchronize(JServerObject* pObj) : m_pObject(pObj)
{
	if (pObj != NULL)
	{
		EnterCriticalSection(&pObj->m_cs);
	}
}


JSynchronize::~JSynchronize()
{
	if (m_pObject != NULL)
	{
		LeaveCriticalSection(&m_pObject->m_cs);
	}
}
