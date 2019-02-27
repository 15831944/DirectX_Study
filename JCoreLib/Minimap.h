#pragma once
#include "JPlaneShape.h"
#include "DxRT.h"
#include "JCamera.h"
class Minimap : public JCamera
{
public:
	DxRT m_RT;
	JPlaneShape m_Screen;
	JPlaneShape m_Minimap;
	D3D11_VIEWPORT m_MinimapViewPort;
	ID3D11ShaderResourceView * m_pSRV;
public:
	bool Create(ID3D11Device* device, FLOAT fTopX, FLOAT fTopY, FLOAT fWidth, FLOAT fHeight, FLOAT fRTWidth = 1024.0f, FLOAT fRTHeight = 1024.0f,
		const char* szPSFunName = "PS", const char* szVSFunName = "VS", const TCHAR* szShaderName = L"../../Data/Shader/Default.hlsl");
	bool ScreenRender(ID3D11DeviceContext* context);
	bool Render(ID3D11DeviceContext* context, ID3D11ShaderResourceView* pSRV = NULL);
	bool BeginRender(ID3D11DeviceContext* context, D3DXVECTOR4 vColor, bool bTarget = true, bool bDepth = true, bool bStencil = true);
	bool EndRender(ID3D11DeviceContext* context);
public:
	Minimap();
	virtual ~Minimap();
};

