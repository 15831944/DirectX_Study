#pragma once
#include "JStd.h"
#include <functional>
enum State 
{ 
	STATE_STAND = 0, 
	STATE_MOVE,
	STATE_ATTACK,
	STATE_RUNAWAY,
	STATE_COUNT
};
enum Event
{
	EVENT_FINDTARGET = 0,
	EVENT_LOSTTARGET,
	EVENT_BEATTACKED,
	EVENT_HEALTHDRYUP,
	EVENT_STOPWALK,
	EVENT_PATROL
};
class JFiniteStateMachine;

class JFiniteState
{
private:
	friend class JFiniteStateMachine;
private:
	DWORD m_dwState;
	map<DWORD, DWORD> m_Map;
private:
	DWORD GetState();
	void AddTransition(DWORD inputEvent, DWORD outputStateID);
	void DeleteTransition(DWORD inputEvent);
	DWORD Output(DWORD inputEvent);
	DWORD GetCount();
public:
	JFiniteState(DWORD State);
	virtual ~JFiniteState();
};

