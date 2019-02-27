#pragma once
#include "JDxObject.h"
class JModel
{
public:
	JDxObject					m_dxObj;
	VSCB						m_cbData;
	D3DXMATRIX					m_matWorld;
	D3DXMATRIX					m_matView;
	D3DXMATRIX					m_matProj;
	int							m_iPrimitiveType;
	D3DXVECTOR3					m_vPos;
	D3DXVECTOR3					m_vLook;
	D3DXVECTOR3			 		m_vUp;
	D3DXVECTOR3					m_vRight;
public:
	virtual void SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	JModel();
	virtual ~JModel();
};