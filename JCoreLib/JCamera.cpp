#include "JCamera.h"
#include "JDxInput.h"
#include "JInput.h"
#include "JWrite.h"

D3DXMATRIX JCamera::SetViewMatrix(D3DXVECTOR3 vPosition, D3DXVECTOR3 vTarget, D3DXVECTOR3 vUp)
{
	m_vCameraPos = vPosition;
	m_vTargetPos = vTarget;

	D3DXMatrixLookAtLH(&m_matView, &vPosition, &vTarget, &vUp);
	D3DXMATRIX matInvView;
	D3DXMatrixInverse(&matInvView, NULL, &m_matView);


	D3DXVECTOR3* pZ = (D3DXVECTOR3*)&matInvView._31;
	m_fYaw = atan2f(pZ->x, pZ->z);
	float fLen = sqrtf(pZ->z*pZ->z + pZ->x*pZ->x);
	m_fPitch = -atan2f(pZ->y, fLen);

	m_vLook.x = m_matView._13;
	m_vLook.y = m_matView._23;
	m_vLook.z = m_matView._33;
	m_vRight.x = m_matView._11;
	m_vRight.y = m_matView._21;
	m_vRight.z = m_matView._31;
	m_vUp.x = m_matView._12;
	m_vUp.y = m_matView._22;
	m_vUp.z = m_matView._32;

	return m_matView;
}
D3DXMATRIX JCamera::SetProjMatrix(ID3D11DeviceContext* context, float Fovy, float Aspect, float Near, float Far)
{
	m_fFovy = Fovy;
	m_fAspect = Aspect;
	m_fNearPlane = Near;
	m_fFarPlane = Far;
	D3DXMatrixPerspectiveFovLH(&m_matProj, Fovy, Aspect, Near, Far);
	CreateFrustum(context, m_matView, m_matProj);
	return m_matProj;
}
D3DXMATRIX JCamera::SetProjMatrix(float Fovy, float Aspect, float Near, float Far)
{
	m_fFovy = Fovy;
	m_fAspect = Aspect;
	m_fNearPlane = Near;
	m_fFarPlane = Far;
	D3DXMatrixPerspectiveFovLH(&m_matProj, Fovy, Aspect, Near, Far);
	return m_matProj;
}
D3DXMATRIX JCamera::SetOrthoMatrix(float Width, float Height, float Near, float Far)
{
	D3DXMatrixOrthoLH(&m_matProj, Width, Height, Near, Far);
	return m_matProj;
}
bool JCamera::Update(float lX, float lY, float lZ, float Radius)
{
	//D3DXMATRIX matRot, matRotX, matRotY, matRotZ;
	//D3DXMatrixRotationYawPitchRoll(&matRot, lX, lY, lZ);
	//D3DXMatrixRotationX(&matRotX, lX);
	//D3DXMatrixRotationY(&matRotY, lY);
	//D3DXMatrixRotationZ(&matRotZ, lZ);
	//matRot = matRotY * matRotX * matRotZ;
	//matRot._41 = m_vCameraPos.x;
	//matRot._42 = m_vCameraPos.y;
	//matRot._43 = m_vCameraPos.z;
	//D3DXMatrixInverse(&m_matView, NULL, &matRot);

	D3DXMATRIX matWorld;
	D3DXQuaternionRotationYawPitchRoll(&m_qRotation, lY, lX, lZ);

	m_vCameraPos += m_vLook * Radius;
	D3DXMatrixAffineTransformation(&m_matWorld,
		1.0f, NULL, &m_qRotation, &m_vCameraPos);
	D3DXMatrixInverse(&m_matView, NULL, &m_matWorld);

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
bool JCamera::Init()
{
	return true;
}
bool JCamera::Frame()
{
	if (I_InputDx.m_MouseState.rgbButtons[0])
	{
		m_fYaw += D3DXToRadian(I_InputDx.m_MouseState.lX * 0.1f);
		m_fPitch += D3DXToRadian(I_InputDx.m_MouseState.lY * 0.1f);
	}
	if (I_InputDx.m_MouseState.lZ != 0)
	{
		m_fRadius = I_InputDx.m_MouseState.lZ * g_fSecPerFrame * m_fSpeed;
	}
	else if(I_InputDx.m_MouseState.lZ == 0.0f)
	{
		m_fRadius = 0.0f;
	}
	if (I_InputDx.IsKeyDown(DIK_SPACE))
	{
		m_fSpeed++;
	}
	else
	{
		if (m_fSpeed > 50.0f)
		{
			m_fSpeed--;
		}
	}
	if (I_InputDx.IsKeyDown(DIK_W))
	{
		m_vCameraPos += m_vLook * g_fSecPerFrame * m_fSpeed;
	}
	if (I_InputDx.IsKeyDown(DIK_S))
	{
		m_vCameraPos -= m_vLook * g_fSecPerFrame* m_fSpeed;
	}
	if (I_InputDx.IsKeyDown(DIK_A))
	{
		m_vCameraPos -= m_vRight * g_fSecPerFrame* m_fSpeed;
	}
	if (I_InputDx.IsKeyDown(DIK_D))
	{
		m_vCameraPos += m_vRight * g_fSecPerFrame* m_fSpeed;
	}
	if (I_InputDx.IsKeyDown(DIK_Q))
	{
		m_vCameraPos += m_vUp * g_fSecPerFrame* m_fSpeed;
	}
	if (I_InputDx.IsKeyDown(DIK_E))
	{
		m_vCameraPos -= m_vUp * g_fSecPerFrame* m_fSpeed;
	}

	Update(m_fPitch, m_fYaw, 0.0f, m_fRadius);
	_stprintf_s(m_szCameraPos, L"CameraPos(%f,%f,%f)", m_vCameraPos.x, m_vCameraPos.y, m_vCameraPos.z);
	return true;
}
JCamera::JCamera()
{
	m_fYaw = 0.0f;
	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
	m_fSpeed = 50.0f;
}
JCamera::~JCamera()
{

}