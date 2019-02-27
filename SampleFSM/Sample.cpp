#include "JCore.h"
#include "JDxPlayer.h"
#include "JEnemy.h"
#include "JFiniteStateMachine.h"
class Sample : public JCore
{
	JDxPlayer player;
	JEnemy enemy;
public:
	bool Init()
	{
		I_FSM.Init();
		player.Init();

		enemy.SetRect(0, 0, 237, 228);
		enemy.Create(g_pd3dDevice, "VS", "PS1");
		enemy.CreateVertexBuffer(g_pd3dDevice);
		enemy.Load(g_pd3dDevice, L"../../Data/DNF_Pixel_Art/DarkMagition/Female_MagicAttack_02/FemaleMagicAttak_0.jpg");
		enemy.FSM(I_FSM.Add(0));
		return true;
	}
	bool Frame()
	{
		for (int iSprite = 0; iSprite < player.m_PlayerList.size(); iSprite++)
		{
			player.m_PlayerList[iSprite].SetUp(0.5f);
		}
		player.Frame(GetContext());
		enemy.Process(&player);
		return true;
	}
	bool Render()
	{
		player.Render(GetContext());
		enemy.Render(GetContext());
		return true;
	}
	bool Release()
	{
		I_FSM.Release();
		player.Release();
		enemy.Release();
		return true;
	}
	Sample() {}
	virtual ~Sample() {}
};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow)
{
	Sample core;
	if (core.SetWindow(hInstance, 960, 480, L"FSM Sample"))
	{
		core.Run();
		return 0;
	}
	return 1;
}