#pragma once
#include "JMap.h"
class NormalMap : public JMap
{
public:
	vector<D3DXVECTOR3> m_vTangentList;
	ID3D11Buffer* m_pTangentVB;
	T_STR m_strNormalMapName;
	INT m_itxNormalMap;
	JTexture* m_pNormalTexture;
	D3DXMATRIX m_matNormal;
public:
	bool Create(ID3D11Device* device, int iWidth, int iHeight, int iCellSize);
	bool Render(ID3D11DeviceContext* context);
	bool UpdateBuffer();
	HRESULT LoadTextures(ID3D11Device* device, const TCHAR* pLoadTextureString);
	void SetMatrix(const D3DXMATRIX* pWorld, const D3DXMATRIX* pView, const D3DXMATRIX* pProj);
public:
	NormalMap();
	virtual ~NormalMap();
};

