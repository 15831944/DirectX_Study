#include "stdafx.h"
#include "UserInterface.h"
bool UserInterface::DeleteTexture(const TCHAR* szTexName)
{
	int iDel = I_TexMgr.Add(g_pd3dDevice, szTexName);

	return true;
}
bool UserInterface::SetLoop()
{
	m_bLoop = !m_bLoop;
	return true;
}
bool UserInterface::SetPlay()
{
	m_bPlay = !m_bPlay;
	return true;
}
bool UserInterface::SetUp(float fSec)
{
	int iSize = m_pTextureList.size();
	if (iSize == 0) return false;
	m_fFrameUpdateSec = fSec / iSize;
	return true;
}
bool UserInterface::Update()
{
	if (!m_bPlay) return false;
	int iSize = m_pTextureList.size();
	m_fFrameElapseSec += g_fSecPerFrame;
	if (m_fFrameElapseSec >= m_fFrameUpdateSec)
	{
		
	
		if (m_iStart++ >= iSize - 1)
		{
			m_iStart = 0;
			m_bPlay = false;
		}
		m_fFrameElapseSec = 0.0f;
	}
	return true;
}
bool UserInterface::Set(RECT rt)
{
	InitMatrixView();
	InitMatrixProj(rt.right, rt.bottom);
	return true;
}
bool UserInterface::UpdateRect()
{
	m_rtPos.left	= m_matWorld._41 - m_matWorld._11;
	m_rtPos.right	= m_matWorld._41 + m_matWorld._11;
	m_rtPos.top		= m_matWorld._42 + m_matWorld._22;
	m_rtPos.bottom	= m_matWorld._42 - m_matWorld._22;

	/* Rect가 LR로 뒤집어졌을 경우 */
	if (m_rtPos.right < m_rtPos.left)
	{
		float Temp		= m_rtPos.right;
		m_rtPos.right	= m_rtPos.left;
		m_rtPos.left	= Temp;
	}
	/* Rect가 LR로 뒤집어졌을 경우 */
	if (m_rtPos.top < m_rtPos.bottom)
	{
		float Temp		= m_rtPos.top;
		m_rtPos.top		= m_rtPos.bottom;
		m_rtPos.bottom	= Temp;
	}
	return true;
}
bool UserInterface::ChangedColor(ID3D11DeviceContext* pContext, D3DXVECTOR4 vColor)
{ 
	if (m_dxObj.m_pVertexBuffer == NULL) return false;
	for (int iVer = 0; iVer < m_pVertices.size(); iVer++)
	{
		m_pVertices[iVer].c = vColor;
	}
	pContext->UpdateSubresource(m_dxObj.m_pVertexBuffer, 0, NULL, &m_pVertices.at(0), 0, 0);
	return true;
}
bool UserInterface::Add(UserInterface* pUI)
{
	m_pChildList.push_back(pUI);
	return true;
}
bool UserInterface::SetParent(UserInterface* pUI)
{
	m_pParent = pUI;
	return true;
}
UserInterface* UserInterface::GetParent()
{
	return m_pParent;
}
bool UserInterface::InitWorldMatrix()
{
	/*  초기Scale값 100,100 */
	D3DXMatrixScaling(&m_matWorld, 100.0f, 100.0f, 1.0f);
	m_matWorld._41 = 0; // x
	m_matWorld._42 = 0; // y
	m_matWorld._43 = 0; // z

	return true;
}
bool UserInterface::InitMatrixView()
{
	D3DXVECTOR3 vPos = { 0, 0, -1 };
	D3DXVECTOR3 vTarget = { 0, 0, 0 };
	D3DXVECTOR3 vUp = { 0, 1, 0 };

	D3DXMatrixLookAtLH(&m_matView, &vPos, &vTarget, &vUp);

	m_vLook.x = m_matView._13;
	m_vLook.y = m_matView._23;
	m_vLook.z = m_matView._33;
	m_vRight.x = m_matView._11;
	m_vRight.y = m_matView._21;
	m_vRight.z = m_matView._31;
	m_vUp.x = m_matView._12;
	m_vUp.y = m_matView._22;
	m_vUp.z = m_matView._32;
	return true;
}
bool UserInterface::InitMatrixProj(float Width, float Height, float Near, float Far)
{
	if (Width == 0 && Height == 0)
	{

	}
	//D3DXMatrixOrthoLH(&m_matProj, Width, Height, Near, Far);
	D3DXMatrixOrthoOffCenterLH(&m_matProj, -(Width / 2), Width / 2, -(Height / 2), Height / 2, Near, Far);
	return true;
}
bool UserInterface::Create()
{
	return true;
}
bool UserInterface::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	if (pWorld != NULL)
	{
		m_matWorld = *pWorld;
	}
	if (pView != NULL)
	{
		m_matView = *pView;
	}
	if (pProj != NULL)
	{
		m_matProj = *pProj;
	}

	/* 전치 후 cbData 넘김 */

	return true;
}
bool UserInterface::Init()
{
	Create();
	//InitWorldMatrix();
	D3DXVECTOR3 vTrans, vScale;
	D3DXQUATERNION qRotate;
	D3DXMatrixDecompose(&vScale, &qRotate, &vTrans, &m_matWorld);
	D3DXMatrixScaling(&m_matScale, vScale.x, vScale.y, vScale.z);
	D3DXMatrixTranslation(&m_matTrans, vTrans.x, vTrans.y, vTrans.z);
	D3DXMatrixRotationQuaternion(&m_matRotate, &qRotate);
	return true;
}
bool UserInterface::Frame()
{
	D3DXMATRIX matParent;

	UpdateRect();

	D3DXMatrixIdentity(&matParent);
	if (m_pParent)
	{
		matParent = m_pParent->m_matWorld;
	}
	m_matWorld = m_matScale * m_matRotate;
	m_matWorld._41 = m_matTrans._41;
	m_matWorld._42 = m_matTrans._42;
	m_matWorld._43 = m_matTrans._43;
	m_matWorld = matParent * m_matWorld;
	for (int iChild = 0; iChild < m_pChildList.size(); iChild++)
	{
		m_pChildList[iChild]->Frame();
	}
	return true;
}
bool UserInterface::PreRender(ID3D11DeviceContext* context, UINT iVertexSize)
{
	m_dxObj.PreRender(context, iVertexSize);
	return true;
}
bool UserInterface::Render(ID3D11DeviceContext* context, UINT iVertexSize, UINT iCount)
{
	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);

	context->UpdateSubresource(m_dxObj.m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
	m_dxObj.Render(context);

	for (int iChild = 0; iChild < m_pChildList.size(); iChild++)
	{
		m_pChildList[iChild]->Render(context);
	}
	return true;
}
bool UserInterface::PostRender(ID3D11DeviceContext* context, UINT iCount)
{
	m_dxObj.PostRender(context, iCount);
	return true;
}
bool UserInterface::Release()
{
	return true;
}

UserInterface::UserInterface()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	D3DXMatrixIdentity(&m_matTrans);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matRotate);
	m_iIndex = 0;
	m_fAngle = 0;
	m_vLook = { 0.0f, 0.0f, 0.0f };
	m_vUp = { 0.0f, 0.0f, 0.0f };
	m_vRight = { 0.0f, 0.0f, 0.0f };
	m_vPos = { 0.0f, 0.0f, 0.0f };
	m_rtPos = { 0.0f, 0.0f, 0.0f, 0.0f };
	Init();
}

UserInterface::~UserInterface()
{
}
