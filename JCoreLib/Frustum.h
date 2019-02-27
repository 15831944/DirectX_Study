#pragma once
#include "JBoxShape.h"

class Frustum
{
public:
	JBoxShape * m_pBox;
	D3DXVECTOR3 m_vFrustum[8];
	vector<PNCT_VERTEX> m_VertexList;
	D3DXMATRIX m_mWorld, m_mView, m_mProj, m_matViewProj;
public:
	bool SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
	bool CreateFrustum(ID3D11DeviceContext* context, D3DXMATRIX matView, D3DXMATRIX matProj);
	bool Init();
	bool PreRender(ID3D11DeviceContext* context);
	bool Render(ID3D11DeviceContext* context);
	bool PostRender(ID3D11DeviceContext* context);
public:
	Frustum();
	virtual ~Frustum();
};