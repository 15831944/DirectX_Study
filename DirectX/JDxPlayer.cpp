#include "JDxPlayer.h"
#include "JInput.h"
bool JDxPlayer::Init()
{
	DataLoad(L"PlayerData.txt");
	SetRect(100, 300, 150, 350);
	SetPos(m_rt);
	Arrow.Init();
	return true;
}
bool JDxPlayer::Frame(ID3D11DeviceContext* context, fRECT EnemyRT)
{
	Arrow.Frame(context, m_Pos, EnemyRT);
	if (I_Input.m_dwMouseState[0] == KEY_PUSH)
	{

		PlayerSpriteList[ATTACK].m_bPlay = true;
		PlayerSpriteList[MOVE].m_bPlay = false;
		PlayerSpriteList[IDLE].m_bPlay = false;
		Arrow.m_ArrowList.push_back(Arrow.m_Arrow);
	}
	if (I_Input.m_MousePos.x >= 0 && I_Input.m_MousePos.x <= 120 &&
		I_Input.m_MousePos.y >= 380 && I_Input.m_MousePos.y <= 480)
	{
		if (I_Input.m_dwMouseState[0] == KEY_PUSH)
		{
			Arrow.m_bSkill = true; 
		}
	}
	if (PlayerSpriteList[MOVE].m_bPlay != true && PlayerSpriteList[ATTACK].m_bPlay != true)
	{
		PlayerSpriteList[IDLE].m_bPlay = true;
		PlayerSpriteList[MOVE].m_bPlay = false;
		PlayerSpriteList[ATTACK].m_bPlay = false;
	}
	if (I_Input.KeyCheck('W') == KEY_PUSH || I_Input.KeyCheck('W') == KEY_HOLD)
	{
		Up();
		PlayerSpriteList[MOVE].m_bPlay = true;
		PlayerSpriteList[IDLE].m_bPlay = false;
		PlayerSpriteList[ATTACK].m_bPlay = false;
	}
	if (I_Input.KeyCheck('S') == KEY_PUSH || I_Input.KeyCheck('S') == KEY_HOLD)
	{
		Down();
		PlayerSpriteList[MOVE].m_bPlay = true;
		PlayerSpriteList[IDLE].m_bPlay = false;
		PlayerSpriteList[ATTACK].m_bPlay = false;
	}
	if (I_Input.KeyCheck('A') == KEY_PUSH || I_Input.KeyCheck('A') == KEY_HOLD)
	{
		Left();
		PlayerSpriteList[MOVE].m_bPlay = true;
		PlayerSpriteList[IDLE].m_bPlay = false;
		PlayerSpriteList[ATTACK].m_bPlay = false;
	}
	if (I_Input.KeyCheck('D') == KEY_PUSH || I_Input.KeyCheck('D') == KEY_HOLD)
	{
		Right();
		PlayerSpriteList[MOVE].m_bPlay = true;
		PlayerSpriteList[IDLE].m_bPlay = false;
		PlayerSpriteList[ATTACK].m_bPlay = false;
	}
	for (int Sprite = 0; Sprite < PlayerSpriteList.size() ; Sprite++)
	{
		PlayerSpriteList[Sprite].VertexList[0] = VertexList[0];
		PlayerSpriteList[Sprite].VertexList[1] = VertexList[1];
		PlayerSpriteList[Sprite].VertexList[2] = VertexList[2];
		PlayerSpriteList[Sprite].VertexList[3] = VertexList[3];
		PlayerSpriteList[Sprite].VertexList[4] = VertexList[4];
		PlayerSpriteList[Sprite].VertexList[5] = VertexList[5];
		context->UpdateSubresource(PlayerSpriteList[Sprite].m_pVertexBuffer, 0, 0, PlayerSpriteList[Sprite].VertexList, 0, 0);
	}
	UpdatePosition(m_rt);
	for (int iSprite = 0; iSprite < PlayerSpriteList.size(); iSprite++)
	{
		PlayerSpriteList[iSprite].Frame(context);
		context->UpdateSubresource(PlayerSpriteList[iSprite].m_pVertexBuffer, 0, 0, PlayerSpriteList[iSprite].VertexList, 0, 0);
	}

	return true;
}
bool JDxPlayer::Render(ID3D11DeviceContext* context)
{
	Arrow.Render(context);
	for (int iSprite = 0; iSprite < PlayerSpriteList.size(); iSprite++)
	{
		PlayerSpriteList[iSprite].Render(context);
	}
	return true;
}
bool JDxPlayer::Release()
{
	for (int iSprite = 0; iSprite < PlayerSpriteList.size(); iSprite++)
	{
		PlayerSpriteList[iSprite].Release();
	}
	Arrow.Release();
	return true;
}
void JDxPlayer::Left()
{
	m_Pos.x -= g_fSecPerFrame * 300.0f;
}
void JDxPlayer::Right()
{
	m_Pos.x += g_fSecPerFrame * 300.0f;
}
void JDxPlayer::Up()
{
	m_Pos.y -= g_fSecPerFrame * 300.0f;
}
void JDxPlayer::Down()
{
	m_Pos.y += g_fSecPerFrame * 300.0f;
}
bool JDxPlayer::SetPos(fRECT rt)
{
	m_Pos.x = rt.left;
	m_Pos.y = rt.top;
	return true;
}
bool JDxPlayer::DataLoad(const TCHAR* pszLoadFile)
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

	/* PLAYER */
	_fgetts(Buffer, _countof(Buffer), fp);
	_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iSpriteCnt);
	PlayerSpriteList.resize(iSpriteCnt);
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
			PlayerSpriteList[iSprite].m_ImageSize = rt_UISize;
			PlayerSpriteList[iSprite].SetTex(rt_Tex, rt_UISize);
			PlayerSpriteList[iSprite].m_rtEffect.push_back(rt_Tex);
			PlayerSpriteList[iSprite].m_iMax = iEffectFrame;
		}
		PlayerSpriteList[iSprite].Create(g_pd3dDevice, "VS", "PS1");
		PlayerSpriteList[iSprite].CreateVertexBuffer(g_pd3dDevice);
		PlayerSpriteList[iSprite].Load(g_pd3dDevice, Bitmap, BitmapMask);
	}
	fclose(fp);
	return true;
}
JDxPlayer::JDxPlayer()
{
	m_iPlayerState = IDLE;
	m_fPower = 100.0f;
	m_fSpeed = 300.0f;
	m_fHp = 100.0f;
	m_fDamage = 10.0f;
}


JDxPlayer::~JDxPlayer()
{
}
