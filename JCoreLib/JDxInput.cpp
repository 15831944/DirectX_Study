#include "JDxInput.h"

#define KEYDOWN(key)	(((m_KeyState[key]) & 0x80) ? true : false)
#define KEYUP(key)		(((m_KeyState[key]) & 0x80) ? false : true)

bool	JDxInput::ResetDevice()
{
	Release();
	Init();
	return true;
}
bool JDxInput::Render()
{
	return true;
}

bool JDxInput::Init()
{
	memset(&m_KeyBeforeState, 0, sizeof(BYTE) * KEYSTATECOUNT);
	memset(&m_MouseBeforeState, 0, sizeof(DIMOUSESTATE));
	m_dwElements = 0;
	return true;
}
bool JDxInput::Frame()
{
	if (!KeyProcess() || !MouseProcess())
	{
		return false;
	}
	return true;
}

bool JDxInput::IsKeyDown(DWORD dwKey)
{
	if (m_dwImmediate)
	{
		if (KEYDOWN(dwKey)) 		return true;
	}
	else
	{
		for (DWORD i = 0; i < m_dwElements; i++)
		{
			if (m_didod[i].dwOfs == dwKey && (m_didod[i].dwData & 0x80))
			{
				return true;
			}
		}
	}
	return false;
}
bool JDxInput::IsKeyUP(DWORD dwKey)
{
	if (m_dwImmediate)
	{
		if (m_KeyBeforeState[dwKey] & 0x80)
		{
			if (KEYUP(dwKey))
				return true;
		}
	}
	else
	{
		for (DWORD i = 0; i < m_dwElements; i++)
		{	
			if (m_didod[i].dwOfs == dwKey && !(m_didod[i].dwData & 0x80))
			{
				return true;
			}
		}
	}


	return false;
}
void JDxInput::PostProcess()
{
	memcpy(&m_KeyBeforeState, &m_KeyState, sizeof(BYTE) * KEYSTATECOUNT);
	memcpy(&m_MouseBeforeState, &m_MouseState, sizeof(DIMOUSESTATE));
}
JDxInput::JDxInput()
{
	m_pDi = NULL;
	m_pDidevKey = NULL;
	m_pDidevMouse = NULL;
	m_hWnd = NULL;
	m_dwElements = 0;
	m_dwImmediate = TRUE;
}

JDxInput::~JDxInput()
{

}

bool JDxInput::InitDirectInput(HINSTANCE hInst, HWND hWnd, bool keyboard, bool mouse)
{
	HRESULT hr;//GetModuleHandle(NULL)
	m_hWnd = hWnd;
	if (m_pDidevKey || m_pDidevMouse) return true;
	if (FAILED(hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDi, NULL)))
	{

		return false;
	}

	if (keyboard)
	{
		if (FAILED(m_pDi->CreateDevice(GUID_SysKeyboard, &m_pDidevKey, NULL)))
			return false;
		if (FAILED(m_pDidevKey->SetDataFormat(&c_dfDIKeyboard)))
			return false;
		if (FAILED(hr = m_pDidevKey->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY)))
		{
			while (m_pDidevKey->Acquire() == DIERR_INPUTLOST);
			if (FAILED(hr = m_pDidevKey->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_BACKGROUND | DISCL_NOWINKEY))) {}
				//return false;
		}
		if (!m_dwImmediate)
		{
			DIPROPDWORD dipdw;

			dipdw.diph.dwSize = sizeof(DIPROPDWORD);
			dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
			dipdw.diph.dwObj = 0;
			dipdw.diph.dwHow = DIPH_DEVICE;
			dipdw.dwData = SAMPLE_BUFFER_SIZE; // Arbitary buffer size

			if (FAILED(hr = m_pDidevKey->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph)))
				return false;
		}

		while (m_pDidevKey->Acquire() == DIERR_INPUTLOST);
	}
	if (mouse)
	{
		if (FAILED(m_pDi->CreateDevice(GUID_SysMouse, &m_pDidevMouse, NULL)))
			return false;
		if (FAILED(m_pDidevMouse->SetDataFormat(&c_dfDIMouse)))
			return false;
		if (FAILED(m_pDidevMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE )))//| DISCL_BACKGROUND)))
		{
			while (m_pDidevMouse->Acquire() == DIERR_INPUTLOST);
			{
				if (FAILED(m_pDidevMouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND )))//| DISCL_BACKGROUND)))
					return false;
			}

		}
		while (m_pDidevMouse->Acquire() == DIERR_INPUTLOST);
	}

	return true;
}

bool JDxInput::Release()
{
	if (m_pDi)
	{
		if (m_pDidevKey)
		{
			m_pDidevKey->Unacquire();
			SAFE_RELEASE(m_pDidevKey);// ->Release();
		}
		if (m_pDidevMouse)
		{
			m_pDidevMouse->Unacquire();
			SAFE_RELEASE(m_pDidevMouse);// ->Release();
		}

		SAFE_RELEASE(m_pDi);
	}
	return true;
}

bool JDxInput::KeyProcess()
{
	HRESULT            hr;
	if (m_dwImmediate)
	{
		ZeroMemory(m_KeyState, sizeof(BYTE) * KEYSTATECOUNT);
		if (m_pDidevKey == nullptr) return false;
		if (FAILED(hr = m_pDidevKey->GetDeviceState(KEYSTATECOUNT, m_KeyState)))
		{
			while (m_pDidevKey->Acquire() == DIERR_INPUTLOST)
				m_pDidevKey->Acquire();
			return true;
		}
	}
	else
	{
		if (NULL == m_pDidevKey)     return false;
		memset(&m_didod, 0, sizeof(DIDEVICEOBJECTDATA)* SAMPLE_BUFFER_SIZE);
		m_dwElements = SAMPLE_BUFFER_SIZE;
		hr = m_pDidevKey->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_didod, &m_dwElements, 0);

		if (hr != DI_OK)
		{
			m_dwElements = 0;
			hr = m_pDidevKey->Acquire();
			while (hr == DIERR_INPUTLOST)
				hr = m_pDidevKey->Acquire();
			return true;
		}
	}
	return true;
}

bool JDxInput::MouseProcess()
{
	ZeroMemory(&m_MouseState, sizeof(DIMOUSESTATE));
	if (!m_pDidevMouse) return false;

	if (FAILED(m_pDidevMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseState)))
	{
		while (m_pDidevMouse->Acquire() == DIERR_INPUTLOST)
			m_pDidevMouse->Acquire();

		return true;
	}

	return true;
}
void JDxInput::SetAcquire(bool bActive)
{
	if (bActive) DeviceAcquire();
	else		  DeviceUnacquire();
}
void JDxInput::DeviceAcquire()
{
	if (m_pDidevKey)
		m_pDidevKey->Acquire();
	if (m_pDidevMouse)
		m_pDidevMouse->Acquire();
}

void JDxInput::DeviceUnacquire()
{
	if (m_pDidevKey)
		m_pDidevKey->Unacquire();
	if (m_pDidevMouse)
		m_pDidevMouse->Unacquire();
}

