#include "JDxObject.h"
/* Helper Function */
bool JDxObject::SetTexture(ID3D11Device* device, const TCHAR* szTexName)
{
	m_pTexture = I_Texture.GetPtr(I_Texture.Add(device, szTexName));
	return true;
}
bool JDxObject::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	if (pWorld != NULL)
		m_matWorld = *pWorld;
	if (pView != NULL)
		m_matView = *pView;
	if (pProj != NULL)
		m_matProj = *pProj;

	m_vRight.x = m_matWorld._11;
	m_vRight.y = m_matWorld._12;
	m_vRight.z = m_matWorld._13;

	m_vUp.x = m_matWorld._21;
	m_vUp.y = m_matWorld._22;
	m_vUp.z = m_matWorld._23;

	m_vLook.x = m_matWorld._31;
	m_vLook.y = m_matWorld._32;
	m_vLook.z = m_matWorld._33;

	m_vPos.x = m_matWorld._41;
	m_vPos.y = m_matWorld._42;
	m_vPos.z = m_matWorld._43;

	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
	return true;
}
/* ========================================================================= */
/* ========================================================================= */
/* ========================================================================= */
bool Create(ID3D11Device* pDevice,
	const char* szPSFunName = "PS",
	const char* szVSFunName = "VS",
	const TCHAR* szShaderName = L"../../Data/Shader/UI_Default.hlsl")
{
	return true;
}
bool JDxObject::SetCamera(float fWidth, float fHeight, float fNear, float fFar)
{
	D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	D3DXMatrixLookAtLH(&m_matView, &vPos, &vTarget, &vUp);
	D3DXMatrixOrthoOffCenterLH(&m_matProj, -(fWidth / 2.0f), fWidth / 2.0f, -(fHeight / 2.0f), fHeight / 2.0f, fNear, fFar);
	return true;
}
bool JDxObject::Create(ID3D11Device* pDevice, const char* szPSFunName, const char* szVSFunName, const TCHAR* szShaderName)
{
	/* 순수가상 */
	return true;
}
bool JDxObject::SetChild(JDxObject& pChild)
{
	pChild.m_vTrans		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pChild.m_vRot		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pChild.m_vScl		= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		  
	pChild.m_pParent = this;
	m_pChildList.push_back(&pChild);
	return true;
}
bool JDxObject::PlayMove(float fX, float fY, float fZ, bool bPlus)
{
	if (bPlus == true)
	{
		m_vTrans.x += fX;
		m_vTrans.y += fY;
		m_vTrans.z += fZ;
	}
	else
	{
		m_vTrans.x -= fX;
		m_vTrans.y -= fY;
		m_vTrans.z -= fZ;
	}
	return true;
}
bool JDxObject::PlayScale(float fX, float fY, float fZ, bool bPlus)
{
	if (bPlus == true)
	{
		m_vScl.x += fX;
		m_vScl.y += fY;
		m_vScl.z += fZ;
	}
	else
	{
		m_vScl.x -= fX;
		m_vScl.y -= fY;
		m_vScl.z -= fZ;
	}
	return true;
}
bool JDxObject::PlayRotate(float fX, float fY, float fZ, bool bPlus)
{
	if (bPlus == true)
	{
		m_vRot.x += fX;
		m_vRot.y += fY;
		m_vRot.z += fZ;
	}
	else
	{
		m_vRot.x -= fX;
		m_vRot.y -= fY;
		m_vRot.z -= fZ;
	}
	return true;
}
bool JDxObject::Init()
{
	SetCamera();
	return true;
}
bool JDxObject::Frame()
{
	D3DXMatrixScaling(&m_matScl, m_vScl.x, m_vScl.y, m_vScl.z);
	D3DXMatrixRotationYawPitchRoll(&m_matRot, m_vRot.z, m_vRot.y, m_vRot.z);
	m_matWorld = m_matScl * m_matRot;
	m_matWorld._41 = m_vTrans.x;
	m_matWorld._42 = m_vTrans.y;
	m_matWorld._43 = m_vTrans.z;

	if (m_pParent)
	{
		m_matWorld = m_pParent->m_matWorld * m_matWorld;
	}

	for (int iChild = 0; iChild < m_pChildList.size(); iChild++)
	{
		m_pChildList[iChild]->Frame();
	}
	return true;
}

bool JDxObject::PreRender(ID3D11DeviceContext* pContext, UINT iVertexSize)
{
	UINT stride = iVertexSize;
	UINT offset = 0;
	if (iVertexSize == 0) stride = m_iVertexSize;
	JState::SetSamplerState(pContext, JState::g_pTexSS);
	pContext->IASetInputLayout(m_pIL);
	pContext->VSSetShader(m_pVS, NULL, 0);
	pContext->PSSetShader(m_pPS, NULL, 0);
	pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	pContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	pContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	if (m_pTexture != NULL && m_pTexture->m_pSRV != NULL)
	{
		pContext->PSSetShaderResources(0, 1, &m_pTexture->m_pSRV);
	}
	return true;
}
bool JDxObject::Render(ID3D11DeviceContext* pContext, UINT iVertexSize, UINT iCount)
{
	SetMatrix(&m_matWorld, &m_matView, &m_matProj);

	pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
	PreRender(pContext, iVertexSize);
	PostRender(pContext, iCount);

	for (int iChild = 0; iChild < m_pChildList.size(); iChild++)
	{
		m_pChildList[iChild]->Render(pContext);
	}
	return true;
}
bool JDxObject::PostRender(ID3D11DeviceContext* pContext, UINT iCount)
{
	if (iCount == 0) iCount = m_iIndexNum;
	if (iCount != 0)
		pContext->DrawIndexed(iCount, 0, 0);
	else
		pContext->Draw(m_iVertexNum, 0);
	return true;
}
bool JDxObject::Release()
{
	SAFE_RELEASE(m_pVertexBuffer)
	SAFE_RELEASE(m_pIndexBuffer)
	SAFE_RELEASE(m_pConstantBuffer)
	SAFE_RELEASE(m_pVS)
	SAFE_RELEASE(m_pPS)
	SAFE_RELEASE(m_pIL)
	SAFE_RELEASE(m_BlobVS)
	SAFE_RELEASE(m_BlobPS)
	SAFE_RELEASE(m_pTexture)
	SAFE_RELEASE(m_pParent)
	m_pChildList.clear();
	
	return true;
}
JDxObject::JDxObject()
{
	m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vLook = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vUp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	/* ======================================= */
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matScl);
	m_vTrans = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vScl = D3DXVECTOR3(100.0f, 100.0f, 1.0f);
	Init();
}
JDxObject::~JDxObject()
{

}