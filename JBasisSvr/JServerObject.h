#pragma once
#include "JServerStd.h"
class JServerObject
{
public:
	CRITICAL_SECTION m_cs;
public:
	JServerObject();
	virtual ~JServerObject();
};

