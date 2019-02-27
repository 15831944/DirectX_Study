#pragma once
#include "JDxObject.h"
using namespace DX;
class UserInterface
{
public:
	wstring					 m_szNodeName;
	wstring					 m_szParentName;
	UserInterface*			 m_pParent;
	vector<UserInterface*>	 m_pChildList;
public:
	int						 m_iIndex;
	JDxObject				 m_dxObj; // Object Buffers
	vector<PNCT_VERTEX>		 m_pVertices;
	vector<DWORD>			 m_pIndices;
	VSCB					 m_cbData;
public:
	vector<JTexture*> 		 m_pTextureList;
	wstring					 m_strTexName;
public:
	D3DXMATRIX			 	 m_matTrans;
	D3DXMATRIX				 m_matScale;
	D3DXMATRIX				 m_matRotate;
	float					 m_fAngle;
public:
	D3DXMATRIX				 m_matWorld;
	D3DXMATRIX				 m_matView;
	D3DXMATRIX				 m_matProj;
	D3DXVECTOR3				 m_vLook;
	D3DXVECTOR3			 	 m_vUp;
	D3DXVECTOR3				 m_vRight;
	D3DXVECTOR3				 m_vPos;
public:
	fRECT					 m_rtPos;
public:
	/* ====================Sprite==================== */
	float					 m_fSec;
	bool					 m_bPlay;
	bool					 m_bLoop;
	int						 m_iStart;
	float					 m_fFrameUpdateSec;
	float					 m_fFrameElapseSec;
public:
	virtual bool			 SetUp(float fSec);
	virtual bool			 Update();
	virtual bool			 SetLoop();
	virtual bool			 SetPlay();
	virtual bool			 DeleteTexture(const TCHAR* szTexName);
	/* =============================================== */
public:
	virtual bool Add(UserInterface* pUI);
	virtual UserInterface* GetParent();
	virtual bool SetParent(UserInterface* pUI);
	virtual bool ChangedColor(ID3D11DeviceContext* pContext, D3DXVECTOR4 vColor);
	virtual bool UpdateRect();
public:
	virtual bool SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	virtual bool Set(RECT rt);
	virtual bool InitWorldMatrix();
	virtual bool InitMatrixView();
	virtual bool InitMatrixProj(float Width, float Height, float Near = 0.1f, float Far = 1.0f);
	virtual bool Create();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool PreRender(ID3D11DeviceContext* context, UINT iVertexSize);
	virtual bool Render(ID3D11DeviceContext* context, UINT iVertexSize = 0, UINT iCount = 0);
	virtual bool PostRender(ID3D11DeviceContext* context, UINT iCount);
	virtual bool Release();
public:
	UserInterface();
	virtual ~UserInterface();
};

