#include "JDxPlayer.h"
#include "JInput.h"
bool JDxPlayer::Init()
{
	DataLoad(L"PlayerData.txt");
	SetRect(0, 0, 180, 182);
	SetPos(m_rt);
	JDxSprite sprite;
	//m_PlayerList.push_back(sprite);
	//m_PlayerList.push_back(sprite);
	//m_PlayerList.push_back(sprite);
	return true;
}
bool JDxPlayer::Frame(ID3D11DeviceContext* context)
{
	if (m_PlayerList[MOVE].m_bPlay != true && m_PlayerList[ATTACK].m_bPlay != true)
	{
		m_PlayerList[IDLE].m_bPlay = true;
		m_PlayerList[MOVE].m_bPlay = false;
		m_PlayerList[ATTACK].m_bPlay = false;
	}
	if (I_Input.KeyCheck('T') == KEY_PUSH || I_Input.KeyCheck('T') == KEY_HOLD)
	{
		m_PlayerList[IDLE].m_bPlay = false;
		m_PlayerList[MOVE].m_bPlay = false;
		m_PlayerList[ATTACK].m_bPlay = true;
	}
	if (I_Input.KeyCheck('W') == KEY_PUSH || I_Input.KeyCheck('W') == KEY_HOLD)
	{
		Up();
		m_PlayerList[MOVE].m_bPlay = true;
		m_PlayerList[IDLE].m_bPlay = false;
		m_PlayerList[ATTACK].m_bPlay = false;
	}
	if (I_Input.KeyCheck('S') == KEY_PUSH || I_Input.KeyCheck('S') == KEY_HOLD)
	{
		Down();
		m_PlayerList[MOVE].m_bPlay = true;
		m_PlayerList[IDLE].m_bPlay = false;
		m_PlayerList[ATTACK].m_bPlay = false;
	}
	if (I_Input.KeyCheck('A') == KEY_PUSH || I_Input.KeyCheck('A') == KEY_HOLD)
	{
		Left();
		m_PlayerList[MOVE].m_bPlay = true;
		m_PlayerList[IDLE].m_bPlay = false;
		m_PlayerList[ATTACK].m_bPlay = false;
	}
	if (I_Input.KeyCheck('D') == KEY_PUSH || I_Input.KeyCheck('D') == KEY_HOLD)
	{
		Right();
		m_PlayerList[MOVE].m_bPlay = true;
		m_PlayerList[IDLE].m_bPlay = false;
		m_PlayerList[ATTACK].m_bPlay = false;
	}
	for (int Sprite = 0; Sprite < m_PlayerList.size() ; Sprite++)
	{
		for (int iFrameCnt = 0; iFrameCnt < m_PlayerList[Sprite].m_ImageList.size(); iFrameCnt++)
		{
			m_PlayerList[Sprite].m_ImageList[iFrameCnt].VertexList[0] = VertexList[0];
			m_PlayerList[Sprite].m_ImageList[iFrameCnt].VertexList[1] = VertexList[1];
			m_PlayerList[Sprite].m_ImageList[iFrameCnt].VertexList[2] = VertexList[2];
			m_PlayerList[Sprite].m_ImageList[iFrameCnt].VertexList[3] = VertexList[3];
			m_PlayerList[Sprite].m_ImageList[iFrameCnt].VertexList[4] = VertexList[4];
			m_PlayerList[Sprite].m_ImageList[iFrameCnt].VertexList[5] = VertexList[5];
			m_PlayerList[Sprite].m_ImageList[iFrameCnt].CreateVertexBuffer(g_pd3dDevice);
		}
	}
	for (int iSprite = 0; iSprite < m_PlayerList.size(); iSprite++)
	{
		m_PlayerList[iSprite].Frame(context);
		m_PlayerList[iSprite].CreateVertexBuffer(g_pd3dDevice);
	}
	return true;
}
bool JDxPlayer::Render(ID3D11DeviceContext* context)
{
	for (int iSprite = 0; iSprite < m_PlayerList.size(); iSprite++)
	{
		m_PlayerList[iSprite].Render(context);
	}
	return true;
}
bool JDxPlayer::Release()
{
	for (int iSprite = 0; iSprite < m_PlayerList.size(); iSprite++)
	{
		m_PlayerList[iSprite].Release();
	}
	return true;
}
void JDxPlayer::Left()
{
	m_Pos.x -= g_fSecPerFrame * 300.0f;
	SetRect(m_Pos.x, m_Pos.y, m_Pos.x + 180, m_Pos.y + 182);
}
void JDxPlayer::Right()
{
	m_Pos.x += g_fSecPerFrame * 300.0f;
	SetRect(m_Pos.x, m_Pos.y, m_Pos.x + 180, m_Pos.y + 182);
}
void JDxPlayer::Up()
{
	m_Pos.y -= g_fSecPerFrame * 300.0f;
	SetRect(m_Pos.x, m_Pos.y, m_Pos.x + 180, m_Pos.y + 182);
}
void JDxPlayer::Down()
{
	m_Pos.y += g_fSecPerFrame * 300.0f;
	SetRect(m_Pos.x, m_Pos.y, m_Pos.x + 180, m_Pos.y + 182);
}
bool JDxPlayer::SetPos(fRECT rt)
{
	m_Pos.x = rt.left;
	m_Pos.y = rt.top;
	return true;
}
bool JDxPlayer::Attack()
{
	return false;
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
	JDxObject Images;

	_fgetts(Buffer, _countof(Buffer), fp);
	_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iSpriteCnt);
	m_PlayerList.resize(iSpriteCnt);
	for (int iSprite = 0; iSprite < iSpriteCnt; iSprite++)
	{
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%f %f", &rt_UISize.x, &rt_UISize.y);
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iEffectFrame);
		for (int frame = 0; frame < iEffectFrame; frame++)
		{
			_fgetts(Buffer, _countof(Buffer), fp);
			_stscanf_s(Buffer, L"%s", Bitmap, _countof(Bitmap));
			//Player.PlayerSpriteList[iSprite].SetRect(400,300,450,350);
			JDxObject sample;
			sample.SetRect(0, 0, rt_UISize.x, rt_UISize.y);
			sample.Create(g_pd3dDevice, "VS", "PS1");
			sample.CreateVertexBuffer(g_pd3dDevice);
			sample.Load(g_pd3dDevice, Bitmap);
			m_PlayerList[iSprite].m_ImageSize = rt_UISize;
			//m_Sample[iSprite].SetRect(0,0,rt_UISize.x,rt_UISize.y);
			m_PlayerList[iSprite].m_iMax = iEffectFrame;
			//m_Sample[iSprite].Create(g_pd3dDevice, "VS", "PS1");
			//m_Sample[iSprite].CreateVertexBuffer(g_pd3dDevice);
			//m_Sample[iSprite].Load(g_pd3dDevice, Bitmap, BitmapMask);
			m_PlayerList[iSprite].m_ImageList.push_back(sample);
		}
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
	m_fDamage = 100.0f;
}


JDxPlayer::~JDxPlayer()
{
}
