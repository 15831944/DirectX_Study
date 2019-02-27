#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "JStd.h"
#include "JShape.h"
#include "JDxHelper.h"
enum MaterialType { DIFFUSE = 1 };
struct ASE_SCENE
{
	int iFirstFrame;
	int iLastFrame;
	int iFrameSpeed;
	int iTickPerFrame;
};
struct ASE_TEXTURE
{
	int iType;
	string strTexName;
};
struct ASE_MATERIAL
{
	string strMtrlName;
	vector<ASE_TEXTURE> tex;
	vector<ASE_MATERIAL> subMtrl;
};
struct ASE_VERTEX
{
	float p[3];
	float n[3];
	float c[4];
	float t[2];
};
struct ASE_TRIANGLE
{
	ASE_VERTEX v[3];
	DWORD dwSubID;
};

struct ASE_INDEX
{
	DWORD i[3];
	DWORD dwSubID;
};
struct ASE_FACENORMAL
{
	float fn[3];
	float vn[3][3];
};
struct ASE_GEOMETRY
{
	int							iGeomMtrlRef;
	string						strNodeName;
	vector<ASE_VERTEX>			VertexPosList;
	vector<ASE_INDEX>			IndexPosList;
	vector<ASE_VERTEX>			VertexColList;
	vector<ASE_INDEX>			IndexColList;
	vector<ASE_VERTEX>			VertexTexList;
	vector<ASE_INDEX>			IndexTexList;
	vector<ASE_TRIANGLE>		TriangleList;
	vector<ASE_FACENORMAL>		TriNormalList;
};
class AseObject : public JShape
{
public:
	vector<AseObject> m_SubAseObj;
public:
	ASE_SCENE m_Scene;
	vector<ASE_MATERIAL> m_Mtrl;
	ASE_GEOMETRY m_Geom;
public:
	vector<ASE_VERTEX> m_pVertexList;
	vector<DWORD> m_pIndexList;
private:
	char* m_pData;
	LARGE_INTEGER m_lFileSize;
	vector<string> m_Tokenlist;
	string m_CurrentToken;
	DWORD m_dwMaxTokenLine;
	DWORD m_dwTokenIndex;
	DWORD m_dwFaceSize;
public:
	bool Load(const TCHAR* AseFileName);
private:
	bool LoadAseFile(const TCHAR* AseFileName);
	bool CuttingFile();
	string DestroyToken(const char* szName, const char* szToken);
	string DestroyTokenName(const char* szName, const char* szToken);
	string DividePath(const char* pszFileName);
	const char* GetNextToken();
	INT FindToken(string szToken);
	vector<DWORD> CutIndex(vector<ASE_INDEX> index);
	vector<ASE_VERTEX> CutTriangle(vector<ASE_TRIANGLE> triangle);
	vector<DWORD> SetIndex(vector<ASE_TRIANGLE> pData);
	void GenTriangle();
	bool SetSubObj();
private:
	bool LoadScene();
	bool LoadMaterial();
	bool LoadGeom();
public:
	bool Init();
	bool Frame();
	bool Render(ID3D11DeviceContext* context);
	bool Release();
public:
	AseObject();
	virtual ~AseObject();
};
