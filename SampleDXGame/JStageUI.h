#pragma once
class JStageUI
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	JStageUI();
	virtual ~JStageUI();
};
