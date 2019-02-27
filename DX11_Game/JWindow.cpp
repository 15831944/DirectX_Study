#include "JWindow.h"
#include "JInput.h"
HINSTANCE g_hInstance;
RECT g_rtWindow;
HWND g_hWnd;
JWindow* g_pWindow = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_pWindow->MsgProc(hWnd, msg, wParam, lParam);
}
LRESULT JWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		//ReziseDevice(width, height);
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
bool JWindow::Run()
{
	GameInit();
	MSG msg;
	while (!I_Input.KeyCheck(VK_ESCAPE))
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
			MsgEvent(msg);
		}
		else
		{
			GameRun();
		}
	}
	GameRelease();
	return true;
}
bool JWindow::SetWindow(HINSTANCE hInstance, int Width, int	Height,	LPCWSTR ClassName)
{
	m_hInstance = hInstance;
	g_hInstance = hInstance;

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(m_hInstance, IDI_ERROR);
	wc.hCursor = LoadCursor(m_hInstance, IDC_IBEAM);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ClassName;
	wc.hIconSm = LoadIcon(m_hInstance, IDI_ERROR);
	if (RegisterClassEx(&wc) == false) return false;

	RECT rt = { 0,0,Width,Height };
	m_rtWindow = rt;
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, ClassName, ClassName, WS_OVERLAPPEDWINDOW, 500, 200, rt.right - rt.left, rt.bottom - rt.top, NULL, NULL, m_hInstance, NULL);
	if (m_hWnd == NULL) return false;
	GetClientRect(m_hWnd, &rt);

	ShowWindow(m_hWnd, SW_SHOW);
	g_rtWindow = m_rtWindow;
	g_hWnd = m_hWnd;
	return true;
}
bool JWindow::GameRun()
{
	return true;
}
bool JWindow::GameInit()
{
	return true;
}
bool JWindow::GameRelease()
{
	return true;
}
bool JWindow::Init()
{
	return true;
}
bool JWindow::Frame()
{
	return true;
}
bool JWindow::Render()
{
	return true;
}
bool JWindow::Release()
{
	return true;
}

JWindow::JWindow()
{
	m_hInstance = NULL;
	m_hWnd		= NULL;
	g_pWindow	= this;
}


JWindow::~JWindow()
{
}
