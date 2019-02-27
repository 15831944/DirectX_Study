#include "JDebugLog.h"
void JDebugLog::PushError()
{
	PushError(WSAGetLastError());
}
void JDebugLog::PushError(int iCode)
{
	C_STR msg;
	switch (iCode)
	{
	case WSAEADDRINUSE:
	{
		msg += "WSAEADDRINUSE";
		I_Debug.PushError(msg);
	}break;
	case WSAEACCES:
	{
		msg += "WSAEACCES"; 
		I_Debug.PushError(msg);
	}break;
	}

	{
		JSynchronize sync(this);
		LPVOID lpMsg;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, iCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (TCHAR*)&lpMsg, 0, NULL);
		msg += (CHAR*)&lpMsg;
		m_ErrorList.push_back(msg);
		LocalFree(lpMsg);
	}
}
void JDebugLog::PushError(T_STR msg)
{
	{
		JSynchronize sync(this);
		m_ErrorList.push_back(wtom(msg));
	}
}
void JDebugLog::PushError(C_STR msg)
{
	{
		JSynchronize sync(this);
		m_ErrorList.push_back(msg);
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
				cout << m_ErrorList[i] << endl;
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
