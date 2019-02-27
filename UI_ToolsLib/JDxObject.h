#pragma once
#include "TextureMgr.h"
#include "Model.h"
#include "JDxHelper.h"
#include "JState.h"
using namespace DX;
class JDxObject : public Model
{
public:
	Texture*				 m_pTexture;
	wstring					 m_NodeName;
	wstring					 m_ParentName;
	vector<JDxObject*>		 m_pChildList;
	JDxObject*				 m_pParent;
public:
	vector<PNCT_VERTEX>		 m_pVertices;
	vector<DWORD>			 m_pIndices;
public:
	D3DXMATRIX				 m_matWorld;
	D3DXMATRIX				 m_matView;
	D3DXMATRIX				 m_matProj;
public:
	VSCB					 m_cbData;
	D3DXVECTOR3				 m_vPos;
	D3DXVECTOR3				 m_vLook;
	D3DXVECTOR3			 	 m_vUp;
	D3DXVECTOR3				 m_vRight;
public:
	D3DXMATRIX				 m_matRot;
	D3DXMATRIX				 m_matScl;
	D3DXVECTOR3				 m_vTrans;
	D3DXVECTOR3				 m_vRot;
	D3DXVECTOR3				 m_vScl;
public:
	float					 m_fWidth;
	float					 m_fHeight;
public:
	bool SetChild(JDxObject& pChild);
	bool SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	bool SetTexture(ID3D11Device* device, const TCHAR* szTexName);
	bool PlayMove(float fX, float fY, float fZ, bool bPlus = true);
	bool PlayScale(float fX, float fY, float fZ, bool bPlus = true);
	bool PlayRotate(float fX, float fY, float fZ, bool bPlus = true);
public:
	virtual bool SetCamera(float fWidth = 800.0f, float fHeight = 600.0f, float fNear = 0.1f, float fFar = 1.0f);
	virtual bool Create(ID3D11Device* pDevice,
						const char* szPSFunName = "PS",
						const char* szVSFunName = "VS",
						const TCHAR* szShaderName = L"../../Data/Shader/UI_Default.hlsl");
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool PreRender(ID3D11DeviceContext* pContext, UINT iVertexSize = 0);
	virtual bool Render(ID3D11DeviceContext* pContext, UINT iVertexSize = 0, UINT iCount = 0);
	virtual bool PostRender(ID3D11DeviceContext* pContext, UINT iCount = 0);
	virtual bool Release();
public:
	JDxObject();
	virtual ~JDxObject();
};