#pragma once
#include "JShape.h"
class JBoxShape : public JShape
{
public:
	bool Create(const char* szPSFunName = "PS", const char* szVSFunName = "VS", const TCHAR* szShaderName = L"../../Data/Shader/Default.hlsl");
	bool Init();
	bool Frame();
	bool PreRender(ID3D11DeviceContext* context, UINT iVertexSize = 0);
	bool Render(ID3D11DeviceContext* context, UINT iVertexSize = 0, UINT iCount = 0);
	bool PostRender(ID3D11DeviceContext* context, UINT iCount = 0);
public:
	JBoxShape();
	virtual ~JBoxShape();
};