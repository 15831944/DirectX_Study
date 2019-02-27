#include "JUserInterface.h"
#include "JInput.h"
#include "JWrite.h"
bool JUserInterface::Init()
{
	//m_EventUI.Init();

	m_BackGround.SetRect(0, 0, 960, 380);
	m_BackGround.Create(g_pd3dDevice);
	m_BackGround.CreateVertexBuffer(g_pd3dDevice);
	m_BackGround.Load(g_pd3dDevice, L"../../Data/bitmap/BackGround1.bmp");

	m_ui_btn_on[0].SetRect(0, 380, 120, 480);
	m_ui_btn_on[1].SetRect(120, 380, 240, 480);
	m_ui_btn_on[2].SetRect(240, 380, 360, 480);
	m_ui_btn_on[3].SetRect(360, 380, 480, 480);
	m_ui_btn_on[4].SetRect(480, 380, 600, 480);
	m_ui_btn_on[5].SetRect(600, 380, 720, 480);
	m_ui_btn_on[6].SetRect(720, 380, 840, 480);
	m_ui_btn_on[7].SetRect(840, 380, 960, 480);

	m_ui_btn_off[0].SetRect(0, 380, 120, 480);
	m_ui_btn_off[1].SetRect(120, 380, 240, 480);
	m_ui_btn_off[2].SetRect(240, 380, 360, 480);
	m_ui_btn_off[3].SetRect(360, 380, 480, 480);
	m_ui_btn_off[4].SetRect(480, 380, 600, 480);
	m_ui_btn_off[5].SetRect(600, 380, 720, 480);
	m_ui_btn_off[6].SetRect(720, 380, 840, 480);
	m_ui_btn_off[7].SetRect(840, 380, 960, 480);
	for (int iList = 0; iList < 8; iList++)
	{
		m_ui_btn_on[iList].Create(g_pd3dDevice);
		m_ui_btn_on[iList].CreateVertexBuffer(g_pd3dDevice);
		m_ui_btn_on[iList].Load(g_pd3dDevice, L"../../Data/UserInterface/ui_pet_btn_3_on.png");
		m_ui_btn_off[iList].Create(g_pd3dDevice);
		m_ui_btn_off[iList].CreateVertexBuffer(g_pd3dDevice);
		m_ui_btn_off[iList].Load(g_pd3dDevice, L"../../Data/UserInterface/ui_pet_btn_3_off.png");
	}

	m_StageUI.Init();
	return true;
}
bool JUserInterface::Frame()
{
	m_BackGround.Frame();
	if (RectInPt(m_ui_btn_on[1].m_rt, I_Input.m_MousePos))
	{
		if (I_Input.m_dwMouseState[0] == KEY_UP)
		{
			//m_EventUI.m_bShowEvent = !m_EventUI.m_bShowEvent;
		}
	}
	m_StageUI.Frame();
	return true;
}
bool JUserInterface::Render(ID3D11DeviceContext* context)
{
	m_BackGround.Render(context);
	//m_EventUI.Render(context);
	for (int iList = 0; iList < 8; iList++)
	{
		if (RectInPt(m_ui_btn_on[iList].m_rt, I_Input.m_MousePos))
		{
			m_ui_btn_on[iList].Render(context);
		}
		else
		{
			m_ui_btn_off[iList].Render(context);
		}
	}
	I_Write.RedDraw(L"스킬", 25, { 40,  415, 1100,1000 });
	I_Write.RedDraw(L"정보", 25, { 160, 415, 1100,1000 });
	I_Write.RedDraw(L"아이템", 25, { 265, 415, 1100,1000 });
	I_Write.RedDraw(L"가방", 25, { 400, 415, 1100,1000 });
	I_Write.RedDraw(L"길드", 25, { 520, 415, 1100,1000 });
	I_Write.RedDraw(L"랭킹", 25, { 640, 415, 1100,1000 });
	I_Write.RedDraw(L"결투장", 25, { 745, 415, 1100,1000 });
	I_Write.RedDraw(L"옵션", 25, { 880, 415, 1100,1000 });

	m_StageUI.Render();
	return true;
}
bool JUserInterface::Release()
{
	m_BackGround.Release();
	//m_EventUI.Release();
	for (int iList = 0; iList < 8; iList++)
	{
		m_ui_btn_on[iList].Release();
		m_ui_btn_off[iList].Release();
	}
	m_StageUI.Release();
	return true;
}

JUserInterface::JUserInterface()
{
}


JUserInterface::~JUserInterface()
{
}
