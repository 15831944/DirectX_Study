#pragma once
#include "JDevice.h"
class JWindow : public JDevice
{
public:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	RECT m_rtWindow;
public:
	bool Run();
	bool SetWindow(HINSTANCE hInstance, int  Width, int Height, LPCWSTR ClassName);
public:
	virtual void MsgEvent(MSG msg) {}
	virtual bool GameRun();
	virtual bool GameInit();
	virtual bool GameRelease();
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	JWindow();
	virtual ~JWindow();
};


