#include "ime.h"

bool ime::Set(HWND hWnd)
{
	if (hWnd == nullptr) return false;
	m_hWnd = hWnd;
	m_hIMC = ImmGetContext(m_hWnd);
}
wstring ime::GetString()
{
	return m_CompString + m_CompWord;
}
void ime::imeStart()
{
	m_bPlay = true;
	m_CompString.clear();
	m_CompWord.clear();
}
void ime::imeEnd()
{
	m_bPlay = false;
	m_CompString.clear();
	m_CompWord.clear();
}
int ime::WndProc(MSG msg)
{
	if (!m_bPlay) return 1;
	int len;
	switch (msg.message)
	{
	case WM_IME_STARTCOMPOSITION: // ���� ����
	{
		m_CompWord.clear(); // ���� �� ���� �ʱ�ȭ
	}
	case WM_IME_ENDCOMPOSITION: // ���� ��
	{
		m_CompWord = msg.wParam; // �ϼ����� �߰�
	}
	case WM_IME_COMPOSITION: // ���� ��
	{
		//if (msg.lParam & GCS_RESULTSTR) // �ϼ��Ǹ�?
		//{
			//TCHAR szBackup[10] = {0,};
			//len = ImmGetCompositionString(m_hIMC, GCS_RESULTSTR, NULL, 0); // IME��Ʈ�����̸�����
			
			//ImmGetCompositionString(m_hIMC, GCS_RESULTSTR, szBackup, len); // �ϼ��� �����Է�
			
			//if (len > 0)
			//{
			//	m_CompString += szBackup; // �Ʒ� WM_CHAR���� 2�� �߰���.....
			//}
			
		//}
		//else
		if (msg.lParam & GCS_COMPSTR) // ���� �� �̸�
		{
			TCHAR szBackup[10] = {0,};
			len = ImmGetCompositionString(m_hIMC, GCS_COMPSTR, NULL, 0); // ���� ���� ���� ����

			ImmGetCompositionString(m_hIMC, GCS_COMPSTR, szBackup, len); // ���ڿ� �Է�
			m_CompWord = szBackup;
		}
		ImmReleaseContext(m_hWnd, m_hIMC); // �ڵ��ȯ
		return 0;
	}
	case WM_CHAR: // ���ڳѾ��
	{
		switch (msg.wParam)
		{
		case VK_BACK: // backspace
		{
			if (m_CompWord.size() > 0)
			{
				m_CompWord.pop_back(); // �ѱ��� ����
			}
			else if (m_CompString.size() > 0)
			{
				m_CompString.pop_back();
			}
			break;
		}
		case VK_RETURN: // Enter ����
		{
			m_CompString.clear();
			m_CompWord.clear();
			break;
		}
		default:
		{
			m_CompString += msg.wParam;
			break;
		}
		}
		return 0;
	}
	}
	return 1;
}

ime::ime()
{
}


ime::~ime()
{
}
