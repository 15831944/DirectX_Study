#pragma once
#include "JObject.h"
class JDxEventUI : public JObject
{
public:
	JObject		m_EventUI;
	bool	  m_bShowEvent;
public:
	bool Init();
	bool Frame();
	bool Render(ID3D11DeviceContext* context);
	bool Release();
public:
	JDxEventUI();
	virtual ~JDxEventUI();
};

