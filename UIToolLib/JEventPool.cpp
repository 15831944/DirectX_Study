#include "JEventPool.h"
namespace UI
{
	bool JEventPool::Run()
	{
		while (TRUE)
		{
			if (m_pEventList.size() > 0)
			{
				JEvent* pEvent = m_pEventList.front();
				pEvent->EventPlay(*pEvent);
				m_pEventList.pop();

			}
		}
	}
	void JEventPool::push_event(JEvent* pEvent)//JEventHandle* pEvent)
	{
		m_pEventList.push(pEvent);
	}

	JEventPool::JEventPool()
	{
		CreateThread();
	}


	JEventPool::~JEventPool()
	{
	}
}