#pragma once
#include "JDxObject.h"
class JDxSprite : public JDxObject
{
public:
	vector<JDxObject> m_ImageList;
	vector<fRECT> m_rtEffect;
	int m_iStart;
	int m_iMax;
	fPOINT m_ImageSize;
	float m_fFrameUpdateSec;
	float m_fFrameElapseSec;
	bool m_bPlay;
	bool m_bLoop;
public:
	bool Frame(ID3D11DeviceContext* context);
	void SetUp(float fSec = 0.7f);
	void Update();
	bool PreRender(ID3D11DeviceContext* context);
	bool Render(ID3D11DeviceContext* context);
	bool PostRender(ID3D11DeviceContext* context);
	bool Release();
public:
	JDxSprite();
	virtual ~JDxSprite();
};

