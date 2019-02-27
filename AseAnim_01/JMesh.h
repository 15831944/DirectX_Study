#pragma once
#include "JModel.h"
#include "JDxHelper.h"
class AseMesh;
class JMesh
{
public:
	vector<AseMesh>					m_pSubMeshList;
	vector<AnimTrack*>				m_pTransTrack;
	vector<AnimTrack*>				m_pRotateTrack;
	vector<AnimTrack*>				m_pScaleTrack;
	D3DXMATRIX						m_matCalc;
	D3DXMATRIX						m_matAseWorld;
	D3DXMATRIX						m_matLocalWorld;
	D3DXMATRIX						m_matLocalTrans;
	D3DXMATRIX						m_matLocalRotate;
	D3DXMATRIX						m_matLocalScale;
	string							m_strNodeName;
	string							m_strParentName;
	JMesh*							m_pParent;
	JMesh*							m_pChild;
public:
	bool Draw(ID3D11DeviceContext* context, D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
	bool Frame();
	bool Render(ID3D11DeviceContext* context);
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
class AseMesh : public JModel
{
public:
	vector<PNCT_VERTEX>			m_pVertexList;
	vector<DWORD>				m_pIndexList;
	vector<ASE_TRIANGLE>		m_pTriangleList;
	string						m_pTexName;
public:
	//void SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
	bool Create(ID3D11Device* device);
	bool LoadTexFile(ID3D11Device* device, string szTexName);
public:
	bool Render(ID3D11DeviceContext* context);
public:
	AseMesh();
	virtual ~AseMesh();
};

