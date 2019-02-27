#pragma once
#include "JDevice.h"
#include "JInput.h"
#include "JTimer.h"
#include "JWrite.h"
#include "JSound.h"
class JCore : public JDevice
{
public:
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
	virtual bool PreFrame();
	virtual bool PreRender();
	virtual bool Frame();
	virtual bool Render();
	virtual bool PostFrame();
	virtual bool PostRender();
	virtual bool Release();
public:
	JCore();
	virtual ~JCore();
};

