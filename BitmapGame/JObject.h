#pragma once
#include "JStd.h"
#include "JBitmapMgr.h"
class JObject : public JBitmap
{
public:
	HDC m_hScreenDC;
	HDC m_hOffScreenDC;
	JBitmap* m_pBitmap;
	JBitmap* m_pBitmapMask;
	int m_iBitmap;
	int m_iBitmapMask;
	fPOINT m_pos;
	fPOINT m_CenterPos;
	RECT m_rt;
	RECT m_rtCollision;
	bool m_bBitmapMask;
	int m_iDirection[1];
	float m_fSpeed;
public:
	bool Load(HDC hScreenDC, HDC hOffScreenDC, const TCHAR* pszLoadFile, const TCHAR* pszLoadMaskFile = NULL);
	void SetRectPos(RECT rt, fPOINT pos);
	bool RotateBit(float fAngle);
	HBITMAP GetRotationBitmap(HDC hdc, float fAngle, int iWidth, int iHeight);
public:
	void Left();
	void Right();
	void Up();
	void Down();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:

public:
	JObject();
	~JObject();
};

