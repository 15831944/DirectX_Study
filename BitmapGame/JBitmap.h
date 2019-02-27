#pragma once
#include "JStd.h"
class JBitmap
{
public:
	wstring m_szName;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	HDC m_hMemDC;
	HDC m_hScreenDC;
	BITMAP m_bitmapInfo;
public:
	void Set(HDC hdc);
	bool Load(const TCHAR* pszLoadFile);
	bool Draw(HDC hdc, fPOINT pos, RECT rt, DWORD opMode);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	
public:
	JBitmap();
	virtual ~JBitmap();
};

