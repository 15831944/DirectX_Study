#include "JDxEnemy.h"
#include "JWrite.h"
#include "JSound.h"
bool JDxEnemy::Init()
{
	DataLoad(L"EnemyData.txt");
	SetRect(1000, 270, 160, 350);
	SetPos(m_rt);
	m_Effect.Init();
	return true;
}
bool JDxEnemy::Frame(ID3D11DeviceContext* context, JDxPlayer Player)
{
	for (int iSprite = 0; iSprite < EnemySpriteList.size(); iSprite++)
	{
		EnemySpriteList[iSprite].VertexList[0] = VertexList[0];
		EnemySpriteList[iSprite].VertexList[1] = VertexList[1];
		EnemySpriteList[iSprite].VertexList[2] = VertexList[2];
		EnemySpriteList[iSprite].VertexList[3] = VertexList[3];
		EnemySpriteList[iSprite].VertexList[4] = VertexList[4];
		EnemySpriteList[iSprite].VertexList[5] = VertexList[5];
		EnemySpriteList[iSprite].Frame(context);
		//EnemySpriteList[iSprite].CreateVertexBuffer(g_pd3dDevice);
		context->UpdateSubresource(EnemySpriteList[iSprite].m_pVertexBuffer, 0, 0, EnemySpriteList[iSprite].VertexList, 0, 0);
	}
	
	for (vector<JObject>::iterator ITOR =  Player.Arrow.m_ArrowList.begin();
									 ITOR != Player.Arrow.m_ArrowList.end(); ITOR++)
	{
		if (DxRectInRect(m_rt, (*ITOR).m_rt))
		{
			(*ITOR).m_Pos.x = 1000.0f;
			Player.Arrow.m_ArrowList.erase(ITOR);
			m_fCurrentHp -= Player.m_fDamage;
			m_Effect.Add();
			break;
		}
	}
	if (DxRectInRect(m_rt, Player.m_rt))
	{
		m_EnemyState = ENEMY_ATTACK;
		EnemySpriteList[ENEMY_ATTACK].m_bPlay = true;
		EnemySpriteList[ENEMY_MOVE].m_bPlay = false;
		SetRect(
			m_rt.left, 
			m_rt.top, 
			m_rt.left + EnemySpriteList[ENEMY_ATTACK].m_rtEffect[EnemySpriteList[ENEMY_ATTACK].m_iStart].right,
			m_rt.top +  EnemySpriteList[ENEMY_ATTACK].m_rtEffect[EnemySpriteList[ENEMY_ATTACK].m_iStart].bottom);
		//CreateVertexBuffer(g_pd3dDevice);
		Attack();
	}
	else
	{

		m_EnemyState = ENEMY_MOVE;
		EnemySpriteList[ENEMY_ATTACK].m_bPlay = false;
		EnemySpriteList[ENEMY_MOVE].m_bPlay = true;
		SetRect(
			m_rt.left,
			m_rt.top,
			m_rt.left + EnemySpriteList[ENEMY_MOVE].m_rtEffect[EnemySpriteList[ENEMY_MOVE].m_iStart].right,
			m_rt.top + EnemySpriteList[ENEMY_MOVE].m_rtEffect[EnemySpriteList[ENEMY_MOVE].m_iStart].bottom);
		//CreateVertexBuffer(g_pd3dDevice);
		Move();
	}
	UpdatePosition(m_rt);
	m_Effect.Frame(context,m_Pos);
	if (m_fCurrentHp < 0.0f)
	{
		m_Pos.x = 1000.0f;
		m_fCurrentHp = m_fNextHp;
		m_fNextHp *= 1.025;
		m_iEnemyDieCnt++;
	}
	if (m_Pos.x <= g_rtClient.left)
	{ 
		m_Pos.x = 1000.0f;
	}
	return true;
}
bool JDxEnemy::Render(ID3D11DeviceContext* context)
{
	for (int iSprite = 0; iSprite < EnemySpriteList.size(); iSprite++)
	{
		EnemySpriteList[iSprite].Render(context);
	}
	m_Effect.Render(context);
	return true;
}
bool JDxEnemy::Release()
{
	for (int iSprite = 0; iSprite < EnemySpriteList.size(); iSprite++)
	{
		EnemySpriteList[iSprite].Release();
	}
	m_Effect.Release();
	return true;
}
void JDxEnemy::Move()
{
	m_Pos.x -= g_fSecPerFrame * 500.0f;
}
void JDxEnemy::Attack()
{

}
bool JDxEnemy::SetPos(fRECT rt)
{
	m_Pos.x = rt.left;
	m_Pos.y = rt.top;
	return true;
}
bool JDxEnemy::DataLoad(const TCHAR* pszLoadFile)
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

	/* ENEMY1 */
	//JDxEnemy enemy;
	_fgetts(Buffer, _countof(Buffer), fp);
	_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iSpriteCnt);
	EnemySpriteList.resize(iSpriteCnt);
	_fgetts(Buffer, _countof(Buffer), fp);
	_stscanf_s(Buffer, L"%f %f", &rt_UISize.x, &rt_UISize.y);
	for (int iSprite = 0; iSprite < iSpriteCnt; iSprite++)
	{
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%s %d %s %s", Temp, _countof(Temp), &iEffectFrame, Bitmap, _countof(Bitmap), BitmapMask, _countof(BitmapMask));
		for (int frame = 0; frame < iEffectFrame; frame++)
		{
			_fgetts(Buffer, _countof(Buffer), fp);
			_stscanf_s(Buffer, L"%f %f %f %f", &rt_Tex.left, &rt_Tex.top, &rt_Tex.right, &rt_Tex.bottom);
			//Player.PlayerSpriteList[iSprite].SetRect(400,300,450,350);
			EnemySpriteList[iSprite].m_ImageSize = rt_UISize;
			EnemySpriteList[iSprite].SetTex(rt_Tex, rt_UISize);
			EnemySpriteList[iSprite].m_rtEffect.push_back(rt_Tex);
			EnemySpriteList[iSprite].m_iMax = iEffectFrame;
		}
		EnemySpriteList[iSprite].Create(g_pd3dDevice, "VS", "PS1");
		EnemySpriteList[iSprite].CreateVertexBuffer(g_pd3dDevice);
		EnemySpriteList[iSprite].Load(g_pd3dDevice, Bitmap, BitmapMask);
	}
	fclose(fp);
	return true;
}
JDxEnemy::JDxEnemy()
{
	//m_rtDxPos.x = 1000;
	//m_rtDxPos.y = 350;
	m_bDie = false;
	m_bCreate = false;
	m_EnemyState = ENEMY_MOVE;
	m_fCreateTime = 0.0f;
	m_fRandTime = 2 + rand() % 8;
	m_fCurrentHp = 10;
	m_fNextHp = 10;
	m_iEnemyDieCnt = 0;
	m_iMiniStageCnt = 0;
}

JDxEnemy::~JDxEnemy()
{
}
