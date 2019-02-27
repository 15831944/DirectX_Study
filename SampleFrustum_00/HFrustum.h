#pragma once
#include "HPlane.h"
#include "JBoxShape.h"
class HFrustum
{
public:
	JBoxShape * m_pBox;
	// 평면 6개
	HPlane		m_Plane[6];
	// 정점 8 개
	D3DXVECTOR3 m_vFrustum[8];
	//vector<PNCT_VERTEX> m_pVertices;
	JBoxShape m_box;
	D3DXMATRIX m_matWorld, m_matView, m_matProj, m_matViewProj;
public:
	bool SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
	bool CreateFrustum(ID3D11DeviceContext* context, D3DXMATRIX matView, D3DXMATRIX matProj);
	bool Init();
	bool PreRender(ID3D11DeviceContext* context);
	bool Render(ID3D11DeviceContext* context);
	bool PostRender(ID3D11DeviceContext* context);
public:
	HFrustum();
	virtual ~HFrustum();
};

