#include "JFiniteStateMachine.h"

InvalidCurrentStateException::InvalidCurrentStateException(int CurrentStateID) : m_iCurrentStateID(CurrentStateID)
{

}
InvalidCurrentStateException::~InvalidCurrentStateException()
{

}
InvalidInputEventException::InvalidInputEventException(int Evnet) : m_iInputEvent(Evnet)
{

}
InvalidInputEventException::~InvalidInputEventException()
{

}
//JFiniteStateMachine
void JFiniteStateMachine::AddStateTransition(DWORD dwState, DWORD inputEvnet, DWORD outputStateID)
{
	map<DWORD, JFiniteState*>::iterator ITOR;
	JFiniteState* state = NULL;

	// 같은 state가 이미 존재하는지 찾음
	ITOR = m_MapState.begin();
	while (ITOR != m_MapState.end())
	{
		state = ITOR->second;
		if (state->GetState() == dwState) break;
		ITOR++;
	}

	// 같은 state가 없으면 새로 생성
	if (ITOR == m_MapState.end())
	{
		state = new JFiniteState(dwState);
		m_MapState[state->GetState()] = state;
	}
	// 상태 추가
	if (state != NULL)
	{
		state->AddTransition(inputEvnet, outputStateID);
	}
}
void JFiniteStateMachine::DeleteTransition(DWORD dwState, DWORD inputEvent)
{
	map<DWORD, JFiniteState*>::iterator ITOR, ITORPREV;
	JFiniteState* state = NULL;
	// 해당 state 찾기
	ITOR = m_MapState.begin();
	while (ITOR != m_MapState.end())
	{
		ITORPREV = ITOR;
		state = ITOR->second;
		if (state->GetState() == dwState) break;
		ITOR++;
	}
	if (ITOR == m_MapState.end()) return;
	// state 상태 지움
	if (state != NULL)
	{
		state->DeleteTransition(inputEvent);
	}
	if (state->GetCount() == 0)
	{
		delete state;
		m_MapState.erase(ITORPREV);
	}
}
DWORD JFiniteStateMachine::GetOutputState(DWORD inputEvent)
{
	map<DWORD, JFiniteState*>::iterator ITOR;

	// 존재하지않는 State를 입력받앗으면 익셉션 발생
	ITOR = m_MapState.find(inputEvent);
	if(ITOR == m_MapState.end())
		throw (new InvalidCurrentStateException(inputEvent));
	JFiniteState* state = m_MapState[inputEvent];
	if(state == NULL)
		throw (new InvalidCurrentStateException(inputEvent));
	return state->Output(inputEvent);
}
DWORD JFiniteStateMachine::GetCurrentStateID(DWORD Output)
{
	JFiniteState* CurrentState = m_MapState[Output];
	return CurrentState->GetState();
}
DWORD JFiniteStateMachine::StateTransition(DWORD dwCurrent, int Event)
{
	DWORD Output;
	try
	{
		Output = m_MapState[dwCurrent]->Output(Event);
	}
	catch (InvalidInputEventException* ex)
	{
		delete ex;
		return -1;
	}
	return Output;
}
bool JFiniteStateMachine::Load(const TCHAR* szFileName)
{
	return true;
}
bool JFiniteStateMachine::Release()
{
	map<DWORD, JFiniteState*>::iterator ITOR, ITORPREV;
	ITOR = m_MapState.begin();
	while (ITOR != m_MapState.end())
	{
		ITORPREV = ITOR++;
		delete ITORPREV->second;
		m_MapState.erase(ITORPREV);
	}
	return false;
}
JFiniteStateMachine::JFiniteStateMachine()
{
}


JFiniteStateMachine::~JFiniteStateMachine()
{
	Release();
}
// FSMMgr
bool JFSMMgr::Init()
{
	JFiniteStateMachine* pPoint = new JFiniteStateMachine();
	pPoint->AddStateTransition(STATE_STAND, EVENT_FINDTARGET, STATE_ATTACK);
	pPoint->AddStateTransition(STATE_STAND, EVENT_BEATTACKED, STATE_ATTACK);
	pPoint->AddStateTransition(STATE_STAND, EVENT_PATROL, STATE_MOVE);

	pPoint->AddStateTransition(STATE_MOVE, EVENT_FINDTARGET, STATE_ATTACK);
	pPoint->AddStateTransition(STATE_MOVE, EVENT_STOPWALK, STATE_STAND);

	pPoint->AddStateTransition(STATE_ATTACK, EVENT_LOSTTARGET, STATE_STAND);
	pPoint->AddStateTransition(STATE_ATTACK, EVENT_HEALTHDRYUP, STATE_RUNAWAY);

	pPoint->AddStateTransition(STATE_RUNAWAY, EVENT_LOSTTARGET, STATE_STAND);

	pPoint->m_szName = _T("DefaultEnemy");
	JMap.insert(make_pair(++m_iCurrentIndex, pPoint));
	pPoint->m_iIndex = m_iCurrentIndex;
	return true;
}
int JFSMMgr::Add(const TCHAR* szLoadFileName)
{
	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR Name[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	
	// 기본 유한상태기기를 사용
	if (szLoadFileName == NULL)
	{
		szLoadFileName = _T("DefaultEnemy");
	}

	if (szLoadFileName)
	{
		_tsplitpath_s(szLoadFileName, Drive, Dir, Name, Ext);
		Ext[4] = 0;
		memset(szFileName, 0, sizeof(TCHAR) * MAX_PATH);
		_stprintf_s(szFileName, _T("%s%s"), Name, Ext);
		for (TemplateMapITOR ITOR = JMap.begin(); ITOR != JMap.end(); ITOR++)
		{
			JFiniteStateMachine* pPoint = (JFiniteStateMachine*)(*ITOR).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szFileName))
			{
				return (*ITOR).first;
			}
		}
	}
	JFiniteStateMachine* pPoint = new JFiniteStateMachine;
	// 파일에 저장되어있는 유한상태기기를 사용
	if (!pPoint->Load(szLoadFileName))
	{
		if (pPoint)
		{
			delete pPoint;
			pPoint = NULL;
		}
		return 1;
	}
	pPoint->m_szName = szFileName;
	JMap.insert(make_pair(++m_iCurrentIndex, pPoint));
	pPoint->m_iIndex = m_iCurrentIndex;
	return m_iCurrentIndex;
}
JFiniteStateMachine* JFSMMgr::GetPtr(int iIndex)
{
	TemplateMapITOR ITOR = JMap.find(iIndex);
	if (ITOR == JMap.end()) return NULL;
	JFiniteStateMachine* pPoint = (*ITOR).second;
	return pPoint;
}
bool JFSMMgr::Release()
{
	JFiniteStateMachine* pPoint;
	for (TemplateMapITOR ITOR = JMap.begin(); ITOR != JMap.end(); ITOR++)
	{
		pPoint = (JFiniteStateMachine*)(*ITOR).second;
		pPoint->Release();
		if (pPoint)
		{
			delete pPoint;
			pPoint = NULL;
		}
	}
	JMap.clear();
	m_iCurrentIndex = 0;
	return true;
}
bool JFSMMgr::Delete()
{
	return true;
}
JFSMMgr::JFSMMgr()
{

}
JFSMMgr::~JFSMMgr()
{

}