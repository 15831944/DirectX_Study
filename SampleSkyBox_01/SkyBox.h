#pragma once
#include "JBoxShape.h"
#include "JState.h"

class SkyBox : public JBoxShape
{
public:
	JTexture * m_Tex[6];
	D3DXMATRIX m_matSkyView;
public:
	bool Create(ID3D11Device* device, const TCHAR* szSkyName[]);
	bool Frame();
	bool Render(ID3D11DeviceContext* context);
	bool Release();
public:
	SkyBox();
	virtual ~SkyBox();
};