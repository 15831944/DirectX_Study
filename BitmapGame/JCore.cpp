#include "JCore.h"
HDC g_hScreenDC;
HDC g_hOffScreenDC;
void JCore::MsgEvent(MSG msg)
{
	I_Input.MsgEvent(msg);
}
bool JCore::GameRun()
{
	GameFrame();
	GameRender();
	return true;
}
bool JCore::GameInit()
{
	I_Timer.Init();
	I_Input.Init();
	I_Sound.Init();

	m_hScreenDC = GetDC(m_hWnd);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);

	m_hOffScreenBitmap = CreateCompatibleBitmap(m_hScreenDC, m_rtWindow.right + 600.0f, m_rtWindow.bottom);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);

	Init();

	g_hScreenDC = m_hScreenDC;
	g_hOffScreenDC = m_hOffScreenDC;
	return true;
}
bool JCore::GameFrame()
{
	if (I_Input.KeyCheck('V') == KEY_PUSH)
	{
		m_bShowDebug = !m_bShowDebug;
	}
	I_Timer.Frame();
	I_Input.Frame();
	I_Sound.Frame();
	Frame();
	return true;
}
bool JCore::GameRender()
{
	Render();
	I_Timer.Render();
	I_Input.Render();
	I_Sound.Render();
	if (m_bShowDebug)
	{
		TextOut(g_hOffScreenDC, 0, 20, I_Input.m_szBuffer, wcslen(I_Input.m_szBuffer));
		TextOut(g_hOffScreenDC, 0, 0, I_Timer.m_szBuffer, wcslen(I_Timer.m_szBuffer));
	}


	BitBlt(m_hScreenDC, 0, 0, m_rtWindow.right + 600, m_rtWindow.bottom, m_hOffScreenDC, m_rtWindow.left,m_rtWindow.top,SRCCOPY);
	return true;
}
bool JCore::GameRelease()
{

	Release();
	I_Timer.Release();
	I_Input.Release();
	I_Sound.Release();
	SelectObject(m_hOffScreenDC, m_hOldBitmap);
	ReleaseDC(m_hWnd, m_hOffScreenDC);
	
	return true;
}
bool JCore::Init()
{
	return true;
}
bool JCore::Frame()
{
	return true;
}
bool JCore::Render()
{
	return true;
}
bool JCore::Release()
{
	return true;
}

JCore::JCore()
{
	m_bShowDebug = false;
}


JCore::~JCore()
{
}
