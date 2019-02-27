#pragma once
#include "JBoxShape.h"
#include "JState.h"

class JSkyBox : public JBoxShape
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
	JSkyBox();
	virtual ~JSkyBox();
};