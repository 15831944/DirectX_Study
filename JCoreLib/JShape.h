#pragma once
#include "JStd.h"
#include "JDxHelper.h"
#include "JDxObject.h"
#include "JState.h"
using namespace DX;
class JShape
{
public:
	ID3D11Buffer*			 m_pInstanceBuffer;
	vector<Instance>		 m_pInstance;
	int						 m_iCount;
	bool					 m_bInstanced;
public:
	JDxObject				 m_dxObj;
	VSCB					 m_cbData;
	D3DXMATRIX				 m_matWorld;
	D3DXMATRIX				 m_matView;
	D3DXMATRIX				 m_matProj;
	int						 m_iPrimitiveType;
	D3DXVECTOR3				 m_vPos;
	D3DXVECTOR3				 m_vLook;
	D3DXVECTOR3			 	 m_vUp;
	D3DXVECTOR3				 m_vRight;
	vector<PNCT_VERTEX>		 m_pVertices;
	vector<DWORD>			 m_pIndices;
	fRECT					 m_rt;
public:
	virtual void ChangedVertexShader(const char* szFuntionName = "VS", const TCHAR* szShaderName = L"../../Data/Shader/Default.hlsl");
	virtual void ChangedPixelShader(const char* szFuntionName = "PS", const TCHAR* szShaderName = L"../../Data/Shader/Default.hlsl");
	virtual void SetTexture(const TCHAR* szTexName);
	virtual void CreateInstance(UINT iNumInstance);
	virtual void SetInstanceIL();
	virtual void SetCount(int iCount);
	virtual bool Create(const char* szPSFunName = "PS", const char* szVSFunName = "VS", const TCHAR* szShaderName = L"../../Data/Shader/Default.hlsl");
	virtual bool Init();
	virtual bool Frame();
	virtual bool PreRender(ID3D11DeviceContext* context, UINT iVertexSize = 0);
	virtual bool Render(ID3D11DeviceContext* context, UINT iVertexSize = 0, UINT iCount = 0);
	virtual bool PostRender(ID3D11DeviceContext* context, UINT iCount = 0);
	virtual bool Release();
	virtual void SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
	virtual void Draw(ID3D11DeviceContext* context, D3DXVECTOR3 vPos, D3DXVECTOR3 vEnd, D3DXVECTOR4 vColor);
public:
	JShape();
	virtual ~JShape();
};