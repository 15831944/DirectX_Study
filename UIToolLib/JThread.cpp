#include "JThread.h"
namespace UI
{
	void JThread::CreateThread()
	{
		if (m_bStarted) return;
		m_hThread = _beginthreadex(NULL, 0, HandleRunner,
			(LPVOID)this, 0, &m_dwThreadID);
		m_bStarted = true;
	}
	bool JThread::Run()
	{
		return true;
	}
	unsigned int WINAPI JThread::HandleRunner(LPVOID parameter)
	{
		JThread* pThread = (JThread*)parameter;
		_ASSERT(pThread);
		pThread->Run();
		return 0;
	}

	JThread::JThread()
	{
		m_bStarted = false;
	}


	JThread::~JThread()
	{
		CloseHandle((HANDLE)m_hThread);
	}
}