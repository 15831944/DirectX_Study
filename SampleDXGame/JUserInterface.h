#pragma once
#include "JObject.h"
#include "JStageUI.h"
#include "JDxEventUI.h"
class JUserInterface : public JObject
{
public:
	JObject m_BackGround;
	//JDxEventUI m_EventUI;
	JStageUI  m_StageUI;
	JObject m_ui_btn_on[8];
	JObject m_ui_btn_off[8];
public:
	bool Init();
	bool Frame();
	bool Render(ID3D11DeviceContext* context);
	bool Release();
public:
	JUserInterface();
	virtual ~JUserInterface();
};

