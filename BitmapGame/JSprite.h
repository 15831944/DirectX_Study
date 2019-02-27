#pragma once
#include "JObject.h"
class JSprite : public JObject
{
public:
	vector<RECT> m_rtEffect;
	int m_iStart;
	int m_iMax;
	float m_fFrameUpdateSec;
	float m_fFrameElapseSec;
	bool m_bPlay;
	bool m_bLoop;
public:
	bool Frame();
	bool Render();
	void SetUp(float fSec = 0.7f);
	void Update();
public:
	JSprite();
	virtual ~JSprite();
};