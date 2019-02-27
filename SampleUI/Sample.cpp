#include "stdafx.h"
#include "Sample.h"
UserInterface* Sample::FindParent(const TCHAR* szString)
{
	UserInterface* pParent = NULL;
	for (int iUI = 0; iUI < m_pPlaneList.size(); iUI++)
	{
		pParent = m_pPlaneList[iUI];
		if (pParent->m_szNodeName == szString)
		{
			return pParent;
		}
	}
	return NULL;
}
bool Sample::SetWindows(LONG Width, LONG Height)
{
	m_rtClientSize.left = 0;
	m_rtClientSize.top = 0;
	m_rtClientSize.right = Width;
	m_rtClientSize.bottom = Height;
	return true;
}
bool Sample::ChangeCurrentPlane(UserInterface* pPlane)
{
	if (pPlane == NULL)
	{
		AfxMessageBox(L"ChangeCurrentPlane Error!");
		return false;
	}
	/* 이전 CurrentPlane Color 원래대로 돌려놓기 */
	if (m_pCurrentPlane != NULL)
		m_pCurrentPlane->ChangedColor(GetContext(), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	/* 현재 CurrentPlane Color = Red */
	m_pCurrentPlane = pPlane;
	m_pCurrentPlane->ChangedColor(GetContext(), D3DXVECTOR4(1.0f, 0.8f, 0.8f, 1.0f));
	return true;
}
bool Sample::CreatePlane(D3DXMATRIX Scl, D3DXMATRIX Rot, D3DXMATRIX Trans, const TCHAR* szNodeName, const TCHAR* szParentName)
{
	ImageCtrl* pPlane = new ImageCtrl();
	/* Pos Z 값 조정을 위한 값 */
	int iIndex = m_pPlaneList.size();
	pPlane->Set(m_rtClientSize);
	pPlane->m_matScale = Scl;
	pPlane->m_matRotate = Rot;
	pPlane->m_matTrans = Trans;
	pPlane->m_szNodeName = szNodeName;
	pPlane->m_pParent = FindParent(szParentName);
	if (pPlane->m_pParent) pPlane->m_szParentName = pPlane->m_pParent->m_szNodeName;
	pPlane->m_iIndex = iIndex;
	/* ======================= */
	m_pPlaneList.push_back(pPlane);
	if (!ChangeCurrentPlane(m_pPlaneList[iIndex])) return false;
	return true;
}
bool Sample::CreateSprite(D3DXMATRIX Scl, D3DXMATRIX Rot, D3DXMATRIX Trans, const TCHAR* szNodeName, const TCHAR* szParentName)
{
	SpriteCtrl* pSprite = new SpriteCtrl();
	/* Pos Z 값 조정을 위한 값 */
	int iIndex = m_pPlaneList.size();
	pSprite->Set(m_rtClientSize);
	pSprite->m_matScale = Scl;
	pSprite->m_matRotate = Rot;
	pSprite->m_matTrans = Trans;
	pSprite->m_szNodeName = szNodeName;
	pSprite->m_pParent = FindParent(szParentName);
	if (pSprite->m_pParent) pSprite->m_szParentName = pSprite->m_pParent->m_szNodeName;
	pSprite->m_iIndex = iIndex;
	/* ======================= */
	m_pPlaneList.push_back(pSprite);
	if (!ChangeCurrentPlane(m_pPlaneList[iIndex])) return false;
	return true;
}
bool Sample::UpdateMouse()
{
	if (m_pCurrentPlane == NULL) return false;
	POINT mouse;
	mouse.x = I_Input.m_MousePos.x * ((float)m_rtClientSize.right / (float)g_rtClient.right);
	mouse.y = I_Input.m_MousePos.y * ((float)m_rtClientSize.bottom / (float)g_rtClient.bottom);
	m_ptMouse.x = (mouse.x - (m_rtClientSize.right / 2.0f));
	m_ptMouse.y = (mouse.y - (m_rtClientSize.bottom / 2.0f)) * -1.0f;
	_stprintf_s(m_szMouse, L"MFC MousePos( %ld , %ld )", m_ptMouse.x, m_ptMouse.y);
	return true;
}
bool Sample::ClickedFindCurrentPlane()
{
	if (I_Input.m_dwMouseState[0] == KEY_PUSH)
	{
		/* 클릭한 곳의 겹쳐져있는 Plane을 모두 List에 집어넣는다 */
		for (int iUI = 0; iUI < m_pPlaneList.size(); iUI++)
		{
			for (int iPlane = 0; iPlane < m_pPlaneList.size(); iPlane++)
			{
				UserInterface* Plane = m_pPlaneList[iUI];
				if (fRectInPt(Plane->m_rtPos, m_ptMouse))
				{
					m_pSelectList.push_back(Plane);
				}
			}
		}
		/* List의 z값 비교를 하고 제일 위의 Plane을 CurrentPlane으로 한다. */
		int iListCnt = m_pSelectList.size();
		/* 클릭된 곳에 Plane이 없을 경우 */
		if (iListCnt == 0)
		{
			return false;
		}
		/* 겹친 Plane이 없을 경우 */
		if (iListCnt == 1)
		{
			ChangeCurrentPlane(m_pSelectList[0]);
			m_pSelectList.clear();
			return true;
		}
		/* 겹친 Plane이 있을경우 */
		UserInterface* BigZValuePlane = m_pSelectList[0];
		for (int iSelect = 1; iSelect < m_pSelectList.size(); iSelect++)
		{
			UserInterface* Plane = m_pSelectList[iSelect];
			BigZValuePlane = FindBigZValuePlane(BigZValuePlane, Plane);
		}
		ChangeCurrentPlane(BigZValuePlane);
		m_pSelectList.clear();
	}
	return true;
}
UserInterface* Sample::FindBigZValuePlane(UserInterface* pSrc, UserInterface* pDesk)
{
	UserInterface* Src = pSrc;
	UserInterface* Desk = pDesk;
	/* z값 작은 Plane 리턴 */
	if(Src->m_matWorld._43 < Desk->m_matWorld._43)
	{
		return Src;
	} 
	else
	{
		return Desk;
	}
	return NULL;
}
bool Sample::Transition()
{
	if (I_Input.m_dwMouseState[0] == KEY_PUSH || I_Input.m_dwMouseState[0] == KEY_HOLD)
	{
		if (fRectInPt(m_pCurrentPlane->m_rtPos, m_ptMouse))
		{
			static float fDX = 0.0f;
			static float fDY = 0.0f;
			D3DXMATRIX m_matWorld;
			/* 처음 MOUSE PUSH를 하게되면 아래의 PUSH 조건이 걸릴것이다 */
			/* 그 이후의 MouseState는 HOLD가 되기때문에 아래의 PUSH 조건은 안걸릴것이고 */
			/* HOLD조건에 걸리기때문에 Mouse UP이 되기전까진 Rect와 Mouse의 Distance만큼 떨어지게 된다 */
			if (I_Input.m_dwMouseState[0] == KEY_PUSH)
			{
				m_matWorld = m_pCurrentPlane->m_matWorld;
				D3DXVECTOR3 v0 = D3DXVECTOR3(m_matWorld._41, m_matWorld._42, m_matWorld._43);
				D3DXVECTOR3 v1 = D3DXVECTOR3(m_ptMouse.x, m_ptMouse.y, 0.0f);
				fDX = v0.x - v1.x;
				fDY = v0.y - v1.y;
			}
			if (I_Input.m_dwMouseState[0] == KEY_HOLD)
			{
				if (m_pCurrentPlane->m_pParent)
				{
					m_pCurrentPlane->m_matTrans._41 = m_ptMouse.x + fDX - m_pCurrentPlane->m_pParent->m_matWorld._41 ;
					m_pCurrentPlane->m_matTrans._42 = m_ptMouse.y + fDY - m_pCurrentPlane->m_pParent->m_matWorld._42 ;
				}
				else
				{
					m_pCurrentPlane->m_matTrans._41 = m_ptMouse.x + fDX;
					m_pCurrentPlane->m_matTrans._42 = m_ptMouse.y + fDY;
				}
			}
			if (I_Input.m_dwMouseState[0] == KEY_UP)
			{
				fDX = 0.0f;
				fDY = 0.0f;
			}
		}
	}
	return true;
}
bool Sample::Rotation()
{
	static float fTime = 0.0f;
	if (I_Input.KeyCheck('Q') == KEY_PUSH || I_Input.KeyCheck('Q') == KEY_HOLD)
	{
		m_pCurrentPlane->m_fAngle += g_fSecPerFrame;
		D3DXMatrixRotationZ(&m_pCurrentPlane->m_matRotate, m_pCurrentPlane->m_fAngle);
	}
	if (I_Input.KeyCheck('E') == KEY_PUSH || I_Input.KeyCheck('E') == KEY_HOLD)
	{
		m_pCurrentPlane->m_fAngle -= g_fSecPerFrame;
		D3DXMatrixRotationZ(&m_pCurrentPlane->m_matRotate, m_pCurrentPlane->m_fAngle);
	}
	if (I_Input.KeyCheck(VK_SPACE) == KEY_PUSH || I_Input.KeyCheck(VK_SPACE) == KEY_HOLD)
	{
		m_pCurrentPlane->m_fAngle = 0.0f;
		D3DXMatrixRotationZ(&m_pCurrentPlane->m_matRotate, m_pCurrentPlane->m_fAngle);
	}
	return true;
}
bool Sample::Scaling()
{
	if (I_Input.KeyCheck('A') == KEY_PUSH || I_Input.KeyCheck('A') == KEY_HOLD)
	{
		m_pCurrentPlane->m_matScale._11 -= g_fSecPerFrame * 3.141592f * 10.0f;
	}
	if (I_Input.KeyCheck('D') == KEY_PUSH || I_Input.KeyCheck('D') == KEY_HOLD)
	{
		m_pCurrentPlane->m_matScale._11 += g_fSecPerFrame * 3.141592f* 10.0f;
	}
	if (I_Input.KeyCheck('W') == KEY_PUSH || I_Input.KeyCheck('W') == KEY_HOLD)
	{
		m_pCurrentPlane->m_matScale._22 += g_fSecPerFrame * 3.141592f* 10.0f;
	}
	if (I_Input.KeyCheck('S') == KEY_PUSH || I_Input.KeyCheck('S') == KEY_HOLD)
	{
		m_pCurrentPlane->m_matScale._22 -= g_fSecPerFrame * 3.141592f* 10.0f;
	}
	return true;
}
bool Sample::LoadSingleTexture(CString szTexName)
{
	int iTex = I_TexMgr.Add(g_pd3dDevice, szTexName);
	if (iTex < 0 || m_pCurrentPlane == NULL) return false;
	m_pCurrentPlane->m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTex);
	return true;
}
bool Sample::LoadMultyTexture(CString szTexName)
{
	int iTex = I_TexMgr.Add(g_pd3dDevice, szTexName);
	if (iTex < 0 || m_pCurrentPlane == NULL) return false;
	JTexture* tex = new JTexture();
	tex = I_TexMgr.GetPtr(iTex);
	m_pCurrentPlane->m_pTextureList.push_back(I_TexMgr.GetPtr(iTex));
	m_pCurrentPlane->m_dxObj.m_pPS = DX::LoadPixelShader(g_pd3dDevice, L"../../data/shader/shape.psh", &m_pCurrentPlane->m_dxObj.m_BlobPS);
	return true;
}
bool Sample::DeleteTexture(CString szTexName)
{
	vector<JTexture*>::iterator ITOR;
	for (ITOR = m_pCurrentPlane->m_pTextureList.begin();
		ITOR != m_pCurrentPlane->m_pTextureList.end();
		ITOR++)
	{
		JTexture* DelData = (*ITOR);
		wstring DelTexName = szTexName;
		if (DelData->m_szName == DelTexName)
		{
			m_pCurrentPlane->m_pTextureList.erase(ITOR);
			if (m_pCurrentPlane->m_pTextureList.size() <= 0)
			{
				m_pCurrentPlane->m_dxObj.m_pPS = DX::LoadPixelShader(g_pd3dDevice, L"../../data/shader/shape.psh", &m_pCurrentPlane->m_dxObj.m_BlobPS, "PSColor");
			}
			return true;
		}
	}	
	return false;
}
bool Sample::Init()
{
	SetWindows(1024, 768);
	return true;
}
bool Sample::Frame() 
{
	UpdateMouse();
	if (!m_pCurrentPlane) return false;
	ClickedFindCurrentPlane();
	Transition();
	Rotation();
	Scaling();
	for (int iPlane = 0; iPlane < m_pPlaneList.size(); iPlane++)
	{
		m_pPlaneList[iPlane]->Frame();
	}
	_stprintf_s(m_szRect, L"Rect ( %f , %f , %f , %f )", m_pCurrentPlane->m_rtPos.left, m_pCurrentPlane->m_rtPos.right, 
														 m_pCurrentPlane->m_rtPos.top, m_pCurrentPlane->m_rtPos.bottom);

	_stprintf_s(m_Client, L"g_rtClient ( %ld , %ld , %ld , %ld )", g_rtClient.left, g_rtClient.right, g_rtClient.top, g_rtClient.bottom);
	return true;
}
bool Sample::Render() 
{
	for (int iPlane = 0; iPlane < m_pPlaneList.size(); iPlane++)
	{
		m_pPlaneList[iPlane]->Render(GetContext());
	}
	if (m_bShowDebug)
	{
		I_Write.Draw(m_szMouse, 15, { 0,150,800,600 });
		I_Write.Draw(m_szRect, 15, { 0,200,800,600 });
		I_Write.Draw(m_Client, 15, { 0,250,800,600 }); 
	}
	return true;
}
bool Sample::Release()
{
	return true;
}
bool Sample::fRectInPt(fRECT rt, POINT pt)
{
	if (rt.left <= pt.x && rt.right >= pt.x)
	{
		if (rt.top >= pt.y && rt.bottom <= pt.y)
		{
			return true;
		}
	}
	return false;
}
CString Sample::PathDivide(CString strName)
{
	CString retStr;
	TCHAR RetData[MAX_PATH] = { 0, };
	TCHAR Drive[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR FileName[MAX_PATH] = { 0, };
	TCHAR Ext[MAX_PATH] = { 0, };
	_tsplitpath_s(strName, Drive, Dir, FileName, Ext);
	retStr = FileName;
	retStr += Ext;
	return retStr;
}
Sample::Sample()
{
	m_ptMouse = { 0,0 };
}
Sample::~Sample()
{

}