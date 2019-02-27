#pragma once
#include "JStd.h"
class JWindow
{
public:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	RECT m_rtWindow;
public:
	bool Run();
	bool SetWindow(HINSTANCE hInstance, int  Width, int Height, LPCWSTR ClassName);
public:
	virtual void MsgEvent(MSG msg);
	virtual bool GameRun();
	virtual bool GameInit();
	virtual bool GameRelease();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	JWindow();
	virtual ~JWindow();
};


