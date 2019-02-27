#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "JStd.h"
#include "JDxHelper.h"
#include "JPaser.h"
#include "JWrite.h"
//#include "AseMesh.h"
class AseObject
{
public:
	float m_fCurrentTick;
	JPaser							m_Paser;
	ASE_SCENE						m_Scene;
	vector<JMesh*>					m_pMesh;
public:
	bool Load(ID3D11Device* device, const TCHAR* AseFileName);
	bool SetData();
	bool Draw(ID3D11DeviceContext* context, D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
	bool Interpolate(JMesh* pMesh, float fCurrentTick, D3DXMATRIX matParentCalc);
public:
	bool Init();
	bool Frame();
	bool Render(ID3D11DeviceContext* context);
	bool Release();
public:
	AseObject();
	virtual ~AseObject();
};
