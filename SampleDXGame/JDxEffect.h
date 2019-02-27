#pragma once
#include "JDxSprite.h"
class JDxEffect : public JDxSprite
{
public:
	vector<JDxSprite> m_EffectList;
	vector<JDxSprite> m_Effect;

public:
	bool DataLoad(const TCHAR* pszLoadFile);
	bool Add();
public:
	bool Init();
	bool Frame(ID3D11DeviceContext* context, fPOINT EnemyPos);
	bool Render(ID3D11DeviceContext* context);
	bool Release();
public:
	JDxEffect();
	virtual ~JDxEffect();
};

