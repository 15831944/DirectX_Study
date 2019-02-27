#pragma once
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <map>
#include <vector>

#pragma comment(lib,"winmm.lib") // timeGetTime
using namespace std;
struct fPOINT
{
	float x;
	float y;
};
struct Vector2
{
	float x;
	float y;
	float LengthSquared()
	{
		return (x*x + y * y);
	}
	float Length()
	{
		return (float)sqrt(LengthSquared());
	}
	Vector2 Normal()
	{
		float invertLength = 1.0f / Length();
		return Vector2(x*invertLength, y*invertLength);
	}
	Vector2(int ix, int iy)
	{
		x = ix; y = iy;
	}
	Vector2()
	{
		
	}
};
template<class T>
class JSingleton
{
public:
	static T& GetInstance()
	{
		static T SingleInstance;
		return SingleInstance;
	}
};
class JBasis
{
public:
	virtual bool Init()
	{
		return true;
	}
	virtual bool Frame()
	{
		return true;
	}
	virtual bool Render()
	{
		return true;
	}
	virtual bool Release()
	{
		return true;
	}
};

static bool RectInRect(RECT rtDesk, RECT rtSrc)
{
	POINT  cDesk, cSrc, Radius, DeskRadius, SrcRadius;
	cDesk.x = (rtDesk.left + rtDesk.right) / 2;
	cDesk.y = (rtDesk.top + rtDesk.bottom) / 2;
	cSrc.x = (rtSrc.left + rtSrc.right) / 2;
	cSrc.y = (rtSrc.top + rtSrc.bottom) / 2;
	Radius.x = abs(cDesk.x - cSrc.x);
	Radius.y = abs(cDesk.y - cSrc.y);
	DeskRadius.x = (rtDesk.right - rtDesk.left) / 2;
	DeskRadius.y = (rtDesk.bottom - rtDesk.top) / 2;
	SrcRadius.x = (rtSrc.right - rtSrc.left) / 2;
	SrcRadius.y = (rtSrc.bottom - rtSrc.top) / 2;
	if (Radius.x <= (DeskRadius.x + SrcRadius.x) &&
		Radius.y <= (DeskRadius.y + SrcRadius.y))
	{
		return true;
	}
	return false;
}
static bool RectInPt(RECT rt, POINT pt)
{
	if (rt.left <= pt.x && rt.right >= pt.x)
	{
		if (rt.top <= pt.y && rt.bottom >= pt.y)
		{
			return true;
		}
	}
	return false;
}
static bool RectInfPt(RECT rt, fPOINT pt)
{
	if (rt.left <= pt.x && rt.right >= pt.x)
	{
		if (rt.top <= pt.y && rt.bottom >= pt.y)
		{
			return true;
		}
	}
	return false;
}

class JStd
{
public:
	JStd();
	virtual ~JStd();
};
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern RECT g_rtWindow;
extern float g_fSecPerFrame;
extern DWORD g_dwFPS;
extern HDC g_hScreenDC;
extern HDC g_hOffScreenDC;
extern fPOINT g_AllPos;
static int g_iArrowCount = 0;
static fPOINT g_EnemyPos;

#define RUN int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow) {	Sample core;if (core.SetWindow(hInstance, 800,600,L"Windows Sample"))	{		core.Run();		return 0;	}	return 1;}