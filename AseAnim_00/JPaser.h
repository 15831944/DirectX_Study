#pragma once
#define _CRT_SECURE_NO_WARNINGS
//#include "JStd.h"
#include "JMesh.h"
enum MaterialType { DIFFUSE = 1 };
class JPaser
{
public:
	vector<MeshData>			m_pMeshList;
public:
	ASE_SCENE					m_Scene;
	vector<ASE_MATERIAL>		m_Mtrl;
	ASE_GEOMETRY					m_Geom;
public:
	vector<TRACK*> m_pPos;
	vector<TRACK*> m_pRot;
	vector<TRACK*> m_pScale;
public:
	vector<TRACK*> m_pTrasTrack;
	vector<TRACK*> m_pRotateTrack;
	vector<TRACK*> m_pScaleTrack;
public:
	D3DXMATRIX					matWorld;
	D3DXMATRIX					matInvWorld;
	D3DXMATRIX					matTrans;
	D3DXMATRIX					matRotate;
	D3DXMATRIX					matScale;
private:
	char*						m_pData;
	LARGE_INTEGER				m_lFileSize;
	vector<string>				m_Tokenlist;
	string						m_CurrentToken;
	DWORD						m_dwMaxTokenLine;
	DWORD						m_dwTokenIndex;
	DWORD						m_dwFaceSize;
public:
	TRACK * SetDoublyLinkedList(TRACK* pCurrentTrack, TRACK* pPrev);
public:
	vector<MeshData> GetData();
	vector<TRACK*> GetPos();
	vector<TRACK*> GetRot();
	vector<TRACK*> GetScl();
	bool clear();
public:
	bool LoadScene();
	bool LoadMaterial();
	bool LoadGeom();
	bool Load();
public:
	bool LoadAseFile(const TCHAR* AseFileName);
	string DestroyToken(const char* szName, const char* szToken);
	string DestroyTokenName(const char* szName, const char* szToken);
	string DividePath(const char* pszFileName);
	INT FindToken(string szToken);
	//vector<PNCT_VERTEX> CutTriangle(vector<ASE_TRIANGLE> triangle);
	const char* GetNextToken();
	void GenTriangle();
	bool TriangleSubID();
	bool Convert();
public:
	JPaser();
	virtual ~JPaser();
};

