#pragma once
#include "JThread.h"
class JWorkThread : public JThread
{
public:
	bool Run();
	bool Release();
public:
	JWorkThread();
	virtual ~JWorkThread();
};

