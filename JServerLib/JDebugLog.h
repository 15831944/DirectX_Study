#pragma once
#include "JThread.h"
class JDebugLog : public JThread, public JSingleton<JDebugLog>
{
private:
	friend class JSingleton<JDebugLog>;
public:
	T_STR_VECTOR m_ErrorList;
public:
	bool Run();
	void PushError();
	void PushError(T_STR msg);
	void PushError(C_STR msg);
	void PushError(int iCode);
public:
	JDebugLog();
	virtual ~JDebugLog();
};
#define I_Debug JDebugLog::GetInstance()