#pragma once
#include "JCore.h"
class JSample : public JCore
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	bool Run();
public:
	JSample();
	virtual ~JSample();
};

