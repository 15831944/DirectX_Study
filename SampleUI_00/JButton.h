#pragma once
#include "JShape.h"
typedef vector<PNCT_VERTEX> vVertex;
class JButton : public JShape
{
public:
	vector<PNCT_VERTEX> m_pRenderVertices;
	vector<vVertex> m_pVertices;
	vector<DWORD> m_pIndices;
public:
	void Create(fRECT rt, float u0, float v0, float u1, float v1);
	bool Init();
	bool Frame();
	bool PreRender(ID3D11DeviceContext* context, UINT iVertexSize = 0);
	bool PostRender(ID3D11DeviceContext* context, UINT iCount = 0);
	bool Render(ID3D11DeviceContext* context, UINT iVertexSize = 0, UINT iCount = 0);
	bool Release();
public:
	JButton();
	virtual ~JButton();
};

