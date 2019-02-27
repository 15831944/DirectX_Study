#include "JObject.h"

bool JObject::RotateBit(float fAngle)
{
	int iOffWidth = m_rt.right;
	int iOffHeight = m_rt.bottom;
	if (iOffWidth > iOffHeight)
	{
		iOffHeight = iOffWidth;
	}
	else
	{
		iOffWidth = iOffHeight;
	}
	double fDiagonal = sqrt((m_rt.right * m_rt.right) + (m_rt.bottom * m_rt.bottom));
	HBITMAP hColorBitmap = GetRotationBitmap(m_pBitmap->m_hMemDC, fAngle, fDiagonal, fDiagonal);
	HBITMAP hMaskBitmap = GetRotationBitmap(m_pBitmapMask->m_hMemDC, fAngle, iOffWidth, iOffHeight);

	HDC m_hMemColorDC = CreateCompatibleDC(m_hScreenDC);
	HDC m_hMemMaskDC = CreateCompatibleDC(m_hScreenDC);

	HBITMAP hOldColorBitmap = (HBITMAP)SelectObject(m_hMemColorDC, hColorBitmap);
	HBITMAP hOldMaskBitmap = (HBITMAP)SelectObject(m_hMemMaskDC, hMaskBitmap);
	BitBlt(m_hOffScreenDC, m_CenterPos.x, m_CenterPos.y, iOffWidth, iOffHeight, m_hMemMaskDC, 0, 0,SRCAND);
	BitBlt(m_hOffScreenDC, m_CenterPos.x, m_CenterPos.y, iOffWidth, iOffHeight, m_hMemColorDC, 0, 0, SRCINVERT);
	BitBlt(m_hOffScreenDC, m_CenterPos.x, m_CenterPos.y, iOffWidth, iOffHeight, m_hMemMaskDC, 0, 0,SRCINVERT);
	BitBlt(m_hOffScreenDC, m_pos.x, m_pos.y, iOffWidth, iOffHeight, m_hMemColorDC, 0, 0, SRCCOPY);

	DeleteObject(SelectObject(m_hMemColorDC, hOldColorBitmap));
	//DeleteObject(SelectObject(m_hMemMaskDC, hOldMaskBitmap));
	DeleteDC(m_hMemColorDC);
	DeleteDC(m_hMemMaskDC);
	return true;
}
HBITMAP JObject::GetRotationBitmap(HDC hdc, float fAngle, int iWidth, int iHeight)
{
	HDC dc = CreateCompatibleDC(m_hScreenDC);
	HBITMAP hbmResult = CreateCompatibleBitmap(m_hScreenDC, iWidth, iHeight);
	HBITMAP hOld = (HBITMAP)SelectObject(dc, hbmResult);

	// 흰색으로 초기화해놓고 돌림
	HBRUSH hbrBack = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH hbrOld = (HBRUSH)SelectObject(dc, hbrBack);
	PatBlt(dc, 0, 0, iWidth, iHeight, PATCOPY);
	DeleteObject(SelectObject(dc, hbrOld));
	// 화면좌표계를 직각좌표계로 바꾼다
	int  iOldMode = SetGraphicsMode(dc, GM_ADVANCED);
										
	float fRadian = fAngle * 3.141592f / 180.0f;
	float fSine = sin(fRadian);
	float fCosine = cos(fRadian);

	XFORM xForm;
	xForm.eM11 = fCosine;
	xForm.eM12 = -fSine;
	xForm.eM21 = fSine;
	xForm.eM22 = fCosine;

	xForm.eDx = iWidth / 2.0f;
	xForm.eDy = iHeight / 2.0f;

	// 2d행렬 곱(픽셀마다)
	SetWorldTransform(dc, &xForm);

	BitBlt(dc, -(m_rt.right / 2.0f), -(m_rt.bottom / 2.0f),
	m_rt.right, m_rt.bottom, hdc,
	m_rt.left, m_rt.top, SRCCOPY);

	HBITMAP hbmOld = (HBITMAP)SelectObject(dc, hOld);
	DeleteObject((HBITMAP)SelectObject(dc, hOld));
	DeleteObject(dc);
	xForm.eM11 = 1; xForm.eM12 = 0;
	xForm.eM21 = 0; xForm.eM22 = 1;
	xForm.eDx = 0; xForm.eDy = 0;
	SetWorldTransform(dc, &xForm);
	SetGraphicsMode(dc, iOldMode);
	return hbmResult;
}
bool JObject::Load(HDC hScreenDC, HDC hOffScreenDC, const TCHAR* pszLoadFile, const TCHAR* pszLoadMaskFile)
{
	m_hScreenDC = hScreenDC;
	if (pszLoadMaskFile != NULL)
	{
		m_bBitmapMask = true;
		m_hOffScreenDC = hOffScreenDC;
		m_iBitmapMask = I_BitMgr.Add(pszLoadMaskFile);
		m_pBitmapMask = I_BitMgr.GetPtr(m_iBitmapMask);
		m_pBitmapMask->Set(hScreenDC);
		if (m_iBitmapMask < 0) return false;
	}
	
	m_hOffScreenDC = hOffScreenDC;
	m_iBitmap = I_BitMgr.Add(pszLoadFile);
	m_pBitmap = I_BitMgr.GetPtr(m_iBitmap);
	m_pBitmap->Set(hScreenDC);
	if (m_iBitmap >= 0) return true;
	return false;
}
void JObject::SetRectPos(RECT rt, fPOINT pos)
{
	m_pos = pos;
	m_rt = rt;
	m_CenterPos.x = m_pos.x + (m_rt.right / 2);
	m_CenterPos.y = m_pos.y + (m_rt.bottom / 2);
	m_rtCollision.left = m_pos.x;
	m_rtCollision.top = m_pos.y;
	m_rtCollision.right = m_rt.right;
	m_rtCollision.bottom = m_rt.bottom;
}
bool JObject::Init()
{
	return true;
}
bool JObject::Frame()
{
	return true;
}
bool JObject::Render()
{
	if (m_bBitmapMask == false)
	{
		m_pBitmap->Draw(m_hOffScreenDC, m_CenterPos, m_rt, SRCCOPY);
	}
	if (m_bBitmapMask == true)
	{
		m_pBitmapMask->Draw(m_hOffScreenDC, m_CenterPos, m_rt, SRCAND);
		m_pBitmap->Draw(m_hOffScreenDC, m_CenterPos, m_rt, SRCINVERT);
		m_pBitmapMask->Draw(m_hOffScreenDC, m_CenterPos, m_rt, SRCINVERT);
	}
	return true;
}
bool JObject::Release()
{
	m_pBitmap->Release();
	return true;
}
JObject::JObject()
{
	m_pos.x = 0;
	m_pos.y = 0;
	m_bBitmapMask = false;
	m_iDirection[0] = 1;
	m_iDirection[1] = 1;
}


JObject::~JObject()
{
}
