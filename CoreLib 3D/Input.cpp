#include "Input.h"

bool Input::isDebug = false;
//bool Input::isChatting = false;
short	  Input::m_WheelScroll = 0;
short	  Input::m_tempWheelScroll = 0;
POINT	  Input::m_Cursor = { 0, };
POINT	  Input::m_prevCursor = { 0, };
EKeyState Input::m_KeyState[256]	 = { EKeyState::FREE, };
EKeyState Input::m_MouseState[3]	 = { EKeyState::FREE, };
EKeyState Input::m_MousePrevState[3] = { EKeyState::FREE, };

bool Input::Init() noexcept
{
	return true;
}

bool Input::Frame() noexcept
{
	// ��ũ�� ��ǥ ���, ��ũ��->Ŭ���̾�Ʈ ��ǥ ��ȯ
	m_prevCursor = m_Cursor;
	GetCursorPos(&m_Cursor);
	ScreenToClient(Window::m_hWnd, &m_Cursor);
	// ���콺 �� ��
	m_WheelScroll = m_tempWheelScroll;
	m_tempWheelScroll = 0;

	if (KeyCheck(VK_ESCAPE) == EKeyState::DOWN)
	{
		isDebug = !isDebug;
		//isChatting = false;
	}

	KeyCheck(VK_F1);		KeyCheck(VK_F2);		KeyCheck(VK_F3);		KeyCheck(VK_F4);
	KeyCheck(VK_F5);		KeyCheck(VK_F6);		KeyCheck(VK_F7);		KeyCheck(VK_F8);
	KeyCheck(VK_F9);		KeyCheck(VK_F10);		KeyCheck(VK_F11);		KeyCheck(VK_F12);
	KeyCheck(VK_LEFT);		KeyCheck(VK_RIGHT);		KeyCheck(VK_UP);		KeyCheck(VK_DOWN);
	KeyCheck(VK_SPACE);		KeyCheck(VK_SHIFT);		KeyCheck(VK_ESCAPE);	KeyCheck(VK_TAB);
	KeyCheck(VK_INSERT);	KeyCheck(VK_DELETE);	KeyCheck(VK_HOME);		KeyCheck(VK_END);
	KeyCheck(VK_NUMPAD0);	KeyCheck(VK_NUMPAD1);	KeyCheck(VK_NUMPAD2);	KeyCheck(VK_NUMPAD3);
	KeyCheck(VK_NUMPAD4);	KeyCheck(VK_NUMPAD5);	KeyCheck(VK_NUMPAD6);	KeyCheck(VK_NUMPAD7);
	KeyCheck(VK_NUMPAD8);	KeyCheck(VK_NUMPAD9);	KeyCheck(VK_NUMLOCK);
	KeyCheck(VK_ADD);		KeyCheck(VK_SUBTRACT);	KeyCheck(VK_DIVIDE);
	KeyCheck(VK_RETURN);	KeyCheck(VK_CONTROL);

	KeyCheck('1');		KeyCheck('2');		KeyCheck('3');		KeyCheck('4');
	KeyCheck('Q');		KeyCheck('W');		KeyCheck('E');		KeyCheck('R');
	KeyCheck('A');		KeyCheck('S');		KeyCheck('D');		KeyCheck('F');
	KeyCheck('Z');		KeyCheck('X');		KeyCheck('C');		KeyCheck('V');
	KeyCheck('`');

	return true;
}

bool Input::Render() noexcept
{
	return true;
}

bool  Input::Release() noexcept
{
	return true;
}

POINT Input::GetCursor()
{
	return m_Cursor;
}

EKeyState Input::GetMouseState(const EMouseButton& mouseButton)
{
	return m_MouseState[mouseButton];
}

D3DXVECTOR2 Input::GetMouseMovePos()
{
	return { float(m_Cursor.x - m_prevCursor.x), float(m_Cursor.y - m_prevCursor.y) };
}

short Input::GetWheelScroll()
{
	return m_WheelScroll;
}

EKeyState Input::GetKeyState(const WORD& keyValue)
{
	//if (isChatting)
	//return EKeyState::FREE;
	return m_KeyState[keyValue];
}

EKeyState Input::KeyCheck(const WORD& keyValue)
{
	// GetKeyState()		// �����
	// GetAsyncKeyState()	// �񵿱��
	short sKey = GetAsyncKeyState(keyValue);
	// Ŭ�� �����Ͻ� �ֻ��� ��Ʈ�� 1�� �ٲ���
	if (sKey & 0x8000)		// ����			
	{
		if (m_KeyState[keyValue] == EKeyState::FREE)
			return m_KeyState[keyValue] = EKeyState::DOWN;
		else
			return m_KeyState[keyValue] = EKeyState::HOLD;
	}
	else                    // �ȴ���
	{
		if (m_KeyState[keyValue] == EKeyState::DOWN ||
			m_KeyState[keyValue] == EKeyState::HOLD)
			return m_KeyState[keyValue] = EKeyState::UP;
	}
	return m_KeyState[keyValue] = EKeyState::FREE;
}

// �̺�Ʈ �ڵ鷯, �����쿡�� ���ڸ� �޾� ��� ó���� ����
void Input::MsgEvent(const MSG& message)
{
	//_stprintf_s(m_Buffer, L"x : %d,  y : %d", m_Cursor.x, m_Cursor.y);

	switch (message.message)
	{
	case WM_LBUTTONDOWN:
	{
		m_MousePrevState[0] = EKeyState::FREE;
		m_MouseState[0] = EKeyState::DOWN;
	} break;
	case WM_LBUTTONUP:
	{
		m_MousePrevState[0] = EKeyState::HOLD;
		m_MouseState[0] = EKeyState::UP;
	} break;
	case WM_RBUTTONDOWN:
	{
		m_MousePrevState[1] = EKeyState::FREE;
		m_MouseState[1] = EKeyState::DOWN;
	} break;
	case WM_RBUTTONUP:
	{
		m_MousePrevState[1] = EKeyState::HOLD;
		m_MouseState[1] = EKeyState::UP;
	} break;
	case WM_MBUTTONDOWN:
	{
		m_MousePrevState[2] = EKeyState::FREE;
		m_MouseState[2] = EKeyState::DOWN;
	} break;
	case WM_MBUTTONUP:
	{
		m_MousePrevState[2] = EKeyState::HOLD;
		m_MouseState[2] = EKeyState::UP;
	} break;
	case WM_MOUSEWHEEL: 
	{
		m_tempWheelScroll = (short)HIWORD(message.wParam);
	}
	}
}

void Input::MouseUpdate()
{
	// ���콺 ���� ����
	for (int i = 0; i < 3; i++)
	{
		if (m_MousePrevState[i] == EKeyState::FREE)
		{
			if (m_MouseState[i] == EKeyState::DOWN)
			{
				m_MousePrevState[i] = EKeyState::DOWN;
				m_MouseState[i] = EKeyState::HOLD;
			}
		}
		else if (m_MousePrevState[i] == EKeyState::HOLD)
		{
			if (m_MouseState[i] == EKeyState::UP)
			{
				m_MousePrevState[i] = EKeyState::FREE;
				m_MouseState[i] = EKeyState::FREE;
			}
		}
	}
}