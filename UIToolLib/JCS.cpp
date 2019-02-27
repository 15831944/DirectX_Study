#include "JCS.h"
namespace UI
{
	JCS::JCS()
	{
		InitializeCriticalSection(&m_cs);
	}


	JCS::~JCS()
	{
		DeleteCriticalSection(&m_cs);
	}

}