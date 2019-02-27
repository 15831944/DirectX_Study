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
		JUser* pUser = (JUser*)KeyValue;
		
		if (bRet == TRUE && dwTransfer != 0 && ov != NULL && pUser != NULL)
		{
			// 정상적임
			pUser->Dispatch(dwTransfer, ov);
		}
		else
		{
			// 소켓으로 Recv로 수신중인 상태에서 Send를 하면 Recv 대기중인게 취소됨 ( Recv, Send 동시작업못함 )
			if (GetLastError() != ERROR_OPERATION_ABORTED) // Send, Recv  동시작업중일때 ::ERROR_OPERATION_ABORTED
			{
				if (dwTransfer == 0 && KeyValue != NULL) // 유저나감
				{
					I_Session.DelUser(pUser);
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
