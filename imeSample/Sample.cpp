#include "JCore.h"
#include "ime.h"
static char* wtom(wchar_t* str)
{
	//반환할 char* 변수 선언
	char* pStr;
	//입력받은 wchar_t 변수의 길이를 구함
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	//char* 메모리 할당
	pStr = new char[strSize];
	//형 변환 
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}

static wchar_t* mtow(char* str)
{
	//wchar_t형 변수 선언
	wchar_t* pStr;
	//멀티 바이트 크기 계산 길이 반환
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
	//wchar_t 메모리 할당
	pStr = new WCHAR[strSize];
	//형 변환
	MultiByteToWideChar(CP_ACP, 0, str, (int)strlen(str) + 1, pStr, strSize);
	return pStr;
}
class Sample : public JCore
{
public:
	wstring str;
	ime ime;
public:
	void MsgEvent(MSG msg)
	{
		ime.WndProc(msg);
	}
	bool Init()
	{
		ime.Set(m_hWnd);
		//ime.imeStart();
		return true;
	}
	bool Frame()
	{
		if (I_Input.KeyCheck(VK_RETURN) == KEY_PUSH)
		{
			ime.imeStart();
		}
		if (I_Input.KeyCheck('W') == KEY_PUSH)
		{
			ime.imeEnd();
		}
		return true;
	}
	bool Render()
	{
		str = ime.GetString();
		JWrite::GetInstance().Draw(str.c_str(), 15, {0,0,800,600});
		return true;
	}
	bool Release()
	{
		return true;
	}
};
RUN;