#include "JCore.h"
#include "ime.h"
static char* wtom(wchar_t* str)
{
	//��ȯ�� char* ���� ����
	char* pStr;
	//�Է¹��� wchar_t ������ ���̸� ����
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	//char* �޸� �Ҵ�
	pStr = new char[strSize];
	//�� ��ȯ 
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}

static wchar_t* mtow(char* str)
{
	//wchar_t�� ���� ����
	wchar_t* pStr;
	//��Ƽ ����Ʈ ũ�� ��� ���� ��ȯ
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
	//wchar_t �޸� �Ҵ�
	pStr = new WCHAR[strSize];
	//�� ��ȯ
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