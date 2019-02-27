#pragma once
#include "JShape.h"
#include "JState.h"
class Plane : public JShape
{
public:
	ID3D11ShaderResourceView * m_pSRV;
public:
	bool Init();
	bool Frame();
	bool PreRender(ID3D11DeviceContext* context, UINT iVertexSize);
	bool Render(ID3D11DeviceContext* context, UINT iVertexSize = 0, UINT iCount = 0);
	bool PostRender(ID3D11DeviceContext* context, UINT iCount);
public:
	Plane();
	virtual ~Plane();
};

