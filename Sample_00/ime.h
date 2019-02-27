#pragma once
#include "JStd.h"
#include <windows.h>
#include <string>
#define MAX_CANDIDATE_LENGTH 256
#define COUNTOF(a) ( sizeof( a ) / sizeof( ( a )[0] ) )

#define LANG_CHT	MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL)

#define INDICATOR_NON_IME	0
#define INDICATOR_CHS		1
#define INDICATOR_CHT		2
#define INDICATOR_KOREAN	3
#define INDICATOR_JAPANESE	4
#define GETLANG()		LOWORD(g_hklCurrent)
#define GETPRIMLANG()	((WORD)PRIMARYLANGID(GETLANG()))
#define GETSUBLANG()	SUBLANGID(GETLANG())
typedef basic_string<TCHAR>::iterator	T_ITOR;
class ime
{
public:
	static ime* Instance;
	static ime* Get()
	{
		if (Instance == nullptr)
		{
			Instance = new ime();
			return Instance;
		}
		return Instance;
	}
public:
	T_STR    m_CompString;
	T_STR    m_CompWord;
	T_STR    m_CurrentString;

	wstring 	m_pszIndicatior;
	HWND		m_hWndMain;
	HIMC		m_himcOrg;

	bool		m_bInitialized;
	HMODULE		m_hImmDll;
	DWORD		m_dwConversion;
	int			m_nComSize;

public:
	bool		ImeUi_IsEnabled(void);
	bool		ImeUi_Initialize(HWND hwnd, bool bDisable = false);
	void		ImeUi_Uninitialize();
	void		CheckInputLocale();

public:
	const TCHAR*		GetStringBuffer();
	void		Uninitialize();
	void		Initialize(HWND hWnd);
	void		ResetCompositionString();
	// 문자 조합 위도우 위치
	void		SetIMECompPos(int xpos, int ypos);
	int			WndProc(const MSG message);
public:
	// WM_IME_COMPOSITION 메세지만 사용할 때
	BOOL		OnImeComposition(WPARAM wParam, LPARAM lParam);
public:
	ime();
	virtual ~ime();
};