#pragma once
#include "Frustum.h"
class JCamera : public Frustum
{
private:
	friend class JSingleton<JCamera>;
public:
	D3DXMATRIX					m_matWorld;
	D3DXMATRIX					m_matView;
	D3DXMATRIX					m_matProj;
	D3DXVECTOR3					m_vLook;
	D3DXVECTOR3					m_vRight;
	D3DXVECTOR3					m_vUp;

	D3DXVECTOR3					m_vCameraPos;
	D3DXVECTOR3					m_vTargetPos;
	D3DXVECTOR3					m_vDirection;

	FLOAT						m_fFovy;
	FLOAT						m_fAspect;
	FLOAT						m_fNearPlane;
	FLOAT						m_fFarPlane;

	FLOAT						m_fYaw;    // y
	FLOAT						m_fPitch;  // x
	FLOAT						m_fRoll;   // z
	FLOAT						m_fRadius; // w

	float						m_fSpeed;

	TCHAR						m_szCameraPos[256];
	TCHAR						m_szCameraName[256];
	D3DXQUATERNION				m_qRotation;
public:
	D3DXMATRIX SetViewMatrix(D3DXVECTOR3 vPosition, D3DXVECTOR3 vTarget, D3DXVECTOR3 vUp);
	D3DXMATRIX SetProjMatrix(ID3D11DeviceContext* context, float Fovy, float Aspect, float Near, float Far);
	D3DXMATRIX SetProjMatrix(float Fovy, float Aspect, float Near, float Far);
	D3DXMATRIX SetOrthoMatrix(float Width, float Height, float Near, float Far);
	bool Update(float lX, float lY, float lZ, float Radius);

	bool Init();
	bool Frame();

public:
	JCamera();
	virtual ~JCamera();
};