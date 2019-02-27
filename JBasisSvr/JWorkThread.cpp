#include "JWorkThread.h"
#include "JSvrIOCP.h"
#include "JSessionMgr.h"
#include "JDebugLog.h"
bool JWorkThread::Run()
{
	BOOL bRet;
	ULONG_PTR KeyValue;
	LPOVERLAPPED ov;
	DWORD dwTransfer;

	while (m_bStarted)
	{
		bRet = GetQueuedCompletionStatus(I_IOCP.m_hIOCP, &dwTransfer, &KeyValue, &ov, INFINITE);
		JSession* pSess = (JSession*)KeyValue;

		if (bRet == TRUE)
		{
			if (dwTransfer != 0)
			{
				if (ov != NULL && pSess != NULL)
				{
					pSess->Dispatch(dwTransfer, ov);
				}
			}
			else
			{
				I_Session.DelUser(pSess);
			}
		}
		else
		{
			if (GetLastError() != ERROR_OPERATION_ABORTED)
			{
				if (dwTransfer == 0 && KeyValue != NULL)
				{
					I_Session.DelUser(pSess);
					continue;
				}
			}
			I_Debug.PushError();
		}
	}
	return true;
}
bool JWorkThread::Release()
{
	return true;
}
JWorkThread::JWorkThread()
{
}


JWorkThread::~JWorkThread()
{
}
