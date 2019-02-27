#pragma once
#include "UI_Std.h"
class Model
{
protected:
	ID3D11Buffer*			 m_pVertexBuffer;
	ID3D11Buffer*			 m_pIndexBuffer;
	ID3D11Buffer*			 m_pConstantBuffer;
	ID3D11VertexShader*		 m_pVS;
	ID3D11PixelShader*		 m_pPS;
	ID3D11InputLayout*		 m_pIL;
	ID3DBlob*				 m_BlobVS;
	ID3DBlob*				 m_BlobPS;
public:
	UINT					 m_iVertexNum;
	UINT					 m_iIndexNum;
	UINT					 m_iVertexSize;
	UINT					 m_iIndexSize;
public:
	Model();
	virtual ~Model();
};

