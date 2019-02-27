#pragma once
#define _CRT_SECURE_NO_WARNINGS
//#include "JStd.h"
#include "JMesh.h"
#include "JToken.h"
enum MaterialType { DIFFUSE = 1 };
enum aseSectionType { GEOM = 0, HELPER = 1, NUM_CNT };
const static char* aseSection[] = { "GEOMOBJECT", "HELPEROBJECT", };
class JPaser : public JToken
{
public:
	vector<JMesh*>			m_pMeshList;
public:
	ASE_SCENE						m_Scene;
	vector<ASE_MATERIAL>			m_Mtrl;
	vector<ASE_GEOMETRY*>			m_Geom;
public:
	AnimTrack * SetDoublyLinkedList(AnimTrack* pCurrentTrack, AnimTrack* pPrev);
public:
	vector<JMesh*> GetData();
	bool clear();
	int  SearchArray(int iCnt, const char** pSection);
public:
	bool LoadScene();
	bool LoadMaterial();
	INT LoadGeom(ASE_GEOMETRY* geom);
	INT LoadHelperObj(ASE_GEOMETRY* geom);
	bool SetAnimation(ASE_GEOMETRY* geom);
	bool Load();
	JMesh* GetParent(JMesh* pMesh);
public:
	bool GenTriangle(ASE_GEOMETRY* geom);
	bool TriangleSubID();
	bool Convert();
public:
	JPaser();
	virtual ~JPaser();
};

