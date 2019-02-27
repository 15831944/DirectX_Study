#include "JDxEffect.h"
#include "JInput.h"
bool JDxEffect::Init()
{
	DataLoad(L"EffectData.txt");
	SetRect(0, 0, 50, 50);
	return true;
}
bool JDxEffect::Add()
{
	m_Effect.push_back(m_EffectList[0]);
	return true;
}
bool JDxEffect::Frame(ID3D11DeviceContext* context, fPOINT EnemyPos)
{
	vector<JDxSprite>::iterator ITOR;
	for (ITOR = m_Effect.begin(); ITOR != m_Effect.end(); ITOR++)
	{
		JDxSprite* data = &(*ITOR);
		if (!data->m_bPlay)
		{
			m_Effect.erase(ITOR);
			break;
		}
	}
	for (int iList = 0; iList < m_EffectList.size(); iList++)
	{
		m_EffectList[iList].VertexList[0] = VertexList[0];
		m_EffectList[iList].VertexList[1] = VertexList[1];
		m_EffectList[iList].VertexList[2] = VertexList[2];
		m_EffectList[iList].VertexList[3] = VertexList[3];
		m_EffectList[iList].VertexList[4] = VertexList[4];
		m_EffectList[iList].VertexList[5] = VertexList[5];
		m_EffectList[iList].CreateVertexBuffer(g_pd3dDevice);
	}
	for (int iList = 0; iList < m_EffectList.size(); iList++)
	{
		m_EffectList[iList].m_bPlay = true;
	}
	m_Pos = EnemyPos;
	UpdatePosition(m_rt);
	for (int List = 0; List < m_Effect.size(); List++)
	{
		m_Effect[List].Frame(context);
		m_Effect[List].CreateVertexBuffer(g_pd3dDevice);
	}
	return true;
}
bool JDxEffect::Render(ID3D11DeviceContext* context)
{
	for (int List = 0; List < m_Effect.size(); List++)
	{
		m_Effect[List].Render(context);
	}
	return true;
}
bool JDxEffect::Release()
{
	for (int List = 0; List < m_Effect.size(); List++)
	{
		m_Effect[List].Release();
	}
	for (int List = 0; List < m_EffectList.size(); List++)
	{
		m_EffectList[List].Release();
	}
	m_Effect.clear();
	m_EffectList.clear();
	return true;
}
bool JDxEffect::DataLoad(const TCHAR* pszLoadFile)
{
	FILE* fp;
	_wfopen_s(&fp, pszLoadFile, L"rt");
	if (fp == NULL)
	{
		return false;
	}
	TCHAR Buffer[256] = { 0, };
	TCHAR Temp[256] = { 0, };
	TCHAR UserName[256] = { 0, };
	TCHAR Bitmap[256] = { 0, };
	TCHAR BitmapMask[256] = { 0, };
	int iUserCnt = 0;
	int iSpriteCnt = 0;
	int iEffectFrame = 0;
	fRECT rt_Tex = { 0,0,0,0 };
	fPOINT rt_UISize = { 0, };
	/* EFFECT */
	_fgetts(Buffer, _countof(Buffer), fp);
	_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iSpriteCnt);
	m_EffectList.resize(iSpriteCnt);
	for (int iSprite = 0; iSprite < iSpriteCnt; iSprite++)
	{
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%s %d %s %s", Temp, _countof(Temp), &iEffectFrame, Bitmap, _countof(Bitmap), BitmapMask, _countof(BitmapMask));
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%f %f", &rt_UISize.x, &rt_UISize.y);
		for (int frame = 0; frame < iEffectFrame; frame++)
		{
			_fgetts(Buffer, _countof(Buffer), fp);
			_stscanf_s(Buffer, L"%f %f %f %f", &rt_Tex.left, &rt_Tex.top, &rt_Tex.right, &rt_Tex.bottom);
			m_EffectList[iSprite].SetRect(0, 0, 50, 50);
			m_EffectList[iSprite].SetTex(rt_Tex, rt_UISize);
			m_EffectList[iSprite].m_ImageSize = rt_UISize;
			m_EffectList[iSprite].m_rtEffect.push_back(rt_Tex);
			m_EffectList[iSprite].m_iMax = iEffectFrame;
		}
		m_EffectList[iSprite].Create(g_pd3dDevice, "VS", "PS1");
		m_EffectList[iSprite].CreateVertexBuffer(g_pd3dDevice);
		m_EffectList[iSprite].Load(g_pd3dDevice, Bitmap, BitmapMask);
	}
	fclose(fp);
	return true;
}

JDxEffect::JDxEffect()
{
}


JDxEffect::~JDxEffect()
{
}
