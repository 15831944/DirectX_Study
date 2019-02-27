#include "JBitmap.h"	
void JBitmap::Set(HDC hdc)
{
	m_hScreenDC = hdc;
}
bool JBitmap::Load(const TCHAR* pszLoadFile)
{
	m_hBitmap = (HBITMAP)LoadImage(g_hInstance, pszLoadFile, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	GetObject(m_hBitmap, sizeof(BITMAP), &m_bitmapInfo);
	m_hMemDC = CreateCompatibleDC(m_hScreenDC);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	return true;
}
bool JBitmap::Draw(HDC hdc, fPOINT pos, RECT rt, DWORD opMode)
{
	BitBlt(hdc, pos.x, pos.y, rt.right, rt.bottom, m_hMemDC, rt.left, rt.top, opMode);
	return true;
}
bool JBitmap::Init()
{
	return true;
}
bool JBitmap::Frame()
{
	return true;
}
bool JBitmap::Render()
{
	return true;
}
bool JBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	ReleaseDC(g_hWnd, m_hMemDC);
	return true;
}

JBitmap::JBitmap()
{

}
JBitmap::~JBitmap()
{

}