#include "JWindow.h"
#include "JInput.h"
HINSTANCE g_hInstance;
RECT g_rtClient;
HWND g_hWnd;
JWindow* g_pWindow = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (g_pWindow->MsgProc(hWnd, msg,
		wParam, lParam)	 > 0)
	{
		return 0;
	}
	switch (msg)
	{
	case WM_SIZE:
	{
		if (wParam != SIZE_MINIMIZED && g_pWindow != NULL)
		{
			UINT width = LOWORD(lParam);
			UINT height = HIWORD(lParam);
			g_pWindow->ResizeClient(width, height);
		}
	}break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
LRESULT JWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
void JWindow::CenterWindow()
{
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int x = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2;
	int y = (iScreenHeight - (m_rtWindow.bottom - m_rtWindow.top)) / 2;
	RECT rt = { 0,0,m_rtWindow.right, m_rtWindow.bottom };
	AdjustWindowRect(&rt, GetWindowStyle(m_hWnd), FALSE);

	MoveWindow(m_hWnd, x, y,
		rt.right - rt.left,
		rt.bottom - rt.top, true);
}
bool	JWindow::ResizeClient(UINT iWidth, UINT iHeight)
{
	GetClientRect(m_hWnd, &m_rtClient);
	g_rtClient = m_rtClient;
	return true;
}
bool JWindow::MFCGameRun()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
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
	return true;
}
bool JWindow::Run()
{
	GameInit();
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
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
	if (RegisterClassEx(&wc) == false) 
		return false;

	RECT rt = { 0,0,Width,Height };
	m_rtWindow = rt;
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, ClassName, ClassName, WS_OVERLAPPEDWINDOW, 0, 0, rt.right - rt.left, rt.bottom - rt.top, NULL, NULL, m_hInstance, NULL);
	if (m_hWnd == NULL) return false;
	g_hWnd = m_hWnd;

	GetWindowRect(m_hWnd, &m_rtWindow);
	GetClientRect(m_hWnd, &m_rtClient);
	g_rtClient = m_rtClient;

	CenterWindow();
	UpdateWindow(m_hWnd);
	ShowWindow(m_hWnd, SW_SHOW);
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
	g_pWindow	= this;
}


JWindow::~JWindow()
{
}
