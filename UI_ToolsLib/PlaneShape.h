#pragma once
#include "Shape.h"
class PlaneShape : public Shape
{
public:
	bool Create(ID3D11Device* pDevice,
		const char* szPSFunName = "PS",
		const char* szVSFunName = "VS",
		const TCHAR* szShaderName = L"../../Data/Shader/UI_Default.hlsl");
public:
	PlaneShape();
	virtual ~PlaneShape();
};

