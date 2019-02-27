#pragma once
#include "JStd.h"
enum KeyState { KEY_FREE = 0, KEY_PUSH, KEY_UP, KEY_HOLD };
class JInput : public JSingleton<JInput>
{
public:
	friend class JSingleton<JInput>;
public:
	DWORD m_dwKeyState[256];
	DWORD m_dwMouseState[3];
	DWORD m_dwBeforeMouseState[3];
	POINT m_MousePos;
	TCHAR m_szBuffer[256];
public:
	void MsgEvent(MSG msg);
	DWORD KeyCheck(DWORD dwKey);
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	JInput();
	virtual ~JInput();
};
#define I_Input JInput::GetInstance()
