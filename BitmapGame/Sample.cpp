#include "JCore.h"
#include "JSprite.h"
#include "JPlayer.h"
#include "JEnemy.h"
#include "JArrow.h"
#define ARROW_MAX 10
#define ENEMY_MAX 30
static int ENEMY_LEVEL = 1;
static float LevelTime = 0.0f;
// SPRITELIST[0] :: BOMB
// SPRITELIST[1] :: FIRE
class Sample : public JCore
{
public:
	JObject			OpeningBack;
	JObject			OpeningBackSky;
	JObject			OpeningGameStart;
	JObject			InGameBack;
	JObject			HP_Back;
	JObject			HP;
	JPlayer			Player;
	vector<JEnemy>  Enemy;
	vector<JArrow>  Arrow;
	vector<JSprite> SpriteList;
	vector<JSprite> Sprite;
public:
	bool (Sample::*FunCall)();
	bool GameDataLoad(const TCHAR* pszLoadFile)
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
		RECT rt = { 0,0,0,0 };

		/* PLAYER */
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iSpriteCnt);
		Player.PlayerSpriteList.resize(iSpriteCnt);
		for (int iSprite = 0; iSprite < iSpriteCnt; iSprite++)
		{
			_fgetts(Buffer, _countof(Buffer), fp);
			_stscanf_s(Buffer, L"%s %d %s %s", Temp, _countof(Temp), &iEffectFrame, Bitmap, _countof(Bitmap), BitmapMask, _countof(BitmapMask));
			for (int frame = 0; frame < iEffectFrame; frame++)
			{
				_fgetts(Buffer, _countof(Buffer), fp);
				_stscanf_s(Buffer, L"%d %d %d %d", &rt.left, &rt.top, &rt.right, &rt.bottom);
				Player.PlayerSpriteList[iSprite].m_rtEffect.push_back(rt);
			}
			Player.PlayerSpriteList[iSprite].m_iMax = iEffectFrame;
			Player.PlayerSpriteList[iSprite].Load(m_hScreenDC, m_hOffScreenDC, Bitmap, BitmapMask);
		}
		/* ENEMY */
		JEnemy enemy;
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iSpriteCnt);
		enemy.EnemySpriteList.resize(iSpriteCnt);
		for (int iSprite = 0; iSprite < iSpriteCnt; iSprite++)
		{
			_fgetts(Buffer, _countof(Buffer), fp);
			_stscanf_s(Buffer, L"%s %d %s %s", Temp, _countof(Temp), &iEffectFrame, Bitmap, _countof(Bitmap), BitmapMask, _countof(BitmapMask));
			for (int frame = 0; frame < iEffectFrame; frame++)
			{
				_fgetts(Buffer, _countof(Buffer), fp);
				_stscanf_s(Buffer, L"%d %d %d %d", &rt.left, &rt.top, &rt.right, &rt.bottom);
				enemy.EnemySpriteList[iSprite].m_rtEffect.push_back(rt);
			}
			enemy.EnemySpriteList[iSprite].m_iMax = iEffectFrame;
			enemy.EnemySpriteList[iSprite].Load(m_hScreenDC, m_hOffScreenDC, Bitmap, BitmapMask);
		}
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			Enemy.push_back(enemy);
		}

		/* EFFECT */
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iSpriteCnt);
		SpriteList.resize(iSpriteCnt);
		for (int iSprite = 0; iSprite < iSpriteCnt; iSprite++)
		{
			_fgetts(Buffer, _countof(Buffer), fp);
			_stscanf_s(Buffer, L"%s %d %s %s", Temp, _countof(Temp), &iEffectFrame, Bitmap, _countof(Bitmap), BitmapMask, _countof(BitmapMask));
			for (int frame = 0; frame < iEffectFrame; frame++)
			{
				_fgetts(Buffer, _countof(Buffer), fp);
				_stscanf_s(Buffer, L"%d %d %d %d", &rt.left, &rt.top, &rt.right, &rt.bottom);
				SpriteList[iSprite].m_rtEffect.push_back(rt);
			}
			SpriteList[iSprite].m_iMax = iEffectFrame;
			SpriteList[iSprite].Load(m_hScreenDC, m_hOffScreenDC, Bitmap, BitmapMask);
		}

		/* ARROW */
		JArrow arrow;
		_fgetts(Buffer, _countof(Buffer), fp);
		_stscanf_s(Buffer, L"%s %d", Temp, _countof(Temp), &iUserCnt);
		for (int i = 0; i < iUserCnt; i++)
		{
			_fgetts(Buffer, _countof(Buffer), fp);
			_stscanf_s(Buffer, L"%s %s %s", UserName, _countof(UserName), Bitmap, _countof(Bitmap), BitmapMask, _countof(BitmapMask));
			for (int i = 0; i < ARROW_MAX; i++)
			{
				Arrow.push_back(arrow);
			}
		}

		fclose(fp);
		return true;
	}
	bool Opening()
	{
		I_Sound.Play(0);
		/* SKY SCROLL */
		static float ScrollX = 0.0f;
		ScrollX += g_fSecPerFrame * 25.0f;	
		if (ScrollX >= OpeningBackSky.m_rt.right)
		{
			ScrollX = 0;
		}
		BitBlt(m_hOffScreenDC, 
			OpeningBackSky.m_pos.x + ScrollX, OpeningBackSky.m_pos.y,
			OpeningBackSky.m_rt.right, OpeningBackSky.m_rt.bottom,
			OpeningBackSky.m_pBitmap->m_hMemDC, 
			OpeningBackSky.m_rt.left, OpeningBackSky.m_rt.top, SRCCOPY);
		BitBlt(m_hOffScreenDC, 
			-OpeningBackSky.m_rt.right + ScrollX, OpeningBackSky.m_pos.y,
			OpeningBackSky.m_rt.right, OpeningBackSky.m_rt.bottom,
			OpeningBackSky.m_pBitmap->m_hMemDC, 
			OpeningBackSky.m_rt.left, OpeningBackSky.m_rt.top, SRCCOPY);

		/* BACKGROUND */
		BitBlt(m_hOffScreenDC,
			OpeningBack.m_pos.x, OpeningBack.m_pos.y,
			OpeningBack.m_rt.right, OpeningBack.m_rt.bottom,
			OpeningBack.m_pBitmapMask->m_hMemDC,
			OpeningBack.m_rt.left, OpeningBack.m_rt.top, SRCAND);
		BitBlt(m_hOffScreenDC,
			OpeningBack.m_pos.x, OpeningBack.m_pos.y,
			OpeningBack.m_rt.right, OpeningBack.m_rt.bottom,
			OpeningBack.m_pBitmap->m_hMemDC,
			OpeningBack.m_rt.left, OpeningBack.m_rt.top, SRCINVERT);
		BitBlt(m_hOffScreenDC,
			OpeningBack.m_pos.x, OpeningBack.m_pos.y,
			OpeningBack.m_rt.right, OpeningBack.m_rt.bottom,
			OpeningBack.m_pBitmapMask->m_hMemDC,
			OpeningBack.m_rt.left, OpeningBack.m_rt.top, SRCINVERT);

		/* GAMESTART */

		//OpeningGameStart.RotateBit(I_Timer.m_fGameTimer);
		BitBlt(m_hOffScreenDC,
			OpeningGameStart.m_pos.x, OpeningGameStart.m_pos.y,
			OpeningGameStart.m_rt.right, OpeningGameStart.m_rt.bottom,
			OpeningGameStart.m_pBitmap->m_hMemDC,
			OpeningGameStart.m_rt.left, OpeningGameStart.m_rt.top, SRCCOPY);

		if (I_Input.m_dwMouseState[0] == KEY_PUSH)
		{
			if (I_Input.m_MousePos.x >= 380 && I_Input.m_MousePos.x <= 580)
			{
				if (I_Input.m_MousePos.y >= 350 && I_Input.m_MousePos.y <= 450)
				{
					I_Sound.Stop(0);
					FunCall = &Sample::InGame;
				}
			}
		}
		return true;
	}
	bool InGame()
	{
		I_Sound.Play(1);
		BitBlt(m_hOffScreenDC, InGameBack.m_pos.x, InGameBack.m_pos.y, InGameBack.m_rt.right, InGameBack.m_rt.bottom, InGameBack.m_pBitmap->m_hMemDC, InGameBack.m_rt.left, InGameBack.m_rt.top, SRCCOPY);
		BitBlt(m_hOffScreenDC, Player.m_pos.x - 25, Player.m_pos.y - 10, HP_Back.m_rt.right, HP_Back.m_rt.bottom, HP_Back.m_pBitmap->m_hMemDC, HP_Back.m_rt.left, HP_Back.m_rt.top, SRCCOPY);
		BitBlt(m_hOffScreenDC, Player.m_pos.x - 25, Player.m_pos.y - 10, Player.m_fHp, HP.m_rt.bottom, HP.m_pBitmap->m_hMemDC, HP.m_rt.left, HP.m_rt.top, SRCCOPY);
		
		for (int ArrowCnt = 0; ArrowCnt < Arrow.size(); ArrowCnt++)
		{
			Arrow[ArrowCnt].Render();
		}
		
		for (int SpriteCnt = 0; SpriteCnt < Player.PlayerSpriteList.size(); SpriteCnt++)
		{
			Player.PlayerSpriteList[SpriteCnt].Render();
		}
		
		for (int EnemyCnt = 0; EnemyCnt < ENEMY_LEVEL; EnemyCnt++)
		{
			for (int SpriteCnt = 0; SpriteCnt < Enemy[EnemyCnt].EnemySpriteList.size(); SpriteCnt++)
			{
				Enemy[EnemyCnt].EnemySpriteList[SpriteCnt].Render();
			}
		}
	
		for (int SpriteCnt = 0; SpriteCnt < Sprite.size(); SpriteCnt++)
		{
			Sprite[SpriteCnt].Render();
		}
		
		return true;
	}
	bool Init()
	{
		I_FSM.Init();
		GameDataLoad(L"GameData.txt");
		I_Sound.Load("../../sound/Opening.mp3");
		I_Sound.Load("../../sound/InGame.mp3");
		I_Sound.Load("../../sound/Bomb.mp3");

		/* BACKGROUND INIT */
		fPOINT bkpos = { 0,0 };
		RECT bkrt = { 0,0,960,480 };
		InGameBack.Init();
		InGameBack.Load(m_hScreenDC, m_hOffScreenDC, L"../../Data/bitmap/BackGround.bmp", NULL);
		InGameBack.SetRectPos(bkrt, bkpos);

		/* OPENING INIT */
		OpeningBackSky.Init();
		OpeningBackSky.Load(m_hScreenDC, m_hOffScreenDC, L"../../Data/bitmap/OpeningBackSky.bmp", NULL);
		OpeningBackSky.SetRectPos(bkrt, bkpos);
		OpeningBack.Init();
		OpeningBack.Load(m_hScreenDC, m_hOffScreenDC, L"../../Data/bitmap/OpeningBack.bmp", L"../../Data/bitmap/OpeningBack_mask.bmp");
		OpeningBack.SetRectPos(bkrt, bkpos);
		fPOINT GameStartPos = { 380,350 };
		RECT GameStartRT = { 0,0,200,100 };
		OpeningGameStart.Init();
		OpeningGameStart.Load(m_hScreenDC, m_hOffScreenDC, L"../../Data/bitmap/GameStart.bmp", NULL);
		OpeningGameStart.SetRectPos(GameStartRT, GameStartPos);

		/* HPBAR INIT */
		fPOINT HPBACKPOS = { 50,10 };
		RECT HPBACKRT = { 0,0,800,60 };
		HP_Back.Init();
		HP_Back.Load(m_hScreenDC, m_hOffScreenDC, L"../../Data/bitmap/HP_Back.bmp", NULL);
		HP_Back.SetRectPos(HPBACKRT, HPBACKPOS);
		fPOINT HPPOS = { 55,15 };
		RECT HPRT = { 0,0,790,50 };
		HP.Init();
		HP.Load(m_hScreenDC, m_hOffScreenDC, L"../../Data/bitmap/HP.bmp", NULL);
		HP.SetRectPos(HPRT, HPPOS);

		/* PLAYER INIT */
		fPOINT PlayerPos = { 100, 300 };
		RECT PlayerRT = { 0, 0, 50, 50 };
		Player.SetRectPos(PlayerRT, PlayerPos);
		for (int SpriteCnt = 0; SpriteCnt < Player.PlayerSpriteList.size(); SpriteCnt++)
		{
			Player.PlayerSpriteList[SpriteCnt].Init();
		}

		/* ENEMY INIT */
		fPOINT EnemyPos[ENEMY_MAX];
		RECT EnemyRT = { 0, 0, 64, 50 };
		for (int EnemyCnt = 0; EnemyCnt < Enemy.size(); EnemyCnt++)
		{
			srand((unsigned)time(NULL));
			EnemyPos[EnemyCnt].x = 1000;
			EnemyPos[EnemyCnt].y = 230 + rand() % 150;
			Enemy[EnemyCnt].SetRectPos(EnemyRT, EnemyPos[EnemyCnt]);
			Enemy[EnemyCnt].m_fSpeed = 100 + rand() % 200;
			for (int SpriteCnt = 0; SpriteCnt < Enemy[EnemyCnt].EnemySpriteList.size(); SpriteCnt++)
			{
				Enemy[EnemyCnt].EnemySpriteList[SpriteCnt].Init();
			}
			Enemy[EnemyCnt].FSM(I_FSM.Add(0));
		}

		/* ARROW INIT */
		fPOINT ArrowPos = { 1000,1000 };
		RECT ArrowRt = { 0, 0, 50, 10 };
		for (int ArrowCnt = 0; ArrowCnt < Arrow.size(); ArrowCnt++)
		{
			Arrow[ArrowCnt].Init();
			Arrow[ArrowCnt].Load(m_hScreenDC, m_hOffScreenDC, L"../../Data/bitmap/Arrow.bmp", L"../../Data/bitmap/Arrow_mask.bmp");
			Arrow[ArrowCnt].SetRectPos(ArrowRt, ArrowPos);
		}

		FunCall = &Sample::Opening;
		return true;
	}
	bool Frame()
	{
		if (FunCall == &Sample::Opening) return false;

		/* BACKGROUND FRAME */
		InGameBack.Frame();

		/* PLAYER FRAME */
		Player.Frame();
		for (int SpriteCnt = 0; SpriteCnt < Player.PlayerSpriteList.size(); SpriteCnt++)
		{
			Player.PlayerSpriteList[SpriteCnt].m_pos = Player.m_pos;
			Player.PlayerSpriteList[SpriteCnt].m_CenterPos = Player.m_CenterPos;
			Player.PlayerSpriteList[SpriteCnt].Frame();
		}

		/* ENEMY FRAME */
		LevelTime += g_fSecPerFrame;
		if (LevelTime >= 5.0f)
		{
			LevelTime = 0.0f;
			ENEMY_LEVEL++;
		}
		for (int EnemyCnt = 0; EnemyCnt < ENEMY_LEVEL; EnemyCnt++)
		{
			Enemy[EnemyCnt].Frame();
			if (EnemyCnt % 2 == 0)
			{
				Enemy[EnemyCnt].EnemySpriteList[0].m_bPlay = true;
				//Enemy[EnemyCnt].Process(Player);
			}
			else
			{
				Enemy[EnemyCnt].EnemySpriteList[1].m_bPlay = true;
				/*Enemy[EnemyCnt].Process(Player);*/
			}
			if (Enemy[EnemyCnt].m_pos.x <= 0.0f)
			{
				Player.m_fHp -= 10.0f;
				Enemy[EnemyCnt].m_pos.x = 1000;
				Enemy[EnemyCnt].m_pos.y = 230 + rand() % 150;
				Enemy[EnemyCnt].m_fSpeed = 100 + rand() % 200;
			}
			for (int SpriteCnt = 0; SpriteCnt < Enemy[EnemyCnt].EnemySpriteList.size(); SpriteCnt++)
			{
				if (RectInRect(Enemy[EnemyCnt].m_rtCollision, Player.m_rtCollision))
				{
					SpriteList[1].m_bPlay = true;
					SpriteList[1].m_pos = Player.m_CenterPos;
					SpriteList[1].m_pos.y -= 100;
					Sprite.push_back(SpriteList[1]);
					Player.m_fHp -= 10.0f;
					Enemy[EnemyCnt].m_pos.x = 1000;
					Enemy[EnemyCnt].m_pos.y = 230 + rand() % 150;
					Enemy[EnemyCnt].m_fSpeed = 100 + rand() % 200;
				}
			}
			Enemy[EnemyCnt].Process(Player);
		}

		/* ARROW FRAME */
		if (I_Input.m_dwMouseState[0] == KEY_PUSH)
		{
			if (g_iArrowCount >= Arrow.size())
			{
				g_iArrowCount = 0;
			}
			Arrow[g_iArrowCount++].m_bAttack = true;
			Arrow[g_iArrowCount - 1].m_pos = Player.m_pos;
			Arrow[g_iArrowCount - 1].m_CenterPos = Player.m_CenterPos;
		}
		vector<JSprite>::iterator ITOR;
		for (ITOR = Sprite.begin(); ITOR != Sprite.end(); ITOR++)
		{
			JSprite* data = &(*ITOR);
			if (!data->m_bPlay)
			{
				Sprite.erase(ITOR);
				break;
			}
		}
		for (int ArrowCnt = 0; ArrowCnt < Arrow.size(); ArrowCnt++)
		{
			Arrow[ArrowCnt].m_rtCollision.left = Arrow[ArrowCnt].m_CenterPos.x;
			Arrow[ArrowCnt].m_rtCollision.top = Arrow[ArrowCnt].m_CenterPos.y;
			Arrow[ArrowCnt].m_rtCollision.right = Arrow[ArrowCnt].m_rt.right + Arrow[ArrowCnt].m_CenterPos.x;
			Arrow[ArrowCnt].m_rtCollision.bottom = Arrow[ArrowCnt].m_rt.bottom + Arrow[ArrowCnt].m_CenterPos.y;

			for (int EnemyCnt = 0; EnemyCnt < ENEMY_LEVEL; EnemyCnt++)
			{
				if (RectInRect(Enemy[EnemyCnt].m_rtCollision, Arrow[ArrowCnt].m_rtCollision))
				{
					I_Sound.Play(2);
					SpriteList[0].m_bPlay = true;
					SpriteList[0].m_pos = Enemy[EnemyCnt].m_CenterPos;
					Sprite.push_back(SpriteList[0]);
					Enemy[EnemyCnt].m_pos.x = 1000;
					Enemy[EnemyCnt].m_pos.y = 230 + rand() % 150;
					Enemy[EnemyCnt].m_fSpeed = 100 + rand() % 200;
					Arrow[ArrowCnt].m_bAttack = false;
				}
			}
			Arrow[ArrowCnt].Frame();
		}
		/* EFFECT FRAME */
		for (int SpriteCnt = 0; SpriteCnt < Sprite.size(); SpriteCnt++)
		{
			Sprite[SpriteCnt].Frame();
		}

		/* 패배 */
		if (Player.m_fHp <= 0.0f)
		{
			ENEMY_LEVEL = 1;
			Player.m_pos.x = 100;
			Player.m_pos.y = 300;
			Player.m_fHp = 100.0f;
			MessageBox(m_hWnd, L"패배", L"게임종료", MB_OK);
			I_Sound.Stop(1);
			FunCall = &Sample::Opening;
		}

		/* 승리 */
		if (ENEMY_LEVEL >= ENEMY_MAX)
		{
			ENEMY_LEVEL = 1;
			Player.m_pos.x = 100;
			Player.m_pos.y = 300;
			Player.m_fHp = 100.0f;
			MessageBox(m_hWnd, L"승리", L"게임종료", MB_OK);
			I_Sound.Stop(1);
			FunCall = &Sample::Opening;
		}
		return true;
	}
	bool Render()
	{
		(this->*FunCall)();
		return true;
	}
	bool Release()
	{
		InGameBack.Release();
		HP.Release();
		HP_Back.Release();
		for (int SpriteCnt = 0; SpriteCnt < Player.PlayerSpriteList.size(); SpriteCnt++)
		{
			Player.PlayerSpriteList[SpriteCnt].Release();
		}
		for (int EnemyCnt = 0; EnemyCnt < Enemy.size(); EnemyCnt++)
		{
			for (int SpriteCnt = 0; SpriteCnt < Enemy[EnemyCnt].EnemySpriteList.size(); SpriteCnt++)
			{
				Enemy[EnemyCnt].EnemySpriteList[SpriteCnt].Release();
			}
		}
		for (int ArrowCnt = 0; ArrowCnt < Arrow.size(); ArrowCnt++)
		{
			Arrow[ArrowCnt].Release();
		}		
		I_FSM.Release();
		return true;
	}
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow)
{
	Sample core;
	if (core.SetWindow(hInstance, 960, 480, L"Defence Game"))
	{
		core.Run();
		return 0;
	}
	return 1;
}