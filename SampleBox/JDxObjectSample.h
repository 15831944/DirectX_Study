#pragma once
#include "JInterface.h"
#define VertexListCnt 6

class JDxObjectSample : public JInterface
{
public:
	JVertex VertexList[VertexListCnt];
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11Buffer* m_pConstantBuffer;
	JImage* m_Image;
	JImage* m_ImageMask;
	int		m_iImage;
	int		m_iImageMask;
	fRECT m_rt;
	fPOINT m_Pos;
public:
	bool Load(ID3D11Device* device, const TCHAR* pszTexLoadName, const TCHAR* pszTexMaskLoadName = NULL);
	ID3D11Buffer * CreateVertexBuffer(ID3D11Device* device, void* pSysMem, UINT VertexSize = sizeof(JVertex), UINT VertexCnt = VertexListCnt);
	ID3D11Buffer * CreateIndexBuffer(ID3D11Device* device, void* pSysMem, UINT VertexSize, UINT VertexCnt);
	ID3D11Buffer * CreateConstantBuffer(ID3D11Device* device, void* pSysMem, UINT VertexSize, UINT VertexCnt);
	void SetRect(float left, float top, float right, float bottom, float fZ = 1.0f);
	void SetTex(fRECT& rt, fPOINT& m_Size);
	bool UpdatePosition(fRECT rt);
public:
	bool Init();
	bool Frame();
	bool PreRender(ID3D11DeviceContext* context, UINT VertexSize);
	bool Render(ID3D11DeviceContext* context, UINT VertexSize, UINT VertexCnt = VertexListCnt);
	bool PostRender(ID3D11DeviceContext* context, UINT VertexCnt = VertexListCnt);
	void UpdatePos(fRECT deck);
	virtual bool Release();
public:
	JDxObjectSample();
	virtual ~JDxObjectSample();
};
