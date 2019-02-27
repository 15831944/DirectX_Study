#include "JSvrIOCP.h"
#include "JUser.h"
bool JSvrIOCP::Init()
{
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, WORKER_THREAD_COUNT);
	for (int iThread = 0; iThread < WORKER_THREAD_COUNT; iThread++)
	{
		m_WorkThread[iThread].CreateThread();
	}
	return true;
}

bool JSvrIOCP::Release()
{
	return true;
}
void JSvrIOCP::Bind(HANDLE hSock, ULONG_PTR pKey)
{
	CreateIoCompletionPort(hSock, m_hIOCP, pKey, 0);
	JUser* pUser = (JUser*)pKey;
	pUser->WaitForPacketRecv();
}

JSvrIOCP::JSvrIOCP()
{
}


JSvrIOCP::~JSvrIOCP()
{
}
