#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "JStd.h"
#pragma comment( lib, "IMM32.lib" )
class ime
{
private:
	//wstring m_Text; // �ؽ�Ʈ ���� ����
	wstring m_CompString; // ���� �� ���ڿ�
	wstring m_CompWord; // ������ ����
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

