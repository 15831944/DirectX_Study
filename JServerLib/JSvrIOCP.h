#pragma once
#include "JWorkThread.h"
#define WORKER_THREAD_COUNT 3
class JSvrIOCP : public JSingleton<JSvrIOCP>, public JServerObject
{
private:
	friend class JSingleton<JSvrIOCP>;
public:
	HANDLE m_hIOCP;
	JWorkThread m_WorkThread[WORKER_THREAD_COUNT];
public:
	bool Init();
	bool Release();
	void Bind(HANDLE hSock, ULONG_PTR pKey); // DWORD넘기면 64비트에서안돌아감
public:
	JSvrIOCP();
	virtual ~JSvrIOCP();
};
#define I_IOCP  JSvrIOCP::GetInstance()