#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "JStd.h"
#pragma comment( lib, "IMM32.lib" )
class ime
{
private:
	//wstring m_Text; // 텍스트 한줄 저장
	wstring m_CompString; // 조합 중 문자열
	wstring m_CompWord; // 조합중 문자
	HWND m_hWnd = NULL;
	HIMC m_hIMC = NULL;
	bool m_bPlay = false;
public:
	void imeStart();
	void imeEnd();
public:
	wstring GetString();
	bool Set(HWND hWnd);
	int WndProc(MSG msg);
public:
	ime();
	virtual ~ime();
};

