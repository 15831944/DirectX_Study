#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "AseConvert.h"
#include "JDxObject.h"
#include "JDxHelper.h"

using namespace DX;
struct ASE_SCENE
{
	string m_FileName;
	DWORD	m_dwFirstFrame;
	DWORD	m_dwLastFrame;
	DWORD	m_dwTickPerFrame;
};
struct MATERIAL_TEXTURE
{
	int m_iType;
	string m_TextureName;
};
struct ASE_MATERIAL
{
	string m_MaterialName;
	MATERIAL_TEXTURE m_Texture;
};
struct ASE_GEOMETRY
{
	string				m_NodeName;
	D3DXMATRIX			m_matWorld;
	int					m_iFaceNum;
	int					m_iMtrlRef;
	vector<D3DXVECTOR3> m_vPosList;
	vector<D3DXVECTOR3> m_vNorList;
	vector<D3DXVECTOR4> m_vColList;
	vector<D3DXVECTOR2> m_vTexList;
};
class AseObject : public AseConvert
{
public:
	DWORD m_iStartToken;
	DWORD m_dwMaterialCount;
	DWORD  m_dwMtrlRef;

	ASE_SCENE m_Scene;
	vector<ASE_MATERIAL> m_MaterialList;
	ASE_GEOMETRY m_GeoMetry;

	JDxObject m_dxObj;
	VSCB		m_cbData;
	D3DXMATRIX	m_matWorld;
	D3DXMATRIX	m_matView;
	D3DXMATRIX	m_matProj;
	D3DXVECTOR3				 m_vPos;
	D3DXVECTOR3				 m_vLook;
	D3DXVECTOR3			 	 m_vUp;
	D3DXVECTOR3				 m_vRight;
public:
	char* Divide(const char* pszFileName);
	string DestroyQuotationMark(const char* szName);
	bool AseLoad(const TCHAR* szFileName);
	bool CutScene();
	bool CutMaterial();
	bool CutGeoMetryObject();
	void SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
public:
	bool Init();
	bool Frame();
	bool Render(ID3D11DeviceContext* context);
	bool Release();
public:
	AseObject();
	virtual ~AseObject();
};

