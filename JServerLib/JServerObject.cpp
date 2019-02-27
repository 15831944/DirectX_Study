#include "JServerObject.h"



JServerObject::JServerObject()
{
	InitializeCriticalSection(&m_cs);
}


JServerObject::~JServerObject()
{
	DeleteCriticalSection(&m_cs);
}
