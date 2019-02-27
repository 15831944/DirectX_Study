#pragma once
#include "JDxObject.h"
class Shape : public JDxObject
{
public:
	ID3D11Buffer*			 m_pInstanceBuffer;
	//vector<Instance>		 m_pInstance;
	int						 m_iCount;
	bool					 m_bInstanced;
public:
	//virtual void CreateInstance(ID3D11Device* pDevice, UINT iNumInstance);
	virtual bool Create(ID3D11Device* pDevice,
		const char* szPSFunName = "PS",
		const char* szVSFunName = "VS",
		const TCHAR* szShaderName = L"../../Data/Shader/UI_Default.hlsl");
	virtual void Draw(ID3D11DeviceContext* context, D3DXVECTOR3 vPos, D3DXVECTOR3 vEnd, D3DXVECTOR4 vColor);
public:
	Shape();
	virtual ~Shape();
};

