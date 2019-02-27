#pragma once
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <map>
#include <vector>
#include <d3d11.h>
#include <d3dx11.h>
#include <string>

#pragma comment(lib,"dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")//확장 버전
#pragma comment(lib,"winmm.lib") // timeGetTime
using namespace std;
typedef basic_string<TCHAR> T_STR;
typedef vector<T_STR> T_STR_Vector;
struct fRECT
{
	float left;
	float top;
	float right;
	float bottom;
	fRECT& operator +=(float a)
	{
		left += a;
		top += a;
		right += a;
		bottom += a;
		return *this;
	}
};
struct fPOINT
{
	float x;
	float y;
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
static TCHAR* NameDivide(const TCHAR* pszFileName)
{
	TCHAR szFileName[MAX_PATH] = { 0, };
	TCHAR Dirve[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR FileName[MAX_PATH] = { 0, };
	TCHAR FileExt[MAX_PATH] = { 0, };
	if (pszFileName != NULL)
	{
		_tsplitpath_s(pszFileName, Dirve, Dir, FileName, FileExt);
		_stprintf_s(szFileName, _T("%s%s"), FileName, FileExt);
	}
	return szFileName;
}
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
static bool RectInRect(fRECT rtDesk, fRECT rtSrc)
{
	fRECT rtdesk = rtDesk; fRECT rtsrc = rtSrc;
	rtdesk += 1.0f; rtsrc += 1.0f;
	fPOINT  cDesk, cSrc, Radius, DeskRadius, SrcRadius;
	cDesk.x = (rtdesk.left + rtdesk.right) / 2;
	cDesk.y = (rtdesk.top + rtdesk.bottom) / 2;
	cSrc.x = (rtsrc.left + rtsrc.right) / 2;
	cSrc.y = (rtsrc.top + rtsrc.bottom) / 2;
	Radius.x = abs(cDesk.x - cSrc.x);
	Radius.y = abs(cDesk.y - cSrc.y);
	DeskRadius.x = (rtdesk.right - rtdesk.left) / 2;
	DeskRadius.y = (rtdesk.bottom - rtdesk.top) / 2;
	SrcRadius.x = (rtsrc.right - rtsrc.left) / 2;
	SrcRadius.y = (rtsrc.bottom - rtsrc.top) / 2;
	if (Radius.x <= (DeskRadius.x + SrcRadius.x) &&
		Radius.y <= (DeskRadius.y + SrcRadius.y))
	{
		return true;
	}
	return false;
}
static bool DxRectInRect(fRECT rtDesk, fRECT rtSrc)
{
	fRECT rtdesk = rtDesk; fRECT rtsrc = rtSrc;
	fPOINT  cDesk, cSrc, Radius;
	cDesk.x = rtdesk.left + (rtdesk.right - rtdesk.left) / 2;
	cDesk.y = rtdesk.top + (rtdesk.bottom - rtdesk.top) / 2;
	cSrc.x = rtsrc.left + (rtsrc.right - rtsrc.left) / 2;
	cSrc.y = rtsrc.top + (rtsrc.bottom - rtsrc.top) / 2;
	//float fX = cDesk.x - cSrc.x;
	Radius.x = abs(cDesk.x - cSrc.x);
	Radius.y = abs(cDesk.y - cSrc.y);
	if (Radius.x <= 40.0f)
	{
		return true;
	}
	return false;
	//DeskRadius.x = (rtdesk.right - rtdesk.left) / 2;
	//DeskRadius.y = (rtdesk.bottom - rtdesk.top) / 2;
	//SrcRadius.x = (rtsrc.right - rtsrc.left) / 2;
	//SrcRadius.y = (rtsrc.bottom - rtsrc.top) / 2;
	//if (Radius.x <= (DeskRadius.x + SrcRadius.x) &&
	//	Radius.y <= (DeskRadius.y + SrcRadius.y))
	//{
	//	return true;
	//}
	//return false;
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
static bool RectInPt(fRECT rt, POINT pt)
{
	fRECT temp;
	temp.left = rt.left;
	temp.top = rt.top;
	temp.right = rt.left + rt.right;
	temp.bottom = rt.top + rt.bottom;
	if (temp.left <= pt.x && temp.right >= pt.x)
	{
		if (temp.top <= pt.y && temp.bottom >= pt.y)
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
extern ID3D11Device* g_pd3dDevice;

#define RUN int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow) {	Sample core;if (core.SetWindow(hInstance, 800,600,L"Windows Sample"))	{		core.Run();		return 0;	}	return 1;}