#pragma once
#include "JStd.h"
#include "Plane.h"
#include "DxRT.h"
#include "JCamera.h"
class Minimap : public JCamera
{
public:
	DxRT m_RT;
	Plane m_Screen;
	Plane m_Minimap;
	D3D11_VIEWPORT m_MinimapViewPort;
public:
	bool Create(ID3D11Device* device, FLOAT fTopX, FLOAT fTopY, FLOAT fWidth, FLOAT fHeight);
	//bool Frame();
	bool Render(ID3D11DeviceContext* context);
	bool BeginRender(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget = true, bool bDepth = true, bool bStencil = true);
	bool EndRender(ID3D11DeviceContext* context);
public:
	Minimap();
	virtual ~Minimap();
};

