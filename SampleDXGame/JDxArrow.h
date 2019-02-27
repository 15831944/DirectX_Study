#pragma once
#include "JObject.h"
class JDxArrow : public JObject
{
public:
	JObject m_Arrow;
	vector<JObject> m_ArrowList;
	float m_fFrameUpdateSec;
	float m_fFrameElapseSec;
	float m_fReleaseUpdateSec;
	float m_fReleaseElapseSec;
	float m_fSkillUpdateSec;
	float m_fSkillElapseSec;
	bool m_bSkill;
public:
	void SetUp(float fFrameSec = 1.0f, float fReleaseSec = 1.0f);
	//bool Update();
	bool UseSkill();
	void DeleteArrow();
	bool Attack();
	bool DataLoad(const TCHAR* pszLoadFile);
	bool SetPos(fRECT rt);
	bool SetPos(fPOINT pos);
public:
	bool Init();
	bool Frame(ID3D11DeviceContext* context, fPOINT PlayerPos, fRECT EnemyRT);
	bool Render(ID3D11DeviceContext* context);
	bool Release();
public:
	JDxArrow();
	virtual ~JDxArrow();
};

