#pragma once
#include "JUtills.h"

#pragma comment( lib, "d3dx10.lib" )
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib") //확장 버전
#pragma comment(lib,"winmm.lib")   // timeGetTime

#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }
#define SAFE_DELETE(A)				{ if(A) { delete[] (A); (A)=NULL; } }