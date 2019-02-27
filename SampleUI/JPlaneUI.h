#pragma once
#include "UserInterface.h"
class JPlaneUI : public UserInterface
{
public:
	bool Frame();
	//bool Render(ID3D11DeviceContext* context);
public:
	JPlaneUI();
	virtual ~JPlaneUI();
};

