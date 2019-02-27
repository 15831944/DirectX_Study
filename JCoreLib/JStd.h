#pragma once
#include "JUtils.h"


#pragma comment( lib, "d3dx10.lib" )
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib") //확장 버전
#pragma comment(lib,"winmm.lib")   // timeGetTime

#pragma comment(lib,"D2D1.lib")
#pragma comment(lib, "DWrite.lib")
#pragma comment(lib, "dinput8.lib") // dxInput
#pragma comment(lib, "dxguid.lib") // guid
#pragma comment(lib, "JCoreLib.lib")

#define SAMPLE_BUFFER_SIZE 16
#define KEYSTATECOUNT 256

#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }
#define SAFE_DELETE(A)				{ if(A) { delete[] (A); (A)=NULL; } }

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern  RECT g_rtClient;
extern float g_fSecPerFrame;
extern DWORD g_dwFPS;
extern ID3D11Device* g_pd3dDevice;

class JStd
{
public:
	JStd();
	virtual ~JStd();
};

#define RUN int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int lpCmdShow) {	Sample core;if (core.SetWindow(hInstance, 800,600,L"Windows Sample"))	{		core.Run();		return 0;	}	return 1;}