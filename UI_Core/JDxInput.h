#pragma once
#include "JStd.h"

class JDxInput : public JSingleton<JDxInput>
{
private:
	friend class JSingleton<JDxInput>;
public:
	LPDIRECTINPUT8 m_pDi;
	LPDIRECTINPUTDEVICE8 m_pDidevKey;
	LPDIRECTINPUTDEVICE8 m_pDidevMouse;
	DIDEVICEOBJECTDATA   m_didod[SAMPLE_BUFFER_SIZE];

	BYTE m_KeyState[KEYSTATECOUNT];
	BYTE m_KeyBeforeState[KEYSTATECOUNT];
	DIMOUSESTATE m_MouseState;
	DIMOUSESTATE m_MouseBeforeState;
	DWORD        m_dwElements;
	HWND         m_hWnd;
	DWORD        m_dwImmediate;
public:
	bool InitDirectInput(HINSTANCE hInst, HWND hWnd, bool keyboard, bool mouse);
	bool KeyProcess();
	bool MouseProcess();
	void DeviceAcquire();
	void DeviceUnacquire();
	bool IsKeyDown(DWORD dwKey);
	bool IsKeyUP(DWORD dwKey);
	void PostProcess();
	void SetAcquire(bool bActive);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool ResetDevice();

public:
	JDxInput();
	virtual ~JDxInput();
};
#define I_InputDx JDxInput::GetInstance()