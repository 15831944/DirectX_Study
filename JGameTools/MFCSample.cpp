#include "stdafx.h"
#include "MFCSample.h"
//	(w)ifstreamtt
//	(w)ofstream
bool MFCSample::SelectPlane()
{
	m_MFCMouse = UpdatePt();
	_stprintf_s(MousePos, L"MFC MousePos( %d , %d )", m_MFCMouse.x, m_MFCMouse.y);
	for (int iRect = 0; iRect < m_PlaneList.size(); iRect++)
	{
		PlaneUI* pRect = m_PlaneList[iRect];
		if (I_Input.m_dwMouseState[0] == KEY_PUSH)
		{
			fRECT rt = pRect->m_Plane->m_rt;
			/* RECT LR,TB ¹Ù²î¾úÀ»¶§ */
			if (rt.left > rt.right)
			{
				SwapLR(m_PlaneList[iRect]->m_Plane->m_rt);
			}
			if (rt.top < rt.bottom)
			{
				SwapTB(m_PlaneList[iRect]->m_Plane->m_rt);
			}
			/* RECT IN PT CHECK */
			if (TRUE == FindBiggerZ(m_PlaneList[iRect]->m_Plane->m_matWorld) &&
				rt.left <= m_MFCMouse.x && rt.right >= m_MFCMouse.x)
			{
				if (rt.top >= m_MFCMouse.y && rt.bottom <= m_MFCMouse.y)
				{
					SwapZ(m_PlaneList[iRect]->m_Plane->m_matWorld);
					m_CurrentPlane = pRect;
				}
			}
		}
	}
	return true;
}
BOOL MFCSample::FindBiggerZ(D3DXMATRIX mat)
{
	for (int iRect = 0; iRect < m_PlaneList.size(); iRect++)
	{
		if (mat._43 > m_PlaneList[iRect]->m_Plane->m_matWorld._43)
			return TRUE;
	}
	return FALSE;
}
POINT MFCSample::UpdatePt()
{
	/* MOUSE ÁÂÇ¥º¯È¯ */
	POINT retPt;
	retPt.x = (I_Input.m_MousePos.x - (g_rtClient.right / 2.0f));
	retPt.y = (I_Input.m_MousePos.y - (g_rtClient.bottom / 2.0f)) * -1.0f;
	return retPt;
}
bool MFCSample::UpdateRect(PlaneUI* Plane)
{
	/* Plane */
	Plane->m_Plane->m_rt.left = Plane->m_Plane->m_matWorld._41 - Plane->m_Plane->m_matWorld._11;
	Plane->m_Plane->m_rt.right = Plane->m_Plane->m_matWorld._41 + Plane->m_Plane->m_matWorld._11;
	Plane->m_Plane->m_rt.top = (Plane->m_Plane->m_matWorld._42 + Plane->m_Plane->m_matWorld._22);
	Plane->m_Plane->m_rt.bottom = (Plane->m_Plane->m_matWorld._42 - Plane->m_Plane->m_matWorld._22);
	/* Collision Plane */
	Plane->m_ColLeft->m_matWorld._41 = Plane->m_Plane->m_matWorld._41 - Plane->m_Plane->m_matWorld._11;
	Plane->m_ColLeft->m_matWorld._42 = Plane->m_Plane->m_matWorld._42;
	Plane->m_ColRight->m_matWorld._41 = Plane->m_Plane->m_matWorld._41 + Plane->m_Plane->m_matWorld._11;
	Plane->m_ColRight->m_matWorld._42 = Plane->m_Plane->m_matWorld._42;
	Plane->m_ColTop->m_matWorld._42 = Plane->m_Plane->m_matWorld._42 + Plane->m_Plane->m_matWorld._22;
	Plane->m_ColTop->m_matWorld._41 = Plane->m_Plane->m_matWorld._41;
	Plane->m_ColBottom->m_matWorld._42 = Plane->m_Plane->m_matWorld._42 - Plane->m_Plane->m_matWorld._22;
	Plane->m_ColBottom->m_matWorld._41 = Plane->m_Plane->m_matWorld._41;

	Plane->m_ColLeft->m_rt.left = Plane->m_ColLeft->m_matWorld._41 - Plane->m_ColLeft->m_matWorld._11;
	Plane->m_ColLeft->m_rt.right = Plane->m_ColLeft->m_matWorld._41 + Plane->m_ColLeft->m_matWorld._11;
	Plane->m_ColLeft->m_rt.top = (Plane->m_ColLeft->m_matWorld._42 + Plane->m_ColLeft->m_matWorld._22);
	Plane->m_ColLeft->m_rt.bottom = (Plane->m_ColLeft->m_matWorld._42 - Plane->m_ColLeft->m_matWorld._22);

	Plane->m_ColRight->m_rt.left = Plane->m_ColRight->m_matWorld._41 - Plane->m_ColRight->m_matWorld._11;
	Plane->m_ColRight->m_rt.right = Plane->m_ColRight->m_matWorld._41 + Plane->m_ColRight->m_matWorld._11;
	Plane->m_ColRight->m_rt.top = (Plane->m_ColRight->m_matWorld._42 + Plane->m_ColRight->m_matWorld._22);
	Plane->m_ColRight->m_rt.bottom = (Plane->m_ColRight->m_matWorld._42 - Plane->m_ColRight->m_matWorld._22);

	Plane->m_ColTop->m_rt.left = Plane->m_ColTop->m_matWorld._41 - Plane->m_ColTop->m_matWorld._11;
	Plane->m_ColTop->m_rt.right = Plane->m_ColTop->m_matWorld._41 + Plane->m_ColTop->m_matWorld._11;
	Plane->m_ColTop->m_rt.top = (Plane->m_ColTop->m_matWorld._42 + Plane->m_ColTop->m_matWorld._22);
	Plane->m_ColTop->m_rt.bottom = (Plane->m_ColTop->m_matWorld._42 - Plane->m_ColTop->m_matWorld._22);

	Plane->m_ColBottom->m_rt.left = Plane->m_ColBottom->m_matWorld._41 - Plane->m_ColBottom->m_matWorld._11;
	Plane->m_ColBottom->m_rt.right = Plane->m_ColBottom->m_matWorld._41 + Plane->m_ColBottom->m_matWorld._11;
	Plane->m_ColBottom->m_rt.top = (Plane->m_ColBottom->m_matWorld._42 + Plane->m_ColBottom->m_matWorld._22);
	Plane->m_ColBottom->m_rt.bottom = (Plane->m_ColBottom->m_matWorld._42 - Plane->m_ColBottom->m_matWorld._22);
	return true;
}
bool MFCSample::SwapZ(D3DXMATRIX& desk)
{
	for (int iRect = 0; iRect < m_PlaneList.size(); iRect++)
	{
		if (desk._43 > m_PlaneList[iRect]->m_Plane->m_matWorld._43)
		{
			float Temp = m_PlaneList[iRect]->m_Plane->m_matWorld._43;
			m_PlaneList[iRect]->m_Plane->m_matWorld._43 = desk._43;
			desk._43 = Temp;
		}
	}
	return true;
}
bool MFCSample::SwapTB(fRECT& rt)
{
	fRECT temp = rt;
	rt.top = rt.bottom;
	rt.bottom = temp.top;
	return true;
}
bool MFCSample::SwapLR(fRECT& rt)
{
	fRECT temp = rt;
	rt.left = rt.right;
	rt.right = temp.left;
	return true;
}
bool MFCSample::CreatePlane()
{
	m_fZ -= 0.1f;
	PlaneUI* Plane = new PlaneUI();
	Plane->m_Plane->Init();
	D3DXMatrixScaling(&Plane->m_Plane->m_matWorld, 100.0f, 100.0f, 100.0f);
	Plane->m_Plane->m_matWorld._43 += m_fZ;
	Plane->m_Plane->SetMatrix(&Plane->m_Plane->m_matWorld,
										&m_MainCam->m_matView, 
										&m_MainCam->m_matProj);
	UpdateRect(Plane);
	/* ====================================Collision Create============================================== */
	JPlaneShape* left = new JPlaneShape; 	left->Init();
	JPlaneShape* right = new JPlaneShape;	right->Init();
	JPlaneShape* top = new JPlaneShape;		top->Init();
	JPlaneShape* bottom = new JPlaneShape;	bottom->Init();

	D3DXMatrixScaling(&left->m_matWorld, 10.0f, Plane->m_Plane->m_matWorld._22, 1.0f);
	D3DXMatrixScaling(&right->m_matWorld, 10.0f, Plane->m_Plane->m_matWorld._22, 1.0f);
	D3DXMatrixScaling(&top->m_matWorld, Plane->m_Plane->m_matWorld._11, 10.0f, 1.0f);
	D3DXMatrixScaling(&bottom->m_matWorld, Plane->m_Plane->m_matWorld._11, 10.0f, 1.0f);

	left->m_matWorld._41 = Plane->m_Plane->m_matWorld._41 - Plane->m_Plane->m_matWorld._11;
	right->m_matWorld._41 = Plane->m_Plane->m_matWorld._41 + Plane->m_Plane->m_matWorld._11;
	top->m_matWorld._42 = Plane->m_Plane->m_matWorld._42 + Plane->m_Plane->m_matWorld._22;
	bottom->m_matWorld._42 = Plane->m_Plane->m_matWorld._42 - Plane->m_Plane->m_matWorld._22;

	left->SetMatrix(&left->m_matWorld,
		&m_MainCam->m_matView,
		&m_MainCam->m_matProj);
	right->SetMatrix(&right->m_matWorld,
		&m_MainCam->m_matView,
		&m_MainCam->m_matProj);
	top->SetMatrix(&top->m_matWorld,
		&m_MainCam->m_matView,
		&m_MainCam->m_matProj);
	bottom->SetMatrix(&bottom->m_matWorld,
		&m_MainCam->m_matView,
		&m_MainCam->m_matProj);

	Plane->m_ColLeft = left;
	Plane->m_ColRight = right;
	Plane->m_ColTop = top;
	Plane->m_ColBottom = bottom;
	/* ============================================================================================== */
	m_PlaneList.push_back(Plane);
	int iCur = m_PlaneList.size();
	m_CurrentPlane = m_PlaneList[iCur - 1];
	return true;
}
bool MFCSample::LoadTexture(CString szTexName)
{
	int iTex = I_TexMgr.Add(g_pd3dDevice, szTexName);
	if (iTex < 0 || m_CurrentPlane == NULL) return false;
	m_CurrentPlane->m_Plane->m_dxObj.m_pTexture = I_TexMgr.GetPtr(iTex);
	return true;
}
bool MFCSample::Init()
{
	box.Init();
	return true;
}
bool MFCSample::Frame()
{
	//if (I_InputDx.m_MouseState.rgbButtons[0])
	//{
	//	AfxMessageBox(L"sadf");
	//}
	static float fTime = 0;
	fTime += g_fSecPerFrame * 3.141592f;
	if (m_CurrentPlane == NULL) return true;
	//if (I_Input.KeyCheck('I') == KEY_PUSH || I_Input.KeyCheck('I') == KEY_HOLD)
	//{
	//	m_CurrentPlane->m_matWorld._42 += g_fSecPerFrame * 100.0f;
	//}
	//if (I_Input.KeyCheck('K') == KEY_PUSH || I_Input.KeyCheck('K') == KEY_HOLD)
	//{
	//	m_CurrentPlane->m_matWorld._42 -= g_fSecPerFrame * 100.0f;
	//	//m_CurrentPlane->m_vPos -= m_CurrentPlane->m_vUp* g_fSecPerFrame;
	//}
	//if (I_Input.KeyCheck('L') == KEY_PUSH || I_Input.KeyCheck('L') == KEY_HOLD)
	//{
	//	m_CurrentPlane->m_matWorld._41 += g_fSecPerFrame * 100.0f;
	//	//m_CurrentPlane->m_vPos += m_CurrentPlane->m_vRight* g_fSecPerFrame;
	//}
	//if (I_Input.KeyCheck('J') == KEY_PUSH || I_Input.KeyCheck('J') == KEY_HOLD)
	//{
	//	m_CurrentPlane->m_matWorld._41 -= g_fSecPerFrame * 100.0f;
	//	//m_CurrentPlane->m_vPos -= m_CurrentPlane->m_vRight * g_fSecPerFrame;
	//}
	//if (I_Input.KeyCheck(VK_RIGHT) == KEY_PUSH || I_Input.KeyCheck(VK_RIGHT) == KEY_HOLD)
	//{
	//	m_CurrentPlane->m_matWorld._11 += 0.1f;
	//}
	//if (I_Input.KeyCheck(VK_UP) == KEY_PUSH || I_Input.KeyCheck(VK_UP) == KEY_HOLD)
	//{
	//	m_CurrentPlane->m_matWorld._22 += 0.1f;
	//}
	//if (I_Input.KeyCheck(VK_LEFT) == KEY_PUSH || I_Input.KeyCheck(VK_LEFT) == KEY_HOLD)
	//{
	//	m_CurrentPlane->m_matWorld._11 -= 0.1f;
	//}
	//if (I_Input.KeyCheck(VK_DOWN) == KEY_PUSH || I_Input.KeyCheck(VK_DOWN) == KEY_HOLD)
	//{
	//	m_CurrentPlane->m_matWorld._22 -= 0.1f;
	//}

	//m_CurrentPlane->m_matWorld._41 = m_CurrentPlane->m_vPos.x;
	//m_CurrentPlane->m_matWorld._43 = m_CurrentPlane->m_vPos.z;
	//m_CurrentPlane->m_matWorld._42 = m_CurrentPlane->m_vPos.y;
	if(I_Input.m_dwMouseState[0] == KEY_UP)
		CollisionCheck();
	SelectPlane();
	if (I_Input.m_dwMouseState[0] == KEY_PUSH ||
		I_Input.m_dwMouseState[0] == KEY_HOLD)
	{
		if (m_CurrentPlane->m_Plane->m_rt.left <= m_MFCMouse.x &&
			m_CurrentPlane->m_Plane->m_rt.right >= m_MFCMouse.x)
		{
			if (m_CurrentPlane->m_Plane->m_rt.top >= m_MFCMouse.y &&
				m_CurrentPlane->m_Plane->m_rt.bottom <= m_MFCMouse.y)
			{
				m_CurrentPlane->m_Plane->m_matWorld._41 = m_MFCMouse.x;
				m_CurrentPlane->m_Plane->m_matWorld._42 = m_MFCMouse.y;
			}
		}
	}
	UpdateRect(m_CurrentPlane);
	_stprintf_s(temp, L"MFC rect( %.0f, %.0f, %.0f, %.0f )", 
		m_PlaneList[0]->m_Plane->m_rt.left, m_PlaneList[0]->m_Plane->m_rt.right,
		m_PlaneList[0]->m_Plane->m_rt.top, m_PlaneList[0]->m_Plane->m_rt.bottom);
	//if (m_CurrentPlane->m_rt.left > g_rtClient.left)
	//	m_CurrentPlane->m_rt.left = g_rtClient.left;
	//if (m_CurrentPlane->m_rt.right > g_rtClient.right)
	//	m_CurrentPlane->m_rt.right = g_rtClient.right;
	//if (m_CurrentPlane->m_rt.top < g_rtClient.top)
	//	m_CurrentPlane->m_rt.top = g_rtClient.top;
	//if (m_CurrentPlane->m_rt.bottom < g_rtClient.bottom)
	//	m_CurrentPlane->m_rt.bottom = g_rtClient.bottom;

	return true;
}
BOOL MFCSample::CollisionCheck()
{
	for (int iPlane = 0; iPlane < m_PlaneList.size(); iPlane++)
	{
		PlaneUI* plane = m_PlaneList[iPlane];
		if (plane == m_CurrentPlane) 
			continue;
		if (fRectInRect(m_CurrentPlane->m_ColLeft->m_rt, plane->m_ColRight->m_rt))
		{
			m_CurrentPlane->m_Plane->m_matWorld._41 = plane->m_Plane->m_matWorld._41 + (m_CurrentPlane->m_Plane->m_matWorld._11 * 2.0f);
			return TRUE;
		}
		if (fRectInRect(m_CurrentPlane->m_ColRight->m_rt, plane->m_ColLeft->m_rt))
		{
			m_CurrentPlane->m_Plane->m_matWorld._41 = plane->m_Plane->m_matWorld._41 - (m_CurrentPlane->m_Plane->m_matWorld._11 * 2.0f);
			return TRUE;
		}
		if (fRectInRect(m_CurrentPlane->m_ColTop->m_rt, plane->m_ColBottom->m_rt))
		{
			m_CurrentPlane->m_Plane->m_matWorld._42 = plane->m_Plane->m_matWorld._42 - (m_CurrentPlane->m_Plane->m_matWorld._22 * 2.0f);
			return TRUE;
		}
		if (fRectInRect(m_CurrentPlane->m_ColBottom->m_rt, plane->m_ColTop->m_rt))
		{
			m_CurrentPlane->m_Plane->m_matWorld._42 = plane->m_Plane->m_matWorld._42 + (m_CurrentPlane->m_Plane->m_matWorld._22 * 2.0f);
			return TRUE;
		}
	}
	return FALSE;
}
bool MFCSample::Render()
{
	for (int iPlane = 0; iPlane < m_PlaneList.size(); iPlane++)
	{
		if (m_PlaneList[iPlane] == m_CurrentPlane)
		{
			m_CurrentPlane->m_Plane->SetMatrix(&m_CurrentPlane->m_Plane->m_matWorld, &m_Camera[4].m_matView, &m_Camera[4].m_matProj);
			m_CurrentPlane->m_Plane->Render(GetContext());

			//m_CurrentPlane->m_ColLeft->SetMatrix(&m_CurrentPlane->m_ColLeft->m_matWorld, &m_Camera[4].m_matView, &m_Camera[4].m_matProj);
			//m_CurrentPlane->m_ColLeft->Render(GetContext());
			//m_CurrentPlane->m_ColRight->SetMatrix(&m_CurrentPlane->m_ColRight->m_matWorld, &m_Camera[4].m_matView, &m_Camera[4].m_matProj);
			//m_CurrentPlane->m_ColRight->Render(GetContext());
			//m_CurrentPlane->m_ColTop->SetMatrix(&m_CurrentPlane->m_ColTop->m_matWorld, &m_Camera[4].m_matView, &m_Camera[4].m_matProj);
			//m_CurrentPlane->m_ColTop->Render(GetContext());
			//m_CurrentPlane->m_ColBottom->SetMatrix(&m_CurrentPlane->m_ColBottom->m_matWorld, &m_Camera[4].m_matView, &m_Camera[4].m_matProj);
			//m_CurrentPlane->m_ColBottom->Render(GetContext());
			continue;
		}
		m_PlaneList[iPlane]->m_Plane->SetMatrix(NULL, &m_Camera[4].m_matView, &m_Camera[4].m_matProj);
		m_PlaneList[iPlane]->m_Plane->Render(GetContext());

		//m_PlaneList[iPlane]->m_ColLeft->SetMatrix(&m_PlaneList[iPlane]->m_ColLeft->m_matWorld, &m_Camera[4].m_matView, &m_Camera[4].m_matProj);
		//m_PlaneList[iPlane]->m_ColLeft->Render(GetContext());
		//m_PlaneList[iPlane]->m_ColRight->SetMatrix(&m_PlaneList[iPlane]->m_ColRight->m_matWorld, &m_Camera[4].m_matView, &m_Camera[4].m_matProj);
		//m_PlaneList[iPlane]->m_ColRight->Render(GetContext());
		//m_PlaneList[iPlane]->m_ColTop->SetMatrix(&m_PlaneList[iPlane]->m_ColTop->m_matWorld, &m_Camera[4].m_matView, &m_Camera[4].m_matProj);
		//m_PlaneList[iPlane]->m_ColTop->Render(GetContext());
		//m_PlaneList[iPlane]->m_ColBottom->SetMatrix(&m_PlaneList[iPlane]->m_ColBottom->m_matWorld, &m_Camera[4].m_matView, &m_Camera[4].m_matProj);
		//m_PlaneList[iPlane]->m_ColBottom->Render(GetContext());
	}
	I_Write.Draw(MousePos, 15, { 0,150,800,600 });
	I_Write.Draw(temp, 15, { 0,200,800,600 });
	box.SetMatrix(NULL, &m_MainCam->m_matView, &m_MainCam->m_matProj);
	box.Render(GetContext());
	return true;
}
bool MFCSample::Release()
{
	for (int iPlane = 0; iPlane < m_PlaneList.size(); iPlane++)
	{
		SAFE_RELEASE(m_PlaneList[iPlane]->m_Plane);
		SAFE_RELEASE(m_PlaneList[iPlane]->m_ColLeft);
		SAFE_RELEASE(m_PlaneList[iPlane]->m_ColRight);
		SAFE_RELEASE(m_PlaneList[iPlane]->m_ColBottom);
		SAFE_RELEASE(m_PlaneList[iPlane]->m_ColTop);
	}
	if (m_CurrentPlane)
	{
		SAFE_RELEASE(m_CurrentPlane->m_Plane);
		SAFE_RELEASE(m_CurrentPlane->m_ColLeft);
		SAFE_RELEASE(m_CurrentPlane->m_ColRight);
		SAFE_RELEASE(m_CurrentPlane->m_ColBottom);
		SAFE_RELEASE(m_CurrentPlane->m_ColTop);
	}
	box.Release();
	return true;
}
CString MFCSample::NameDivide(CString strName)
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
bool MFCSample::fRectInRect(fRECT rtDesk, fRECT rtSrc)
{
	fRECT desk = rtDesk;
	fRECT src = rtSrc;
	desk.left = rtDesk.left + (g_rtClient.right / 2.0f);
	desk.right = rtDesk.right + (g_rtClient.right / 2.0f);
	desk.bottom = (rtDesk.top + (g_rtClient.bottom / 2.0f));
	desk.top = (rtDesk.bottom + (g_rtClient.bottom / 2.0f)) - 1.0f;

	src.left = rtSrc.left + (g_rtClient.right / 2.0f);
	src.right = rtSrc.right + (g_rtClient.right / 2.0f);
	src.bottom = (rtSrc.top + (g_rtClient.bottom / 2.0f));
	src.top = (rtSrc.bottom + (g_rtClient.bottom / 2.0f)) - 1.0f;

	POINT  cDesk, cSrc, Radius, DeskRadius, SrcRadius;
	cDesk.x = (desk.left + desk.right) / 2;
	cDesk.y = (desk.top + desk.bottom) / 2;
	cSrc.x = (src.left + src.right) / 2;
	cSrc.y = (src.top + src.bottom) / 2;
	Radius.x = abs(cDesk.x - cSrc.x);
	Radius.y = abs(cDesk.y - cSrc.y);
	DeskRadius.x = (desk.right - desk.left) / 2;
	DeskRadius.y = (desk.bottom - desk.top) / 2;
	SrcRadius.x = (src.right - src.left) / 2;
	SrcRadius.y = (src.bottom - src.top) / 2;
	if (Radius.x <= (DeskRadius.x + SrcRadius.x) &&
		Radius.y <= (DeskRadius.y + SrcRadius.y))
	{
		return true;
	}
	return false;
}
MFCSample::MFCSample()
{
	m_fZ = 0.0f;
}


MFCSample::~MFCSample()
{
}
