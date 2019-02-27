#pragma once
#include "JInterface.h"
#define VertexListCnt 6

class JObject : public JInterface
{
public:
	JVertex VertexList[VertexListCnt];
	ID3D11Buffer* m_pVertexBuffer;
	JImage* m_Image;
	JImage* m_ImageMask;
	int		m_iImage;
	int		m_iImageMask;
	fRECT	m_rt;
	fPOINT	m_Pos;
public:
	bool Load(ID3D11Device* device, const TCHAR* pszTexLoadName, const TCHAR* pszTexMaskLoadName = NULL);
	ID3D11Buffer * CreateVertexBuffer(ID3D11Device* device);
	void SetRect(float left, float top, float right, float bottom);
	void SetTex(fRECT& rt, fPOINT& m_Size);
	bool UpdatePosition(fRECT rt);
public:
	bool Init();
	bool Frame();
	bool PreRender(ID3D11DeviceContext* context);
	bool Render(ID3D11DeviceContext* context);
	bool PostRender(ID3D11DeviceContext* context);
	void UpdatePos(fRECT deck);
	virtual bool Release();
public:
	JObject();
	virtual ~JObject();
};
