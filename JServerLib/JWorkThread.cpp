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
			// ��������
			pUser->Dispatch(dwTransfer, ov);
		}
		else
		{
			// �������� Recv�� �������� ���¿��� Send�� �ϸ� Recv ������ΰ� ��ҵ� ( Recv, Send �����۾����� )
			if (GetLastError() != ERROR_OPERATION_ABORTED) // Send, Recv  �����۾����϶� ::ERROR_OPERATION_ABORTED
			{
				if (dwTransfer == 0 && KeyValue != NULL) // ��������
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
