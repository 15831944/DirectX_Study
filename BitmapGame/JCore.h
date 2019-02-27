#pragma once
#include "JWindow.h"
#include "JInput.h"
#include "JTimer.h"
#include "JSound.h"
class JCore : public JWindow
{
public:
	HDC m_hScreenDC;
	HDC m_hOffScreenDC;
	HBITMAP m_hOffScreenBitmap;
	HBITMAP m_hOldBitmap;
	bool m_bShowDebug;
public:
	bool GameRun();
	bool GameInit();
	bool GameFrame();
	bool GameRender();
	bool GameRelease();
	void MsgEvent(MSG msg);
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	JCore();
	virtual ~JCore();
};

