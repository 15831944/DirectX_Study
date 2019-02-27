#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "JStd.h"
#include "JDxHelper.h"
#include "JPaser.h"
#include "JWrite.h"
//#include "JMesh.h"
class AseObject
{
public:
	JPaser							m_Paser;
	vector<MeshData>				m_pMesh;
	ASE_SCENE						m_Scene;
	float m_fCurrentTick;
public:
	vector<TRACK*>				m_pPos;
	vector<TRACK*>				m_pRot;
	vector<TRACK*>				m_pScale;
	D3DXMATRIX					m_matCalc;
	D3DXMATRIX					m_matWorld;
	D3DXMATRIX					m_matTrans;
	D3DXMATRIX					m_matRotate;
	D3DXMATRIX					m_matScale;
public:
	bool FindCurrentTrack(vector<TRACK*> mesh, float tick, TRACK** start, TRACK** end);
	bool Interpolate(float CurrentTick);
	bool Load(ID3D11Device* device, const TCHAR* AseFileName);
	bool SetData();
	bool Draw(ID3D11DeviceContext* context, D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
public:
	bool Init();
	bool Frame();
	bool Render(ID3D11DeviceContext* context);
	bool Release();
public:
	AseObject();
	virtual ~AseObject();
};
