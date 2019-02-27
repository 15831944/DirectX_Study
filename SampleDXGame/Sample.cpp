#include "JCore.h"
#include "JDxPlayer.h"
#include "JDxEnemy.h"
#include "JUserInterface.h"
#include "JSound.h"
#include "JDxArrow.h"
class Sample : public JCore
{
	int m_iStage;
	JDxPlayer Player;
	JDxEnemy  Enemy;
	JUserInterface Interface;
	bool bPlay;
	JObject OpeningBack;
	JObject OpeningBackSky;
	JObject OpeningGameStart;
public:
	bool Init()
	{
		I_Sound.Init();

		I_Sound.Load("../../sound/Opening.mp3");
		I_Sound.Load("../../sound/InGame.mp3");
		I_Sound.Load("../../sound/Bomb.mp3");
		Player.Init();
		Enemy.Init();
		Interface.Init();
		bPlay = false;

		OpeningBack.SetRect(0, 0, 960, 480);
		OpeningBack.Create(g_pd3dDevice);
		OpeningBack.CreateVertexBuffer(g_pd3dDevice);
		OpeningBack.Load(g_pd3dDevice, L"../../Data/bitmap/OpeningBack.bmp", L"../../Data/bitmap/OpeningBack_mask.bmp");

		OpeningBackSky.SetRect(0, 0, 960,480);
		OpeningBackSky.Create(g_pd3dDevice);
		OpeningBackSky.CreateVertexBuffer(g_pd3dDevice);
		OpeningBackSky.Load(g_pd3dDevice, L"../../Data/bitmap/OpeningBackSky.bmp");

		OpeningGameStart.SetRect(380, 350, 580, 450);
		OpeningGameStart.Create(g_pd3dDevice);
		OpeningGameStart.CreateVertexBuffer(g_pd3dDevice);
		OpeningGameStart.Load(g_pd3dDevice, L"../../Data/bitmap/GameStart.bmp");
		return true;
	}
	bool Frame()
	{
		GetContext()->RSSetState(JState::g_pRSBackCullSolid);
		GetContext()->OMSetBlendState(JState::g_pAlphaBlend, 0, -1);
		GetContext()->OMSetDepthStencilState(JState::g_pEnableDSS, 0x00);

		if (!bPlay)
		{
			if (I_Input.m_dwMouseState[0] == KEY_PUSH)
			{
				if (I_Input.m_MousePos.x >= 380 && I_Input.m_MousePos.x <= 580)
				{
					if (I_Input.m_MousePos.y >= 350 && I_Input.m_MousePos.y <= 450)
					{
						I_Sound.Stop(0);
						bPlay = true;
					}
				}
			}
			OpeningBack.Frame();
			OpeningBackSky.Frame();
			OpeningGameStart.Frame();
		}
		if (!bPlay) return true;
		Enemy.Frame(GetContext(), Player);
		Player.Frame(GetContext(),Enemy.m_rt);
		Interface.Frame();
		return true;
	}
	bool Render()
	{
		if (!bPlay)
		{
			OpeningBackSky.Render(GetContext());
			OpeningBack.Render(GetContext());
			OpeningGameStart.Render(GetContext());
		}
		if (!bPlay) return true;
		I_Sound.Play(0);
		Interface.Render(GetContext());
		Player.Render(GetContext());
		Enemy.Render(GetContext());

		TCHAR stage[256] = { 0, };
		_stprintf_s(stage, L"Score : %d", Enemy.m_iEnemyDieCnt);
		I_Write.Draw(stage, 25, { 445, 10, 1100,1000 });
		return true;
	}
	bool Release()
	{
		OpeningBack.Release();
		OpeningBackSky.Release();
		OpeningGameStart.Release();

		Interface.Release();
		Player.Release();
		Enemy.Release();
		return true;
	}
	Sample() {}
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow)
{
	Sample core;
	if (core.SetWindow(hInstance, 960, 480, L"DirectX Sample"))
	{
		core.Run();
		return 0;
	}
	return 1;
}