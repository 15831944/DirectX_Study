#include "JFiniteState.h"

DWORD JFiniteState::GetState()
{
	return m_dwState;
}
void JFiniteState::AddTransition(DWORD inputEvent, DWORD outputStateID)
{
	m_Map[inputEvent] = outputStateID;
}
void JFiniteState::DeleteTransition(DWORD inputEvent)
{
	m_Map.erase(inputEvent);
}
DWORD JFiniteState::Output(DWORD inputEvent) //throw (InvalidInputEventException*)
{
	map<DWORD, DWORD>::iterator ITOR;
	ITOR = m_Map.find(inputEvent);
	if (ITOR == m_Map.end())
	{
		//throw(new InvalidInputEventException(inputEvent));
	}
	return m_Map[inputEvent];
}
DWORD JFiniteState::GetCount()
{
	return m_Map.size();
}

JFiniteState::JFiniteState(DWORD State) : m_dwState(State) {}


JFiniteState::~JFiniteState()
{
	map<DWORD, DWORD>::iterator ITOR, ITORPREV;
	ITOR = m_Map.begin();
	while (ITOR != m_Map.end())
	{
		ITORPREV = ITOR++;
		m_Map.erase(ITORPREV);
	}
}
