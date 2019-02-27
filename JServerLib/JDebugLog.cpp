#include "JDebugLog.h"
void JDebugLog::PushError()
{
	PushError(WSAGetLastError());
}
void JDebugLog::PushError(int iCode)
{
	T_STR msg;
	switch (iCode)
	{
	case WSAEADDRINUSE://ip,port 사용중일때
	{
		msg += _T("WSAEADDRINUSE");
	}break;
	case WSAEACCES: // 접근권한
	{
		msg += _T("WSAEACCES");
	}break;
	}

	{
		JSynchronize sync(this);
		LPVOID lpMsg;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, iCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (TCHAR*)&lpMsg, 0, NULL);//할당
		msg += (TCHAR*)&lpMsg;
		m_ErrorList.push_back(msg);
		LocalFree(lpMsg);
	}
}
void JDebugLog::PushError(T_STR msg)
{
	{
		JSynchronize sync(this);
		m_ErrorList.push_back(msg);
	}
}
void JDebugLog::PushError(C_STR msg)
{
	{
		JSynchronize sync(this);
		m_ErrorList.push_back(mtow(msg));
	}
}
bool JDebugLog::Run()
{
	while (TRUE)
	{
		{
			JSynchronize sync(this);
			for (int i = 0; i < m_ErrorList.size(); i++)
			{
				wcout << m_ErrorList[i].c_str() << endl;
			}
			m_ErrorList.clear();
		}
		Sleep(100);
	}
}
JDebugLog::JDebugLog()
{
	CreateThread();
}


JDebugLog::~JDebugLog()
{
}
