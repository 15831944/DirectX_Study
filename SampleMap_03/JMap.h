#pragma once
#include "JShape.h"
#define MAP_HEIGHT 0.1f
struct JVertexLookUp
{
	vector<DWORD> NormalList;
};
class JMap : public JPlaneShape
{
public:
	vector<D3DXVECTOR3>		m_pFaceNormalList;
	vector<JVertexLookUp>	m_pNormalLookUpTable;
	vector<PNCT_VERTEX>		m_pVertices;
	vector<DWORD>			m_pIndices;
	int						m_iNumCols;
	int						m_iNumRows;
	float*					m_fHeightMap;
	int						m_iFaceCnt;
	float					m_fCellSize;
	int						VerticeSize;
	int						m_iCellCols;
	int						m_iCellRows;
	int						m_iWidth;
	int						m_iHeight;
	float					m_fHeightScale;
public:
	float GetHeight(float fX, float fZ);
	float GetHeightOfVertex(UINT iIndex);
	void CalcPerVertexNormalsFastLookup();
	void GenNormalLookUpTable();
	void InitFaceNormal();
	D3DXVECTOR3 ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2);
	void CreateNormalVertex();
	D3DXVECTOR3 GetNormalOfVertex(int iIndex);
	bool SetHeightTexture(ID3D11DeviceContext* context, const TCHAR* szTexName);
	bool Init();
	bool Create(ID3D11Device* device, int iWidth, int iHeight, int iCellSize);
	bool Render(ID3D11DeviceContext* context);
	bool Release();
public:
	JMap();
	virtual ~JMap();
};