#include "JDxArrow.h"
#include "JInput.h"
#include "JDxPlayer.h"
bool JDxArrow::Init()
{
	SetUp(2.0f,1.0f);
	DataLoad(L"ArrowData.txt");
	m_Arrow.SetRect(1000, 1000, 1050, 1010);
	SetPos(m_rt);
	return true;
}
void JDxArrow::SetUp(float fFrameSec, float fReleaseSec)
{
	m_fFrameUpdateSec = fFrameSec;
	m_fReleaseUpdateSec = fReleaseSec;
}
void JDxArrow::DeleteArrow()
{
	if (m_ArrowList.empty()) return;
	m_fReleaseElapseSec += g_fSecPerFrame;
	vector<JObject>::iterator ITOR = m_ArrowList.begin();
	if (m_fReleaseElapseSec >= m_fReleaseUpdateSec)
	{
		(*ITOR).m_Pos.x = 2000;
		(*ITOR).m_Pos.y = 2000;
		m_ArrowList.erase(ITOR);
		m_fReleaseElapseSec = 0.0f;
	}
}
bool JDxArrow::UseSkill()
{
	if (!m_bSkill) return false;
	SetUp(0.05f, 1.0f);
	m_fSkillElapseSec += g_fSecPerFrame;
	if (m_fSkillElapseSec >= m_fSkillUpdateSec)
	{
		SetUp(2.0f, 1.0f);
		m_bSkill = false;
		m_fSkillElapseSec = 0.0f;
		m_ArrowList.clear();
	}
	return true;
}
bool JDxArrow::Frame(ID3D11DeviceContext* context, fPOINT  PlayerPos, fRECT EnemyRT)
{
	DeleteArrow();
	SetPos(PlayerPos);
	Attack();
	UseSkill();

	//m_Pos.x += g_fSecPerFrame;

	
	for (int iList = 0; iList < m_ArrowList.size(); iList++)
	{
		if (DxRectInRect(EnemyRT, m_ArrowList[iList].m_rt))
		{
			m_ArrowList[iList].m_Pos.y = 10000;
			m_ArrowList[iList].m_Pos.x = 10000;
			return true;
		}
	}
	return true;
}
bool JDxArrow::Render(ID3D11DeviceContext* context)
{
	for (int iList = 0; iList < m_ArrowList.size(); iList++)
	{
		m_ArrowList[iList].Render(context);
	}
	return true;
}
bool JDxArrow::SetPos(fPOINT pos)
{
	m_Arrow.m_Pos.x = pos.x + 40.0f;
	m_Arrow.m_Pos.y = pos.y + 25.0f;
	return true;
}
bool JDxArrow::SetPos(fRECT rt)
{
	m_Arrow.m_Pos.x = rt.left;
	m_Arrow.m_Pos.y = rt.top;
	return true;
}
bool JDxArrow::Attack()
{
	for (int iList = 0; iList < m_ArrowList.size(); iList++)
	{
		m_ArrowList[iList].m_Pos.x += g_fSecPerFrame * 1000.0f;
		m_ArrowList[iList].UpdatePosition(m_ArrowList[iList].m_rt);
	}
	return true;
}
bool JDxArrow::Release()
{
	m_Arrow.Release();
	for (int iArrow = 0; iArrow < m_ArrowList.size(); iArrow++)
	{
		m_ArrowList[iArrow].Release();
	}
	m_ArrowList.clear();
	return true;
}
bool JDxArrow::DataLoad(const TCHAR* pszLoadFile)
{
	FILE* fp;
	_wfopen_s(&fp, pszLoadFile, L"rt");
	if (fp == NULL)
	{
		return false;
	}

	TCHAR Buffer[256] = { 0, };
	TCHAR Temp[256] = { 0, };
	TCHAR Bitmap[256] = { 0, };
	TCHAR BitmapMask[256] = { 0, };
	int iSpriteCnt = 0;
	int iEffectFrame = 0;
	fRECT rt_Tex = { 0,0,0,0 };
	fPOINT rt_UISize = { 0, };

	///* ARROW */
	_fgetts(Buffer, _countof(Buffer), fp);
	_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iSpriteCnt);
	_fgetts(Buffer, _countof(Buffer), fp);
	_stscanf_s(Buffer, L"%f %f", &rt_UISize.x, &rt_UISize.y);
	for (int iSprite = 0; iSprite < iSpriteCnt; iSprite++)
	{
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%s %s %s", Temp, _countof(Temp), Bitmap, _countof(Bitmap), BitmapMask, _countof(BitmapMask));
		m_Arrow.SetTex(rt_Tex, rt_UISize);
		m_Arrow.Create(g_pd3dDevice, "VS", "PS1");
		m_Arrow.CreateVertexBuffer(g_pd3dDevice);
		m_Arrow.Load(g_pd3dDevice, Bitmap, BitmapMask);
	}
	fclose(fp);
	return true;
}
JDxArrow::JDxArrow()
{
	m_fFrameUpdateSec = 1.0f;
	m_fReleaseUpdateSec = 0.5f;
	m_fFrameElapseSec = 0.0f;
	m_fReleaseElapseSec = 0.0f;
	m_fSkillUpdateSec = 1.0f;
	m_fSkillElapseSec = 0.0f;
}


JDxArrow::~JDxArrow()
{
}
