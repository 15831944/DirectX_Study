#pragma once
//#include "JStd.h"
#include "JMesh.h"
#include "JToken.h"
enum MaterialType { DIFFUSE = 1 };
enum aseSectionType { GEOM = 0, HELPER = 1, NUM_CNT };
const static char* aseSection[] = { "GEOMOBJECT", "HELPEROBJECT", };
class Parser : public JToken
{
public:
	vector<JMesh*>			m_pMeshList;
public:
	ASE_SCENE						m_Scene;
	vector<ASE_MATERIAL>			m_Mtrl;
	vector<ASE_GEOMETRY*>			m_Geom;
public:
	AnimTrack* SetDoublyLinkedList(AnimTrack* pCurrentTrack, AnimTrack* pPrev);
public:
	vector<JMesh*> GetData();
	bool clear();
public:
	bool LoadTemp();
	bool LoadScene();
	bool LoadMaterial();
	bool LoadObject();
	bool SetAnimation(ASE_GEOMETRY* geom);
	bool Load();
	JMesh* GetParent(JMesh* pMesh);
public:
	bool GenTriangle(ASE_GEOMETRY* geom);
	bool Convert();
public:
	Parser();
	virtual ~Parser();
};