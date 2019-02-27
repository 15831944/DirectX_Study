#pragma once
#include "JFiniteState.h"
class JFiniteStateMachine
{
private:
	map<DWORD, JFiniteState*> m_MapState;
public:
	wstring m_szName;
	int m_iIndex;
public:
	void AddStateTransition(DWORD dwState, DWORD inputEvnet, DWORD outputStateID);
	void DeleteTransition(DWORD dwState, DWORD inputEvent);
	DWORD GetOutputState(DWORD inputEvent);
	DWORD GetCurrentStateID(DWORD Output);
	DWORD StateTransition(DWORD dwCurrent, int Event);
	bool Release();
public:
	JFiniteStateMachine();
	virtual ~JFiniteStateMachine();
};
class JFSMMgr : public JSingleton<JFSMMgr>
{
private:
	friend class JSingleton<JFSMMgr>;
public:
	typedef map<int, JFiniteStateMachine*> TemplateMap;
	typedef TemplateMap::iterator TemplateMapITOR;
	TemplateMap JMap;
	TemplateMapITOR JITOR;
	int m_iCurrentIndex;
public:
	bool Init();
	int Add(const TCHAR* szFileName);
	JFiniteStateMachine* GetPtr(int iIndex);
	bool Release();
	bool Delete();
public:
	JFSMMgr();
	virtual ~JFSMMgr();
};
#define I_FSM JSingleton<JFSMMgr>::GetInstance()