#pragma once
#include "JStd.h"
#include "JLineShape.h"
struct RAY
{
	D3DXVECTOR3 vOrigin;
	D3DXVECTOR3 vDirection;
	float fExtent;
	RAY()
	{
		fExtent = -1;
	}
};
class MousePicking
{
public:
	JLineShape m_Line;
public:
	RAY	m_rRay;
	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
	D3DXVECTOR3 m_vCentor;
	D3DXVECTOR3		m_vSrcVex[3];
	D3DXVECTOR3 m_vIntersection;
	D3DXMATRIX		m_matWorldPick;
	D3DXVECTOR3 qvec;
	D3DXVECTOR3 tvec;
	D3DXVECTOR3 pvec;

public:
	bool Init();
	bool Render(ID3D11DeviceContext* context);
	bool Release();
public:
	void SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
	void Update();
	bool ChkPick(D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2);
	bool IntersectTriangle(const D3DXVECTOR3& orig, const D3DXVECTOR3& dir,
		D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2,
		FLOAT* t, FLOAT* u, FLOAT* v);
public:
	MousePicking();
	virtual ~MousePicking();
};

