#include "JWrite.h"
bool JWrite::Begin()
{
	m_pRT->BeginDraw();
	return true;
}
bool JWrite::End()
{
	m_pRT->EndDraw();
	return true;
}
bool JWrite::Draw(const TCHAR* text, float size, fRECT rt)
{
	CreateTextFormat(size);
	D2D1_RECT_F WriteRT;
	WriteRT.left = rt.left;
	WriteRT.right = rt.right;
	WriteRT.bottom = rt.bottom;
	WriteRT.top = rt.top;
	Begin();
	m_pRT->DrawTextW(text, wcslen(text), m_pTextFormat, WriteRT, m_pBlackBrush);
	End();
	return true;
}
bool JWrite::RedDraw(const TCHAR* text, float size, fRECT rt)
{
	CreateTextFormat(size);
	D2D1_RECT_F WriteRT;
	WriteRT.left = rt.left;
	WriteRT.right = rt.right;
	WriteRT.bottom = rt.bottom;
	WriteRT.top = rt.top;
	Begin();
	m_pRT->DrawTextW(text, wcslen(text), m_pTextFormat, WriteRT, m_pRedBrush);
	End();
	return true;
}
bool JWrite::BlueDraw(const TCHAR* text, float size, fRECT rt)
{
	CreateTextFormat(size);
	D2D1_RECT_F WriteRT;
	WriteRT.left = rt.left;
	WriteRT.right = rt.right;
	WriteRT.bottom = rt.bottom;
	WriteRT.top = rt.top;
	Begin();
	m_pRT->DrawTextW(text, wcslen(text), m_pTextFormat, WriteRT, m_pBlueBrush);
	End();
	return true;
}
bool JWrite::SetColor()
{
	m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &m_pRedBrush);
	m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBlackBrush);
	m_pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &m_pBlueBrush);
	return true;
}
bool JWrite::Set(IDXGISurface1*	pSurface)
{
	HRESULT hr;
	hr = CreateFactory();
	hr = CreateWriteFactory();
	hr = CreateTextFormat(20);
	hr = CreateDeviceResource(pSurface);
	return true;
}
bool JWrite::Init()
{
	return true;
}
bool JWrite::Release()
{
	m_pd2dFactory->Release();
	m_pRT->Release();
	m_pWriteFactory->Release();
	m_pTextFormat->Release();
	m_pBlackBrush->Release();
	m_pRedBrush->Release();
	return true;
}
HRESULT JWrite::CreateFactory()
{
	HRESULT hr = S_OK;
	if (FAILED(hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pd2dFactory)))
	{
		return hr;
	}
	return hr;
}
HRESULT	JWrite::CreateWriteFactory()
{
	HRESULT hr = S_OK;
	if(FAILED(hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)(&m_pWriteFactory))))
	{
		return hr;
	}
	return hr;
}
HRESULT JWrite::CreateTextFormat(float size)
{
	HRESULT hr = S_OK;

	if (FAILED(hr = m_pWriteFactory->CreateTextFormat(L"µµÇöÃ¼",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_MEDIUM,
		size,
		L"ko-kr",
		&m_pTextFormat)))
	{
		return hr;
	}
	return hr;
}

HRESULT JWrite::CreateDeviceResource(IDXGISurface1*	pSurface)
{
	HRESULT hr;
	D2D1_RENDER_TARGET_PROPERTIES properties = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
		m_fdpiX,
		m_fdpiY);
	if (FAILED(hr = m_pd2dFactory->CreateDxgiSurfaceRenderTarget(pSurface, properties, &m_pRT)))
	{
		return hr;
	}
	SetColor();
	return hr;
}
JWrite::JWrite()
{
	m_fdpiX = 0.0f;
	m_fdpiY = 0.0f;
}


JWrite::~JWrite()
{
}
