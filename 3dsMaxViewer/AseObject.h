#pragma once
#include "JStd.h"
#include "JDxHelper.h"
#include "Parser.h"
#include "JWrite.h"
//#include "AseMesh.h"
class AseObject
{
public:
	float m_fCurrentTick;
	Parser							m_Paser;
	ASE_SCENE						m_Scene;
	vector<JMesh*>					m_pMesh;
public:
	bool Load(ID3D11Device* device, const TCHAR* AseFileName);
	bool SetData();
	bool Draw(ID3D11DeviceContext* context, D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
	bool Interpolate(JMesh* pMesh, D3DXMATRIX* matParents, float fFrameTick);
	bool GetAnimationTrack(float fFrame, vector<AnimTrack*> pTrackList, AnimTrack** pStartTrack, AnimTrack** pEndTrack);
public:
	bool Init();
	bool Frame();
	bool Render(ID3D11DeviceContext* context);
	bool Release();
public:
	AseObject();
	virtual ~AseObject();
};
