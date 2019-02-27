#pragma once
/* Surface 받아온 후 Draw */
#include "JStd.h"
#include "D2D1.h"
#include "DWrite.h"

#pragma comment(lib,"D2D1.lib")
#pragma comment(lib, "DWrite.lib")
class JWrite : public JSingleton<JWrite>
{
public:
	friend class JSingleton<JWrite>;
public:
	float m_fdpiX;
	float m_fdpiY;
public:
	ID2D1Factory*			m_pd2dFactory;
	ID2D1RenderTarget*		m_pRT;
	IDWriteFactory*			m_pWriteFactory;
	IDWriteTextFormat*		m_pTextFormat;
	ID2D1SolidColorBrush*	m_pBlackBrush;
	ID2D1SolidColorBrush*	m_pRedBrush;
	ID2D1SolidColorBrush*	m_pBlueBrush;
	ID2D1SolidColorBrush*   m_pGreenBrush;
public:
	HRESULT					CreateFactory();
	HRESULT					CreateWriteFactory();
	HRESULT					CreateTextFormat(float size);
	HRESULT					CreateDeviceResource(IDXGISurface1*	pSurface);
	bool Set(IDXGISurface1*	pSurface);
	bool SetColor();
	bool Draw(const TCHAR* text, float size, fRECT rt = { 0,0,800,600 });
	bool RedDraw(const TCHAR* text, float size, fRECT rt = { 0,0,800,600 });
	bool GreenDraw(const TCHAR* text, float size, fRECT rt = { 0,0,800,600 });
	bool BlueDraw(const TCHAR* text, float size, fRECT rt = { 0,0,800,600 });
	bool Begin();
	bool End();
public:
	bool Init();
	bool Release();
public:
	JWrite();
	virtual ~JWrite();
};
#define I_Write JWrite::GetInstance()