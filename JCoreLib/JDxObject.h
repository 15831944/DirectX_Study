#pragma once
#include "JTextureMgr.h"
#include "JDxHelper.h"
class JDxObject : public JTextureMgr
{
public:
	ID3D11Buffer*			 m_pVertexBuffer;
	ID3D11Buffer*			 m_pIndexBuffer;
	ID3D11Buffer*			 m_pConstantBuffer;
	ID3D11VertexShader*		 m_pVS;
	ID3D11PixelShader*		 m_pPS;
	ID3D11GeometryShader*    m_pGS;
	ID3D11InputLayout*		 m_pIL;
	ID3DBlob*				 m_BlobVS;
	ID3DBlob*				 m_BlobPS;
	ID3DBlob*				 m_BlobGS;
	JTexture*				 m_pTexture;
	int						 m_iTexture;
	UINT					 m_iVertexNum;
	UINT					 m_iIndexNum;
	UINT					 m_iVertexSize;
	UINT					 m_iIndexSize;
public:
	bool PreRender(ID3D11DeviceContext* context, UINT iVertexSize);
	bool Render(ID3D11DeviceContext* context, UINT iVertexSize = 0, UINT iCount = 0);
	bool PostRender(ID3D11DeviceContext* context, UINT iCount);
	bool Release();
public:
	JDxObject();
	virtual ~JDxObject();
};