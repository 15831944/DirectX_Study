#include "JCore.h"
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
	InitDevice();
	I_Timer.Init();
	I_Input.Init();
	I_Sound.Init();
	Init();
	I_Write.Set(m_pSurface);
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
	PreRender();
	Render();
	PostRender();
	return true;
}
bool JCore::GameRelease()
{

	Release();
	I_Timer.Release();
	I_Input.Release();
	I_Sound.Release();
	return true;
}
bool JCore::PreFrame()
{
	return true;
}
bool JCore::PreRender()
{
	JDevice::PreRender();
	I_Timer.Render();
	return true;
}
bool JCore::PostFrame()
{
	return true;
}
bool JCore::PostRender()
{
	JDevice::PostRender();
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
	Clear();
	return true;
}
JCore::JCore()
{
	m_bShowDebug = false;
}


JCore::~JCore()
{
}
