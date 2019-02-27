#pragma once
#include "JModel.h"
#include "JDxHelper.h"
class JMesh;
struct MeshData
{
	vector<JMesh>				m_pSubMeshList;
};
struct TRACK_POS
{
	int iTick;
	D3DXVECTOR3 vPos;
};
struct TRACK_ROT
{
	int iTick;
	D3DXVECTOR4 vRot;
};
struct TRACK_SCALE
{
	int iTick;
	D3DXVECTOR3 vScale;
	D3DXQUATERNION qScale;
};
struct TRACK
{
	int iTick;
	D3DXQUATERNION qRot;
	D3DXVECTOR3    vPos;
	TRACK*		   PrevTrack;
	TRACK*		   NextTrack;
};
class JMesh : public JModel
{
public:
	vector<PNCT_VERTEX>			m_pVertexList;
	vector<DWORD>				m_pIndexList;
	vector<ASE_TRIANGLE>		m_pTriangleList;
	string						m_pTexName;
public:
	//vector<DWORD> SetIndex(vector<ASE_TRIANGLE> pData);
	//void SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
	bool Create(ID3D11Device* device);
	bool LoadTexFile(ID3D11Device* device, string szTexName);
public:
	bool Render(ID3D11DeviceContext* context);
public:
	JMesh();
	virtual ~JMesh();
};

