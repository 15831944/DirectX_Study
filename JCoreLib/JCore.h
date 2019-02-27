#pragma once
#include "JDevice.h"
#include "JTimer.h"
#include "JInput.h"
#include "JDxInput.h"
#include "JWrite.h"
#include "JState.h"
#include "JCamera.h"
#include "JLineShape.h"
/*
	0: QuarterView
	1: TopView
	2: SideView
	3: FrontView
	4: OrtorView
*/
class JCore : public JDevice
{
public:
	JCamera m_Camera[5];
	JCamera* m_MainCam;
	JLineShape*  m_LineShape;
public:
	bool m_bShowDebug;
public:
	bool GameRun();
	bool GameInit();
	bool GameFrame();
	bool GameRender();
	bool GameRelease();
	void MsgEvent(MSG msg);
	bool ResizeClient(UINT iWidth, UINT iHeight);
public:
	// camera
	void SwapCamera(JCamera* cam);
	void InitCamera();
	D3DXMATRIX* GetView();
	D3DXMATRIX* GetProj();
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

